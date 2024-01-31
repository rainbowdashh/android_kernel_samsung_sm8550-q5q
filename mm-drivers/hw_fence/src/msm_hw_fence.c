// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>

#include "hw_fence_drv_priv.h"
#include "hw_fence_drv_utils.h"
#include "hw_fence_drv_debug.h"
#include "hw_fence_drv_ipc.h"

struct hw_fence_driver_data *hw_fence_drv_data;
static bool hw_fence_driver_enable;

void *msm_hw_fence_register(enum hw_fence_client_id client_id_ext,
	struct msm_hw_fence_mem_addr *mem_descriptor)
{
	struct msm_hw_fence_client *hw_fence_client;
	enum hw_fence_client_id client_id;
	int ret;

	HWFNC_DBG_H("++ client_id_ext:%d\n", client_id_ext);

	if (IS_ERR_OR_NULL(hw_fence_drv_data) || !hw_fence_drv_data->resources_ready) {
		HWFNC_ERR("hw fence driver not ready\n");
		return ERR_PTR(-EAGAIN);
	}

	if (!mem_descriptor || client_id_ext >= HW_FENCE_CLIENT_MAX) {
		HWFNC_ERR("Invalid params: %d client_id_ext:%d\n",
			!mem_descriptor, client_id_ext);
		return ERR_PTR(-EINVAL);
	}

	client_id = hw_fence_utils_get_client_id_priv(hw_fence_drv_data, client_id_ext);
	if (client_id >= HW_FENCE_CLIENT_MAX) {
		HWFNC_ERR("Invalid params: client_id:%d client_id_ext:%d\n",
			client_id, client_id_ext);
		return ERR_PTR(-EINVAL);
	}

	/* Alloc client handle */
	hw_fence_client =  kzalloc(sizeof(*hw_fence_client), GFP_KERNEL);
	if (!hw_fence_client)
		return ERR_PTR(-ENOMEM);

	/* Avoid race condition if multiple-threads request same client at same time */
	mutex_lock(&hw_fence_drv_data->clients_register_lock);
	if (hw_fence_drv_data->clients[client_id]) {
		HWFNC_ERR("client with id %d already registered\n", client_id);
		mutex_unlock(&hw_fence_drv_data->clients_register_lock);
		kfree(hw_fence_client);
		return ERR_PTR(-EINVAL);
	}

	/* Mark client as registered */
	hw_fence_drv_data->clients[client_id] = hw_fence_client;
	mutex_unlock(&hw_fence_drv_data->clients_register_lock);

	hw_fence_client->client_id = client_id;
	hw_fence_client->client_id_ext = client_id_ext;
	hw_fence_client->ipc_client_vid =
		hw_fence_ipcc_get_client_virt_id(hw_fence_drv_data, client_id);
	hw_fence_client->ipc_client_pid =
		hw_fence_ipcc_get_client_phys_id(hw_fence_drv_data, client_id);

	if (hw_fence_client->ipc_client_vid <= 0 || hw_fence_client->ipc_client_pid <= 0) {
		HWFNC_ERR("Failed to find client:%d ipc vid:%d pid:%d\n", client_id,
			hw_fence_client->ipc_client_vid, hw_fence_client->ipc_client_pid);
		ret = -EINVAL;
		goto error;
	}

	hw_fence_client->ipc_signal_id = hw_fence_ipcc_get_signal_id(hw_fence_drv_data, client_id);
	if (hw_fence_client->ipc_signal_id < 0) {
		HWFNC_ERR("Failed to find client:%d signal\n", client_id);
		ret = -EINVAL;
		goto error;
	}

	hw_fence_client->update_rxq = hw_fence_ipcc_needs_rxq_update(hw_fence_drv_data, client_id);
	if (hw_fence_client->update_rxq &&
			hw_fence_drv_data->hw_fence_client_queue_size[client_id].queues_num <
			HW_FENCE_CLIENT_QUEUES) {
		HWFNC_ERR("Cannot update rx queue for tx queue-only client:%d\n", client_id);
		ret = -EINVAL;
		goto error;
	}

	hw_fence_client->send_ipc = hw_fence_ipcc_needs_ipc_irq(hw_fence_drv_data, client_id);
	hw_fence_client->skip_txq_wr_idx = hw_fence_utils_skips_txq_wr_idx(hw_fence_drv_data,
		client_id);

	/* Alloc Client HFI Headers and Queues */
	ret = hw_fence_alloc_client_resources(hw_fence_drv_data,
		hw_fence_client, mem_descriptor);
	if (ret)
		goto error;

