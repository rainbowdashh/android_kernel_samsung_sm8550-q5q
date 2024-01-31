/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2022-2023, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _DT_BINDINGS_CLK_QCOM_GCC_SDXPINN_H
#define _DT_BINDINGS_CLK_QCOM_GCC_SDXPINN_H

/* GCC clocks */
#define GPLL0					0
#define GPLL0_OUT_EVEN				1
#define GPLL4					2
#define GPLL5					3
#define GPLL6					4
#define GPLL8					5
#define GCC_AHB_PCIE_LINK_CLK			6
#define GCC_BOOT_ROM_AHB_CLK			7
#define GCC_EEE_EMAC0_CLK			8
#define GCC_EEE_EMAC0_CLK_SRC			9
#define GCC_EEE_EMAC1_CLK			10
#define GCC_EEE_EMAC1_CLK_SRC			11
#define GCC_EMAC0_AXI_CLK			12
#define GCC_EMAC0_CC_SGMIIPHY_RX_CLK		13
#define GCC_EMAC0_CC_SGMIIPHY_TX_CLK		14
#define GCC_EMAC0_PHY_AUX_CLK			15
#define GCC_EMAC0_PHY_AUX_CLK_SRC		16
#define GCC_EMAC0_PTP_CLK			17
#define GCC_EMAC0_PTP_CLK_SRC			18
#define GCC_EMAC0_RGMII_CLK			19
#define GCC_EMAC0_RGMII_CLK_SRC			20
#define GCC_EMAC0_RPCS_RX_CLK			21
#define GCC_EMAC0_RPCS_TX_CLK			22
#define GCC_EMAC0_SLV_AHB_CLK			23
#define GCC_EMAC0_XGXS_RX_CLK			24
#define GCC_EMAC0_XGXS_TX_CLK			25
#define GCC_EMAC1_AXI_CLK			26
#define GCC_EMAC1_CC_SGMIIPHY_RX_CLK		27
#define GCC_EMAC1_CC_SGMIIPHY_TX_CLK		28
#define GCC_EMAC1_PHY_AUX_CLK			29
#define GCC_EMAC1_PHY_AUX_CLK_SRC		30
#define GCC_EMAC1_PTP_CLK			31
#define GCC_EMAC1_PTP_CLK_SRC			32
#define GCC_EMAC1_RGMII_CLK			33
#define GCC_EMAC1_RGMII_CLK_SRC			34
#define GCC_EMAC1_RPCS_RX_CLK			35
#define GCC_EMAC1_RPCS_TX_CLK			36
#define GCC_EMAC1_SLV_AHB_CLK			37
#define GCC_EMAC1_XGXS_RX_CLK			38
#define GCC_EMAC1_XGXS_TX_CLK			39
#define GCC_EMAC_0_CLKREF_EN			40
#define GCC_EMAC_1_CLKREF_EN			41
#define GCC_GP1_CLK				42
#define GCC_GP1_CLK_SRC				43
#define GCC_GP2_CLK				44
#define GCC_GP2_CLK_SRC				45
#define GCC_GP3_CLK				46
#define GCC_GP3_CLK_SRC				47
#define GCC_MVM_AHB_CLK				48
#define GCC_MVM_MASTER_AXI_CLK			49
#define GCC_MVMSS_NTS_CLK			50
#define GCC_PCIE_0_CLKREF_EN			51
#define GCC_PCIE_1_AUX_CLK			52
#define GCC_PCIE_1_AUX_PHY_CLK_SRC		53
#define GCC_PCIE_1_CFG_AHB_CLK			54
#define GCC_PCIE_1_CLKREF_EN			55
#define GCC_PCIE_1_MSTR_AXI_CLK			56
#define GCC_PCIE_1_PHY_RCHNG_CLK		57
#define GCC_PCIE_1_PHY_RCHNG_CLK_SRC		58
#define GCC_PCIE_1_PIPE_CLK			59
#define GCC_PCIE_1_PIPE_CLK_SRC			60
#define GCC_PCIE_1_PIPE_DIV2_CLK		61
#define GCC_PCIE_1_PIPE_DIV2_CLK_SRC		62
#define GCC_PCIE_1_SLV_AXI_CLK			63
#define GCC_PCIE_1_SLV_Q2A_AXI_CLK		64
#define GCC_PCIE_2_AUX_CLK			65
#define GCC_PCIE_2_AUX_PHY_CLK_SRC		66
#define GCC_PCIE_2_CFG_AHB_CLK			67
#define GCC_PCIE_2_CLKREF_EN			68
#define GCC_PCIE_2_MSTR_AXI_CLK			69
#define GCC_PCIE_2_PHY_RCHNG_CLK		70
#define GCC_PCIE_2_PHY_RCHNG_CLK_SRC		71
#define GCC_PCIE_2_PIPE_CLK			72
#define GCC_PCIE_2_PIPE_CLK_SRC			73
#define GCC_PCIE_2_PIPE_DIV2_CLK		74
#define GCC_PCIE_2_PIPE_DIV2_CLK_SRC		75
#define GCC_PCIE_2_SLV_AXI_CLK			76
#define GCC_PCIE_2_SLV_Q2A_AXI_CLK		77
#define GCC_PCIE_AUX_CLK			78
#define GCC_PCIE_AUX_CLK_SRC			79
#define GCC_PCIE_AUX_PHY_CLK_SRC		80
#define GCC_PCIE_CFG_AHB_CLK			81
#define GCC_PCIE_MSTR_AXI_CLK			82
#define GCC_PCIE_PIPE_CLK			83
#define GCC_PCIE_PIPE_CLK_SRC			84
#define GCC_PCIE_RCHNG_PHY_CLK			85
#define GCC_PCIE_RCHNG_PHY_CLK_SRC		86
#define GCC_PCIE_SLEEP_CLK			87
#define GCC_PCIE_SLV_AXI_CLK			88
#define GCC_PCIE_SLV_Q2A_AXI_CLK		89
#define GCC_PDM2_CLK				90
#define GCC_PDM2_CLK_SRC			91
#define GCC_PDM_AHB_CLK				92
#define GCC_PDM_XO4_CLK				93
#define GCC_QUPV3_WRAP0_CORE_2X_CLK		94
#define GCC_QUPV3_WRAP0_CORE_CLK		95
#define GCC_QUPV3_WRAP0_S0_CLK			96
#define GCC_QUPV3_WRAP0_S0_CLK_SRC		97
#define GCC_QUPV3_WRAP0_S1_CLK			98
#define GCC_QUPV3_WRAP0_S1_CLK_SRC		99
#define GCC_QUPV3_WRAP0_S2_CLK			100
#define GCC_QUPV3_WRAP0_S2_CLK_SRC		101
#define GCC_QUPV3_WRAP0_S3_CLK			102
#define GCC_QUPV3_WRAP0_S3_CLK_SRC		103
#define GCC_QUPV3_WRAP0_S4_CLK			104
#define GCC_QUPV3_WRAP0_S4_CLK_SRC		105
#define GCC_QUPV3_WRAP0_S5_CLK			106
#define GCC_QUPV3_WRAP0_S5_CLK_SRC		107
#define GCC_QUPV3_WRAP0_S6_CLK			108
#define GCC_QUPV3_WRAP0_S6_CLK_SRC		109
#define GCC_QUPV3_WRAP0_S7_CLK			110
#define GCC_QUPV3_WRAP0_S7_CLK_SRC		111
#define GCC_QUPV3_WRAP0_S8_CLK			112
#define GCC_QUPV3_WRAP0_S8_CLK_SRC		113
#define GCC_QUPV3_WRAP_0_M_AHB_CLK		114
#define GCC_QUPV3_WRAP_0_S_AHB_CLK		115
#define GCC_SDCC1_AHB_CLK			116
#define GCC_SDCC1_APPS_CLK			117
#define GCC_SDCC1_APPS_CLK_SRC			118
#define GCC_SDCC2_AHB_CLK			119
#define GCC_SDCC2_APPS_CLK			120
#define GCC_SDCC2_APPS_CLK_SRC			121
#define GCC_SYS_NOC_MVMSS_CLK			122
#define GCC_USB2_CLKREF_EN			123
#define GCC_USB30_MASTER_CLK			124
#define GCC_USB30_MASTER_CLK_SRC		125
#define GCC_USB30_MOCK_UTMI_CLK			126
#define GCC_USB30_MOCK_UTMI_CLK_SRC		127
#define GCC_USB30_MOCK_UTMI_POSTDIV_CLK_SRC	128
#define GCC_USB30_MSTR_AXI_CLK			129
#define GCC_USB30_SLEEP_CLK			130
#define GCC_USB30_SLV_AHB_CLK			131
#define GCC_USB3_PHY_AUX_CLK			132
#define GCC_USB3_PHY_AUX_CLK_SRC		133
#define GCC_USB3_PHY_PIPE_CLK			134
#define GCC_USB3_PHY_PIPE_CLK_SRC		135
#define GCC_USB3_PRIM_CLKREF_EN			136
#define GCC_USB_PHY_CFG_AHB2PHY_CLK		137
#define GCC_XO_DIV4_CLK				138
#define GCC_XO_PCIE_LINK_CLK			139
#define GCC_EMAC0_CC_SGMIIPHY_RX_CLK_SRC	140
#define GCC_EMAC0_CC_SGMIIPHY_TX_CLK_SRC	141
#define GCC_EMAC0_SGMIIPHY_MAC_RCLK_SRC		142
#define GCC_EMAC0_SGMIIPHY_MAC_TCLK_SRC		143
#define GCC_EMAC1_CC_SGMIIPHY_RX_CLK_SRC	144
#define GCC_EMAC1_CC_SGMIIPHY_TX_CLK_SRC	145
#define GCC_EMAC1_SGMIIPHY_MAC_RCLK_SRC		146
#define GCC_EMAC1_SGMIIPHY_MAC_TCLK_SRC		147
#define GCC_TLMM_125_CLK_SRC			148
#define GCC_TLMM_125_CLK			149

