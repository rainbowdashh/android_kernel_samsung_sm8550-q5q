/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2023, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _DT_BINDINGS_CLK_QCOM_CAM_CC_CROW_H
#define _DT_BINDINGS_CLK_QCOM_CAM_CC_CROW_H

/* CAM_CC clocks */
#define CAM_CC_PLL0						0
#define CAM_CC_PLL0_OUT_EVEN					1
#define CAM_CC_PLL0_OUT_ODD					2
#define CAM_CC_PLL1						3
#define CAM_CC_PLL1_OUT_EVEN					4
#define CAM_CC_PLL2						5
#define CAM_CC_PLL2_OUT_EVEN					6
#define CAM_CC_PLL3						7
#define CAM_CC_PLL3_OUT_EVEN					8
#define CAM_CC_PLL4						9
#define CAM_CC_PLL4_OUT_EVEN					10
#define CAM_CC_PLL5						11
#define CAM_CC_PLL5_OUT_EVEN					12
#define CAM_CC_PLL6						13
#define CAM_CC_PLL6_OUT_EVEN					14
#define CAM_CC_PLL7						15
#define CAM_CC_PLL7_OUT_EVEN					16
#define CAM_CC_BPS_AHB_CLK					17
#define CAM_CC_BPS_AREG_CLK					18
#define CAM_CC_BPS_CLK						19
#define CAM_CC_BPS_CLK_SRC					20
#define CAM_CC_CAMNOC_ATB_CLK					21
#define CAM_CC_CAMNOC_AXI_CLK_SRC				22
#define CAM_CC_CAMNOC_AXI_HF_CLK				23
#define CAM_CC_CAMNOC_AXI_SF_CLK				24
#define CAM_CC_CAMNOC_NRT_AXI_CLK				25
#define CAM_CC_CAMNOC_RT_AXI_CLK				26
#define CAM_CC_CCI_0_CLK					27
#define CAM_CC_CCI_0_CLK_SRC					28
#define CAM_CC_CCI_1_CLK					29
#define CAM_CC_CCI_1_CLK_SRC					30
#define CAM_CC_CORE_AHB_CLK					31
#define CAM_CC_CPAS_AHB_CLK					32
#define CAM_CC_CPHY_RX_CLK_SRC					33
#define CAM_CC_CRE_AHB_CLK					34
#define CAM_CC_CRE_CLK						35
#define CAM_CC_CRE_CLK_SRC					36
#define CAM_CC_CSI0PHYTIMER_CLK					37
#define CAM_CC_CSI0PHYTIMER_CLK_SRC				38
#define CAM_CC_CSI1PHYTIMER_CLK					39
#define CAM_CC_CSI1PHYTIMER_CLK_SRC				40
#define CAM_CC_CSI2PHYTIMER_CLK					41
#define CAM_CC_CSI2PHYTIMER_CLK_SRC				42
#define CAM_CC_CSI3PHYTIMER_CLK					43
#define CAM_CC_CSI3PHYTIMER_CLK_SRC				44
#define CAM_CC_CSIPHY0_CLK					45
#define CAM_CC_CSIPHY1_CLK					46
#define CAM_CC_CSIPHY2_CLK					47
#define CAM_CC_CSIPHY3_CLK					48
#define CAM_CC_FAST_AHB_CLK_SRC					49
#define CAM_CC_GDSC_CLK						50
#define CAM_CC_ICP_ATB_CLK					51
#define CAM_CC_ICP_CLK						52
#define CAM_CC_ICP_CLK_SRC					53
#define CAM_CC_ICP_CTI_CLK					54
#define CAM_CC_ICP_TS_CLK					55
#define CAM_CC_JPEG_CLK						56
#define CAM_CC_JPEG_CLK_SRC					57
#define CAM_CC_MCLK0_CLK					58
#define CAM_CC_MCLK0_CLK_SRC					59
#define CAM_CC_MCLK1_CLK					60
#define CAM_CC_MCLK1_CLK_SRC					61
#define CAM_CC_MCLK2_CLK					62
#define CAM_CC_MCLK2_CLK_SRC					63
#define CAM_CC_MCLK3_CLK					64
#define CAM_CC_MCLK3_CLK_SRC					65
#define CAM_CC_MCLK4_CLK					66
#define CAM_CC_MCLK4_CLK_SRC					67
#define CAM_CC_OPE_0_AHB_CLK					68
#define CAM_CC_OPE_0_AREG_CLK					69
#define CAM_CC_OPE_0_CLK					70
#define CAM_CC_OPE_0_CLK_SRC					71
#define CAM_CC_SLEEP_CLK					72
#define CAM_CC_SLEEP_CLK_SRC					73
#define CAM_CC_SLOW_AHB_CLK_SRC					74
#define CAM_CC_SOC_AHB_CLK					75
#define CAM_CC_SYS_TMR_CLK					76
#define CAM_CC_TFE_0_AHB_CLK					77
#define CAM_CC_TFE_0_CLK					78
#define CAM_CC_TFE_0_CLK_SRC					79
#define CAM_CC_TFE_0_CPHY_RX_CLK				80
#define CAM_CC_TFE_0_CSID_CLK					81
#define CAM_CC_TFE_0_CSID_CLK_SRC				82
#define CAM_CC_TFE_1_AHB_CLK					83
#define CAM_CC_TFE_1_CLK					84
#define CAM_CC_TFE_1_CLK_SRC					85
#define CAM_CC_TFE_1_CPHY_RX_CLK				86
#define CAM_CC_TFE_1_CSID_CLK					87
#define CAM_CC_TFE_1_CSID_CLK_SRC				88
#define CAM_CC_TFE_2_AHB_CLK					89
#define CAM_CC_TFE_2_CLK					90
#define CAM_CC_TFE_2_CLK_SRC					91
#define CAM_CC_TFE_2_CPHY_RX_CLK				92
#define CAM_CC_TFE_2_CSID_CLK					93
#define CAM_CC_TFE_2_CSID_CLK_SRC				94
#define CAM_CC_TFE_3_AHB_CLK					95
#define CAM_CC_TFE_3_CLK					96
#define CAM_CC_TFE_3_CLK_SRC					97
#define CAM_CC_TFE_3_CPHY_RX_CLK				98
#define CAM_CC_TFE_3_CSID_CLK					99
#define CAM_CC_TFE_3_CSID_CLK_SRC				100
#define CAM_CC_TOP_SHIFT_CLK					101
#define CAM_CC_XO_CLK_SRC					102

/* CAM_CC resets */
#define CAM_CC_BPS_BCR						0
#define CAM_CC_CAMNOC_BCR					1
#define CAM_CC_CAMSS_TOP_BCR					2
#define CAM_CC_CCI_0_BCR					3
#define CAM_CC_CCI_1_BCR					4
#define CAM_CC_CPAS_BCR						5
#define CAM_CC_CRE_BCR						6
#define CAM_CC_CSI0PHY_BCR					7
#define CAM_CC_CSI1PHY_BCR					8
#define CAM_CC_CSI2PHY_BCR					9
#define CAM_CC_CSI3PHY_BCR					10
#define CAM_CC_ICP_BCR						11
#define CAM_CC_MCLK0_BCR					12
#define CAM_CC_MCLK1_BCR					13
#define CAM_CC_MCLK2_BCR					14
#define CAM_CC_MCLK3_BCR					15
#define CAM_CC_MCLK4_BCR					16
#define CAM_CC_OPE_0_BCR					17
#define CAM_CC_TFE_0_BCR					18
#define CAM_CC_TFE_1_BCR					19
#define CAM_CC_TFE_2_BCR					20
#define CAM_CC_TFE_3_BCR					21

#endif