	/* Initialize signal for communication withe FenceCTL */
	ret = hw_fence_init_controller_signal(hw_fence_drv_data, hw_fence_client);
	if (ret)
		goto error;

	/*
	 * Update Fence Controller with the address of the Queues and
	 * the Fences Tables for this client
	 */
	ret = hw_fence_init_controller_resources(hw_fence_client);
	if (ret)
		goto error;

	HWFNC_DBG_INIT("-- Initialized ptr:0x%p client_id:%d ipc_signal_id:%d ipc vid:%d pid:%d\n",
		hw_fence_client, hw_fence_client->client_id, hw_fence_client->ipc_signal_id,
		hw_fence_client->ipc_client_vid, hw_fence_client->ipc_client_pid);

#if IS_ENABLED(CONFIG_DEBUG_FS)
	init_waitqueue_head(&hw_fence_client->wait_queue);
#endif /* CONFIG_DEBUG_FS */

	return (void *)hw_fence_client;
error:

	/* Free all the allocated resources */
	hw_fence_cleanup_client(hw_fence_drv_data, hw_fence_client);

	HWFNC_ERR("failed with error:%d\n", ret);
	return ERR_PTR(ret);
}
EXPORT_SYMBOL(msm_hw_fence_register);

int msm_hw_fence_deregister(void *client_handle)
{
	struct msm_hw_fence_client *hw_fence_client;

	if (IS_ERR_OR_NULL(client_handle)) {
		HWFNC_ERR("Invalid client handle\n");
		return -EINVAL;
	}
	hw_fence_client = (struct msm_hw_fence_client *)client_handle;

	if (hw_fence_client->client_id >= hw_fence_drv_data->clients_num) {
		HWFNC_ERR("Invalid client_id:%d\n", hw_fence_client->client_id);
		return -EINVAL;
	}

	HWFNC_DBG_H("+\n");

	/* Free all the allocated resources */
	hw_fence_cleanup_client(hw_fence_drv_data, hw_fence_client);

	HWFNC_DBG_H("-\n");

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_deregister);

int msm_hw_fence_create(void *client_handle,
	struct msm_hw_fence_create_params *params)
{
	struct msm_hw_fence_client *hw_fence_client;
	struct dma_fence_array *array;
	struct dma_fence *fence;
	int ret;

	if (IS_ERR_OR_NULL(client_handle) || !params || !params->fence || !params->handle) {
		HWFNC_ERR("Invalid input\n");
		return -EINVAL;
	}

	if (!hw_fence_drv_data->vm_ready) {
		HWFNC_DBG_H("VM not ready, cannot create fence\n");
		return -EAGAIN;
	}

	hw_fence_client = (struct msm_hw_fence_client *)client_handle;
	fence = (struct dma_fence *)params->fence;

	HWFNC_DBG_H("+\n");

	/* Block any Fence-Array, we should only get individual fences */
	array = to_dma_fence_array(fence);
	if (array) {
		HWFNC_ERR("HW Fence must be created for individual fences\n");
		return -EINVAL;
	}

	/* This Fence is already a HW-Fence */
	if (test_bit(MSM_HW_FENCE_FLAG_ENABLED_BIT, &fence->flags)) {
		HWFNC_ERR("DMA Fence already has HW Fence Flag set\n");
		return -EINVAL;
	}

	/* Create the HW Fence, i.e. add entry in the Global Table for this Fence */
	ret = hw_fence_create(hw_fence_drv_data, hw_fence_client,
		  fence->context, fence->seqno, params->handle);
	if (ret) {
		HWFNC_ERR("Error creating HW fence\n");
		return ret;
	}

	/* If no error, set the HW Fence Flag in the dma-fence */
	set_bit(MSM_HW_FENCE_FLAG_ENABLED_BIT, &fence->flags);

	HWFNC_DBG_H("-\n");

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_create);

int msm_hw_fence_destroy(void *client_handle,
	struct dma_fence *fence)
{
	struct msm_hw_fence_client *hw_fence_client;
	struct dma_fence_array *array;
	int ret;

	if (IS_ERR_OR_NULL(client_handle) || !fence) {
		HWFNC_ERR("Invalid data\n");
		return -EINVAL;
	}
	hw_fence_client = (struct msm_hw_fence_client *)client_handle;

	HWFNC_DBG_H("+\n");

	/* Block any Fence-Array, we should only get individual fences */
	array = to_dma_fence_array(fence);
	if (array) {
		HWFNC_ERR("HW Fence must be destroy for individual fences\n");
		return -EINVAL;
	}