/* GCC resets */
#define GCC_EMAC0_BCR				0
#define GCC_EMAC1_BCR				1
#define GCC_EMMC_BCR				2
#define GCC_MVMSS_BCR				3
#define GCC_PCIE_1_BCR				4
#define GCC_PCIE_1_LINK_DOWN_BCR		5
#define GCC_PCIE_1_NOCSR_COM_PHY_BCR		6
#define GCC_PCIE_1_PHY_BCR			7
#define GCC_PCIE_2_BCR				8
#define GCC_PCIE_2_LINK_DOWN_BCR		9
#define GCC_PCIE_2_NOCSR_COM_PHY_BCR		10
#define GCC_PCIE_2_PHY_BCR			11
#define GCC_PCIE_BCR				12
#define GCC_PCIE_LINK_DOWN_BCR			13
#define GCC_PCIE_NOCSR_COM_PHY_BCR		14
#define GCC_PCIE_PHY_BCR			15
#define GCC_PCIE_PHY_CFG_AHB_BCR		16
#define GCC_PCIE_PHY_COM_BCR			17
#define GCC_PCIE_PHY_NOCSR_COM_PHY_BCR		18
#define GCC_PDM_BCR				19
#define GCC_QUPV3_WRAPPER_0_BCR			20
#define GCC_QUSB2PHY_BCR			21
#define GCC_SDCC2_BCR				22
#define GCC_TCSR_PCIE_BCR			23
#define GCC_USB30_BCR				24
#define GCC_USB3_PHY_BCR			25
#define GCC_USB3PHY_PHY_BCR			26
#define GCC_USB_PHY_CFG_AHB2PHY_BCR		27
#define GCC_EMAC0_RGMII_CLK_ARES		28

#endif