	/* This Fence not a HW-Fence */
	if (!test_bit(MSM_HW_FENCE_FLAG_ENABLED_BIT, &fence->flags)) {
		HWFNC_ERR("DMA Fence is not a HW Fence flags:0x%llx\n", fence->flags);
		return -EINVAL;
	}

	/* Destroy the HW Fence, i.e. remove entry in the Global Table for the Fence */
	ret = hw_fence_destroy(hw_fence_drv_data, hw_fence_client,
		fence->context, fence->seqno);
	if (ret) {
		HWFNC_ERR("Error destroying the HW fence\n");
		return ret;
	}

	/* Clear the HW Fence Flag in the dma-fence */
	clear_bit(MSM_HW_FENCE_FLAG_ENABLED_BIT, &fence->flags);

	HWFNC_DBG_H("-\n");

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_destroy);

int msm_hw_fence_destroy_with_handle(void *client_handle, u64 handle)
{
	struct msm_hw_fence_client *hw_fence_client;
	int ret;

	if (IS_ERR_OR_NULL(client_handle)) {
		HWFNC_ERR("Invalid data\n");
		return -EINVAL;
	}
	hw_fence_client = (struct msm_hw_fence_client *)client_handle;

	if (hw_fence_client->client_id >= hw_fence_drv_data->clients_num) {
		HWFNC_ERR("Invalid client_id:%d\n", hw_fence_client->client_id);
		return -EINVAL;
	}

	HWFNC_DBG_H("+\n");

	/* Destroy the HW Fence, i.e. remove entry in the Global Table for the Fence */
	ret = hw_fence_destroy_with_hash(hw_fence_drv_data, hw_fence_client, handle);
	if (ret) {
		HWFNC_ERR("Error destroying the HW fence handle:%llu client_id:%d\n", handle,
			hw_fence_client->client_id);
		return ret;
	}

	HWFNC_DBG_H("-\n");

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_destroy_with_handle);

int msm_hw_fence_wait_update_v2(void *client_handle,
	struct dma_fence **fence_list, u64 *handles, u64 *client_data_list, u32 num_fences,
	bool create)
{
	struct msm_hw_fence_client *hw_fence_client;
	struct dma_fence_array *array;
	int i, ret = 0;
	enum hw_fence_client_data_id data_id;

	if (IS_ERR_OR_NULL(client_handle) || !fence_list || !*fence_list) {
		HWFNC_ERR("Invalid data\n");
		return -EINVAL;
	}

	if (!hw_fence_drv_data->vm_ready) {
		HWFNC_DBG_H("VM not ready, cannot destroy fence\n");
		return -EAGAIN;
	}

	hw_fence_client = (struct msm_hw_fence_client *)client_handle;
	data_id = hw_fence_get_client_data_id(hw_fence_client->client_id);
	if (client_data_list && data_id >= HW_FENCE_MAX_CLIENTS_WITH_DATA) {
		HWFNC_ERR("Populating non-NULL client_data_list with unsupported client id:%d\n",
			hw_fence_client->client_id);
		return -EINVAL;
	}

	if (hw_fence_client->client_id > hw_fence_drv_data->rxq_clients_num) {
		HWFNC_ERR("Transmit-only client client_id:%d client_id_ext:%d register for wait\n",
			hw_fence_client->client_id, hw_fence_client->client_id_ext);
		return -EINVAL;
	}

	HWFNC_DBG_H("+\n");

	/* Process all the list of fences */
	for (i = 0; i < num_fences; i++) {
		struct dma_fence *fence = fence_list[i];
		u64 hash, client_data = 0;

		if (client_data_list)
			client_data = client_data_list[i];

		/* Process a Fence-Array */
		array = to_dma_fence_array(fence);
		if (array) {
			ret = hw_fence_process_fence_array(hw_fence_drv_data, hw_fence_client,
				array, &hash, client_data);
			if (ret) {
				HWFNC_ERR("Failed to process FenceArray\n");
				return ret;
			}
		} else {
			/* Process individual Fence */
			ret = hw_fence_process_fence(hw_fence_drv_data, hw_fence_client, fence,
				&hash, client_data);
			if (ret) {
				HWFNC_ERR("Failed to process Fence\n");
				return ret;
			}
		}

		if (handles)
			handles[i] = hash;
	}

	HWFNC_DBG_H("-\n");

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_wait_update_v2);

int msm_hw_fence_wait_update(void *client_handle,
	struct dma_fence **fence_list, u32 num_fences, bool create)
{
	return msm_hw_fence_wait_update_v2(client_handle, fence_list, NULL, NULL, num_fences,
		create);
}
EXPORT_SYMBOL(msm_hw_fence_wait_update);

int msm_hw_fence_reset_client(void *client_handle, u32 reset_flags)
{
	struct msm_hw_fence_client *hw_fence_client;
	struct msm_hw_fence *hw_fences_tbl;
	int i;

	if (IS_ERR_OR_NULL(client_handle)) {
		HWFNC_ERR("Invalid client handle!\n");
		return -EINVAL;
	}

	if (!hw_fence_drv_data->vm_ready) {
		HWFNC_DBG_H("VM not ready, cannot reset client\n");
		return -EAGAIN;
	}

	hw_fence_client = (struct msm_hw_fence_client *)client_handle;
	hw_fences_tbl = hw_fence_drv_data->hw_fences_tbl;

	HWFNC_DBG_L("reset fences and queues for client:%d\n", hw_fence_client->client_id);
	for (i = 0; i < hw_fence_drv_data->hw_fences_tbl_cnt; i++)
		hw_fence_utils_cleanup_fence(hw_fence_drv_data, hw_fence_client,
			&hw_fences_tbl[i], i, reset_flags);

	hw_fence_utils_reset_queues(hw_fence_drv_data, hw_fence_client);

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_reset_client);

int msm_hw_fence_reset_client_by_id(enum hw_fence_client_id client_id_ext, u32 reset_flags)
{
	enum hw_fence_client_id client_id;

	if (client_id_ext >= HW_FENCE_CLIENT_MAX) {
		HWFNC_ERR("Invalid client_id_ext:%d\n", client_id_ext);
		return -EINVAL;
	}

	client_id = hw_fence_utils_get_client_id_priv(hw_fence_drv_data, client_id_ext);

	if (client_id >= HW_FENCE_CLIENT_MAX) {
		HWFNC_ERR("Invalid client_id:%d client_id_ext:%d\n", client_id, client_id_ext);
		return -EINVAL;
	}

	return msm_hw_fence_reset_client(hw_fence_drv_data->clients[client_id],
		reset_flags);
}
EXPORT_SYMBOL(msm_hw_fence_reset_client_by_id);

int msm_hw_fence_update_txq(void *client_handle, u64 handle, u64 flags, u32 error)
{
	struct msm_hw_fence_client *hw_fence_client;

	if (IS_ERR_OR_NULL(hw_fence_drv_data) || !hw_fence_drv_data->resources_ready ||
			!hw_fence_drv_data->vm_ready) {
		HWFNC_ERR("hw fence driver  or vm not ready\n");
		return -EAGAIN;
	} else if (IS_ERR_OR_NULL(client_handle) ||
			(handle >= hw_fence_drv_data->hw_fences_tbl_cnt)) {
		HWFNC_ERR("Invalid handle:%d or client handle:%d max:%d\n", handle,
			IS_ERR_OR_NULL(client_handle), hw_fence_drv_data->hw_fences_tbl_cnt);
		return -EINVAL;
	}
	hw_fence_client = (struct msm_hw_fence_client *)client_handle;

	/* Write to Tx queue */
	hw_fence_update_queue(hw_fence_drv_data, hw_fence_client,
		hw_fence_drv_data->hw_fences_tbl[handle].ctx_id,
		hw_fence_drv_data->hw_fences_tbl[handle].seq_id, handle,
		flags, 0, error, HW_FENCE_TX_QUEUE - 1);

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_update_txq);

/* tx client has to be the physical, rx client virtual id*/
int msm_hw_fence_trigger_signal(void *client_handle,
	u32 tx_client_pid, u32 rx_client_vid,
	u32 signal_id)
{
	struct msm_hw_fence_client *hw_fence_client;

	if (IS_ERR_OR_NULL(hw_fence_drv_data) || !hw_fence_drv_data->resources_ready
			|| !hw_fence_drv_data->vm_ready) {
		HWFNC_ERR("hw fence driver or vm not ready\n");
		return -EAGAIN;
	} else if (IS_ERR_OR_NULL(client_handle)) {
		HWFNC_ERR("Invalid client\n");
		return -EINVAL;
	}
	hw_fence_client = (struct msm_hw_fence_client *)client_handle;

	HWFNC_DBG_H("sending ipc for client:%d\n", hw_fence_client->client_id);
	hw_fence_ipcc_trigger_signal(hw_fence_drv_data, tx_client_pid,
		rx_client_vid, signal_id);

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_trigger_signal);

/* Function used for simulation purposes only. */
int msm_hw_fence_driver_doorbell_sim(u64 db_mask)
{
	if (IS_ERR_OR_NULL(hw_fence_drv_data) || !hw_fence_drv_data->resources_ready) {
		HWFNC_ERR("hw fence driver not ready\n");
		return -EAGAIN;
	}

	HWFNC_DBG_IRQ("db callback sim-mode flags:0x%llx qtime:%llu\n",
		db_mask, hw_fence_get_qtime(hw_fence_drv_data));

	hw_fence_utils_process_doorbell_mask(hw_fence_drv_data, db_mask);

	return 0;
}
EXPORT_SYMBOL(msm_hw_fence_driver_doorbell_sim);

static int msm_hw_fence_probe_init(struct platform_device *pdev)
{
	int rc;

	HWFNC_DBG_H("+\n");

	hw_fence_drv_data = kzalloc(sizeof(*hw_fence_drv_data), GFP_KERNEL);
	if (!hw_fence_drv_data)
		return -ENOMEM;

	dev_set_drvdata(&pdev->dev, hw_fence_drv_data);
	hw_fence_drv_data->dev = &pdev->dev;

	/* Initialize HW Fence Driver resources */
	rc = hw_fence_init(hw_fence_drv_data);
	if (rc)
		goto error;

	mutex_init(&hw_fence_drv_data->clients_register_lock);

	/* set ready ealue so clients can register */
	hw_fence_drv_data->resources_ready = true;

	HWFNC_DBG_H("-\n");

	return rc;

error:
	dev_set_drvdata(&pdev->dev, NULL);
	kfree(hw_fence_drv_data);
	hw_fence_drv_data = (void *) -EPROBE_DEFER;

	HWFNC_ERR("error %d\n", rc);
	return rc;
}

static int msm_hw_fence_probe(struct platform_device *pdev)
{
	int rc = -EINVAL;

	HWFNC_DBG_H("+\n");

	if (!pdev) {
		HWFNC_ERR("null platform dev\n");
		return -EINVAL;
	}

	if (!hw_fence_driver_enable) {
		HWFNC_DBG_INFO("hw fence driver not enabled\n");
		return -EOPNOTSUPP;
	}

	if (of_device_is_compatible(pdev->dev.of_node, "qcom,msm-hw-fence"))
		rc = msm_hw_fence_probe_init(pdev);
	if (rc)
		goto err_exit;

	HWFNC_DBG_H("-\n");

	return 0;

err_exit:
	HWFNC_ERR("error %d\n", rc);
	return rc;
}

static int msm_hw_fence_remove(struct platform_device *pdev)
{
	HWFNC_DBG_H("+\n");

	if (!pdev) {
		HWFNC_ERR("null platform dev\n");
		return -EINVAL;
	}

	hw_fence_drv_data = dev_get_drvdata(&pdev->dev);
	if (!hw_fence_drv_data) {
		HWFNC_ERR("null driver data\n");
		return -EINVAL;
	}

	dev_set_drvdata(&pdev->dev, NULL);
	kfree(hw_fence_drv_data);
	hw_fence_drv_data = (void *) -EPROBE_DEFER;

	HWFNC_DBG_H("-\n");

	return 0;
}

static const struct of_device_id msm_hw_fence_dt_match[] = {
	{.compatible = "qcom,msm-hw-fence"},
	{}
};

static struct platform_driver msm_hw_fence_driver = {
	.probe = msm_hw_fence_probe,
	.remove = msm_hw_fence_remove,
	.driver = {
		.name = "msm-hw-fence",
		.of_match_table = of_match_ptr(msm_hw_fence_dt_match),
	},
};

static int __init msm_hw_fence_init(void)
{
	int rc = 0;

	HWFNC_DBG_H("+\n");

	rc = platform_driver_register(&msm_hw_fence_driver);
	if (rc) {
		HWFNC_ERR("%s: failed to register platform driver\n",
			__func__);
		return rc;
	}

	HWFNC_DBG_H("-\n");

	return 0;
}

static void __exit msm_hw_fence_exit(void)
{
	HWFNC_DBG_H("+\n");

	platform_driver_unregister(&msm_hw_fence_driver);

	HWFNC_DBG_H("-\n");
}

module_param_named(enable, hw_fence_driver_enable, bool, 0600);
MODULE_PARM_DESC(enable, "Enable hardware fences");

module_init(msm_hw_fence_init);
module_exit(msm_hw_fence_exit);

MODULE_DESCRIPTION("QTI HW Fence Driver");
MODULE_LICENSE("GPL v2");
