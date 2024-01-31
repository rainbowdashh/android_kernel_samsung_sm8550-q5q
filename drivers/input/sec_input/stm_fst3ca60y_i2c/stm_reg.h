/* SPDX-License-Identifier: GPL-2.0 */
/* drivers/input/sec_input/stm/stm_reg.h
 *
 * Copyright (C) 2020 Samsung Electronics Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define USE_POR_AFTER_I2C_RETRY

#define BRUSH_Z_DATA			63 /* for ArtCanvas */

#undef USE_OPEN_DWORK

#ifdef USE_OPEN_DWORK
#define TOUCH_OPEN_DWORK_TIME		10
#endif
#define TOUCH_PRINT_INFO_DWORK_TIME	30000	/* 30s */

#define TOUCH_PRINT_INFO_DWORK_TIME	30000	/* 30s */
#define TOUCH_RESET_DWORK_TIME		10
#define TOUCH_POWER_ON_DWORK_TIME	35

#define FIRMWARE_IC			"STM"
#define STM_TS_MAX_FW_PATH			64
#define STM_TS_TS_DRV_NAME			"STM_TS_TOUCH"
#define STM_TS_TS_DRV_VERSION		"0100"

#define STM_TS_TS_I2C_RETRY_CNT		3

#define STM_TS_ID0				0x52
#define STM_TS_ID1				0x36

#define MAX_EVENT_COUNT		31
#define STM_TS_EVENT_BUFF_SIZE		16
#define STM_TS_VERSION_SIZE		9

#define PRESSURE_MIN			0
#define PRESSURE_MAX			127
#define FINGER_MAX			10
#define AREA_MIN			PRESSURE_MIN
#define AREA_MAX			PRESSURE_MAX

#define INT_ENABLE			1
#define INT_DISABLE			0

#define STM_TS_CMD_SPONGE_ACCESS				0x0000

/* COMMANDS */

// For Spruce and Angsana
#define STM_TS_SCAN_MODE_ADDR 0x0010 /* FW reg scan mode address */
#define STM_TS_FLASH_SAVE_ADDR 0x0020 /* FW reg flash save address */
#define STM_TS_HDM_WRITE_REQ_ADDR 0x0021      /* FW reg hdm write address */
#define STM_TS_PI_ADDR 0x0022                 /* FW reg Panel Init address */
#define STM_TS_HDM_REQ_ADDR 0x0023            /* FW reg HDM request address */
#define STM_TS_ITO_TRIGGER_ADDR 0x0024        /* FW reg ITO trigger address */
#define STM_TS_SYS_ERROR_ADDR 0x0040          /* FW reg system error status  address */
#define STM_TS_FIFO_READ_ADDR 0x0060          /* FW reg FIFO read address */

#define STM_TS_BL_MODE_ADDR 0x0020 /* /< bootloader mode address  */
#define STM_TS_BL_FLASH_ADDR 0x0078 /* /< bootloader flash address  */
#define STM_TS_BL_CTRL_ADDR 0x007D  /* /< bootloader control address */
#define STM_TS_BL_KEY_ADDR 0x007F   /* /< bootloader key address */

#define STM_TS_REG_CRC_MASK 0x03   /* mask to read fw register status of reg crc */
#define STM_TS_REG_MISC_MASK 0x0C  /* mask to read fw register status of misc crc */
#define STM_TS_MS_CRC_MASK 0x0F    /* mask to read fw register status of ms cx crc */
#define STM_TS_SS_CRC_MASK 0xF0    /* mask to read fw register status of ss cx crc */
#define STM_TS_IOFF_CRC_MASK 0xFF  /* mask to read fw register status of ioff crc */
#define STM_TS_RAWMS_CRC_MASK 0x03 /* mask to read fw register status of raw frame data crc */

#define STM_TS_CMD_SENSE_ON				0x10
#define STM_TS_CMD_SENSE_OFF				0x11
#define STM_TS_CMD_SW_RESET				0x12
#define STM_TS_CMD_FORCE_CALIBRATION			0x13
#define STM_TS_CMD_FACTORY_PANELCALIBRATION		0x14

#define STM_TS_READ_GPIO_STATUS				0x20
#define STM_TS_READ_FIRMWARE_INTEGRITY			0x21
#define STM_TS_READ_DEVICE_ID				0x22
#define STM_TS_READ_PANEL_INFO				0x23
#define STM_TS_READ_FW_VERSION				0x24

#define STM_TS_CMD_SET_GET_TOUCHTYPE			0x30
#define STM_TS_CMD_SET_GET_OPMODE				0x31
#define STM_TS_CMD_SET_GET_WIRELESSCHARGER_MODE			0x32
#define STM_TS_CMD_SET_GET_NOISE_MODE			0x33
#define STM_TS_CMD_SET_GET_REPORT_RATE			0x34
#define STM_TS_CMD_SET_GET_TOUCH_MODE_FOR_THRESHOLD	0x35
#define STM_TS_CMD_SET_GET_TOUCH_THRESHOLD			0x36
#define STM_TS_CMD_SET_GET_KEY_THRESHOLD			0x37
#define STM_TS_CMD_SET_GET_COVERTYPE			0x38
#define STM_TS_CMD_WRITE_WAKEUP_GESTURE			0x39
#define STM_TS_CMD_WRITE_COORDINATE_FILTER			0x3A
#define STM_TS_CMD_SET_FOD_FINGER_MERGE			0x3B
#define STM_TS_CMD_SET_LOWTEMPERATURE_MODE			0x3C
#define STM_TS_CMD_SET_FOD_INT_CONTROL			0x3D
#define STM_TS_CMD_SET_GET_WIRECHARGER_MODE			0x3F

#define STM_TS_CMD_SET_EAR_DETECT				0x41
#define STM_TS_CMD_SET_POCKET_MODE			0x42

#define STM_TS_READ_ONE_EVENT				0xED

#define STM_TS_CMD_CLEAR_ALL_EVENT				0x62

#define STM_TS_CMD_SENSITIVITY_MODE			0x70
#define STM_TS_READ_SENSITIVITY_VALUE			0x72
#define STM_TS_CMD_RUN_POLARITY_TEST				0x77
#define STM_TS_CMD_RUN_HF_SENSOR_DIFF_TEST			0x79
#define STM_TS_CMD_RUN_SRAM_TEST				0x78

#define STM_TS_CMD_SET_LPM_AOD_OFF_ON			0x9B

#define STM_TS_CMD_LPM_ASYNC_SCAN				0x00
#define STM_TS_CMD_LPM_SYNC_SCAN				0x01
#define STM_TS_CMD_NPM_SYNC_SCAN				0x01

#define STM_TS_CMD_SET_FUNCTION_ONOFF			0xC1
#define STM_TS_CMD_FUNCTION_SET_NOTE_MODE		0x10
#define STM_TS_CMD_FUNCTION_SET_GAME_MODE		0x11
#define STM_TS_CMD_FUNCTION_SET_HOVER_DETECTION		0x12
#define STM_TS_CMD_FUNCTION_SET_PEN_SAVING_MODE		0x13
#define STM_TS_CMD_FUNCTION_SET_PEN_DETECTION		0x14
#define STM_TS_CMD_FUNCTION_SET_TSP_BLOCK		0x15

/* STM_TS SPONGE COMMAND */
#define STM_TS_CMD_SPONGE_READ_WRITE_CMD		0xEE
#define STM_TS_CMD_SPONGE_NOTIFY_CMD			0xC0

#define STM_TS_CMD_SPONGE_OFFSET_MODE			0x00
#define STM_TS_CMD_SPONGE_OFFSET_MODE_01			0x01
#define STM_TS_CMD_SPONGE_OFFSET_AOD_RECT			0x02
#define STM_TS_CMD_SPONGE_OFFSET_UTC			0x10
#define STM_TS_CMD_SPONGE_LP_DUMP				0xF0

/* First byte of ONE EVENT */
#define STM_TS_EVENT_PASS_REPORT				0xC3
#define STM_TS_EVENT_STATUS_REPORT				0x43
#define STM_TS_EVENT_JITTER_RESULT              0x49
#define STM_TS_EVENT_ERROR_REPORT				0xF3

/* Test Event */
#define STM_TS_EVENT_JITTER_MUTUAL_TEST			0x01
#define STM_TS_EVENT_JITTER_SELF_TEST			0x02

#define STM_TS_EVENT_JITTER_MUTUAL_MAX			0x01
#define STM_TS_EVENT_JITTER_MUTUAL_MIN			0x02
#define STM_TS_EVENT_JITTER_MUTUAL_AVG			0x03
#define STM_TS_EVENT_JITTER_SELF_TX_P2P			0x05
#define STM_TS_EVENT_JITTER_SELF_RX_P2P			0x06

#define STM_TS_EVENT_SRAM_TEST_RESULT			0xD0

/* Status Event */
#define STM_TS_COORDINATE_EVENT			0
#define STM_TS_STATUS_EVENT			1
#define STM_TS_GESTURE_EVENT			2
#define STM_TS_VENDOR_EVENT			3

#define STM_TS_GESTURE_CODE_SPAY			0x00
#define STM_TS_GESTURE_CODE_DOUBLE_TAP		0x01
#define STM_TS_GESTURE_CODE_DUMPFLUSH		0x05

#define STM_TS_COORDINATE_ACTION_NONE		0
#define STM_TS_COORDINATE_ACTION_PRESS		1
#define STM_TS_COORDINATE_ACTION_MOVE		2
#define STM_TS_COORDINATE_ACTION_RELEASE		3

#define STM_TS_TOUCHTYPE_NORMAL		0
#define STM_TS_TOUCHTYPE_HOVER		1
#define STM_TS_TOUCHTYPE_FLIPCOVER		2
#define STM_TS_TOUCHTYPE_GLOVE		3
#define STM_TS_TOUCHTYPE_STYLUS		4
#define STM_TS_TOUCHTYPE_PALM		5
#define STM_TS_TOUCHTYPE_WET			6
#define STM_TS_TOUCHTYPE_PROXIMITY		7
#define STM_TS_TOUCHTYPE_JIG			8

/* SEC_TS_DUMP_ID */
#define STM_TS_SPONGE_DUMP_0			0x00
#define STM_TS_SPONGE_DUMP_1			0x01

/* Status - ERROR event */
#define STM_TS_EVENT_STATUSTYPE_CMDDRIVEN		0
#define STM_TS_EVENT_STATUSTYPE_ERROR			1
#define STM_TS_EVENT_STATUSTYPE_INFO			2
#define STM_TS_EVENT_STATUSTYPE_USERINPUT		3
#define STM_TS_EVENT_STATUSTYPE_VENDORINFO		7

#define STM_TS_ERR_EVNET_CORE_ERR			0x00
#define STM_TS_ERR_EVENT_QUEUE_FULL		0x01
#define STM_TS_ERR_EVENT_ESD			0x02

/* Status - Information report */
#define STM_TS_INFO_READY_STATUS			0x00
#define STM_TS_INFO_WET_MODE			0x01
#define STM_TS_INFO_NOISE_MODE			0x02
#define STM_TS_INFO_XENOSENSOR_DETECT		0x04

// Scan mode for A0 command
#define STM_TS_SCAN_MODE_SCAN_OFF			0
#define STM_TS_SCAN_MODE_MS_SS_SCAN		(1 << 0)
#define STM_TS_SCAN_MODE_KEY_SCAN			(1 << 1)
#define STM_TS_SCAN_MODE_HOVER_SCAN		(1 << 2)
#define STM_TS_SCAN_MODE_FORCE_TOUCH_SCAN		(1 << 4)
#define STM_TS_SCAN_MODE_DEFAULT			STM_TS_SCAN_MODE_MS_SS_SCAN


/* Control Command */

// For 0x30 command - touch type
#define STM_TS_TOUCHTYPE_BIT_TOUCH		(1 << 0)
#define STM_TS_TOUCHTYPE_BIT_HOVER		(1 << 1)
#define STM_TS_TOUCHTYPE_BIT_COVER		(1 << 2)
#define STM_TS_TOUCHTYPE_BIT_GLOVE		(1 << 3)
#define STM_TS_TOUCHTYPE_BIT_STYLUS	(1 << 4)
#define STM_TS_TOUCHTYPE_BIT_PALM		(1 << 5)
#define STM_TS_TOUCHTYPE_BIT_WET		(1 << 6)
#define STM_TS_TOUCHTYPE_BIT_PROXIMITY	(1 << 7)
#define STM_TS_TOUCHTYPE_DEFAULT_ENABLE	(STM_TS_TOUCHTYPE_BIT_TOUCH | STM_TS_TOUCHTYPE_BIT_PALM | STM_TS_TOUCHTYPE_BIT_WET)

// For 0x31 command - touch operation mode
#define STM_TS_OPMODE_NORMAL		0
#define STM_TS_OPMODE_LOWPOWER		1

// For 0x32 command - charger mode
#define STM_TS_BIT_CHARGER_MODE_NORMAL			0
#define STM_TS_BIT_CHARGER_MODE_WIRE_CHARGER		1
#define STM_TS_BIT_CHARGER_MODE_WIRELESS_CHARGER		2
#define STM_TS_BIT_CHARGER_MODE_WIRELESS_BATTERY_PACK	3

// For 0xC1 command - on/off function
#define STM_TS_FUNCTION_ENABLE_SIP_MODE			0x00
#define STM_TS_FUNCTION_SET_MONITOR_NOISE_MODE		0x01
#define STM_TS_FUNCTION_ENABLE_BRUSH_MODE			0x02
#define STM_TS_FUNCTION_ENABLE_DEAD_ZONE			0x04	/* *#0*# */
#define STM_TS_FUNCTION_ENABLE_SPONGE_LIB			0x05
#define STM_TS_FUNCTION_EDGE_AREA				0x07	/* used for grip cmd */
#define STM_TS_FUNCTION_DEAD_ZONE				0x08	/* used for grip cmd */
#define STM_TS_FUNCTION_LANDSCAPE_MODE			0x09	/* used for grip cmd */
#define STM_TS_FUNCTION_LANDSCAPE_TOP_BOTTOM		0x0A	/* used for grip cmd */
#define STM_TS_FUNCTION_EDGE_HANDLER			0x0C	/* used for grip cmd */
#define STM_TS_FUNCTION_ENABLE_VSYNC			0x0D
#define STM_TS_FUNCTION_SET_TOUCHABLE_AREA			0x0F

/* STM_TS DEBUG FLAG */
#define STM_TS_DEBUG_PRINT_I2C_READ_CMD			0x04
#define STM_TS_DEBUG_PRINT_I2C_WRITE_CMD			0x08
#define STM_TS_DEBUG_SEND_UEVENT				0x80

#define STM_TS_RETRY_COUNT					10
#define STM_TS_DELAY_NVWRITE				50

/* gesture SF */
#define STM_TS_GESTURE_SAMSUNG_FEATURE			1

/* gesture type */
#define STM_TS_SPONGE_EVENT_SWIPE_UP			0
#define STM_TS_SPONGE_EVENT_DOUBLETAP			1
#define STM_TS_SPONGE_EVENT_PRESS			3
#define STM_TS_SPONGE_EVENT_SINGLETAP			4

/* gesture ID */
#define STM_TS_SPONGE_EVENT_GESTURE_ID_AOD			0
#define STM_TS_SPONGE_EVENT_GESTURE_ID_DOUBLETAP_TO_WAKEUP	1
#define STM_TS_SPONGE_EVENT_GESTURE_ID_FOD_LONG		0
#define STM_TS_SPONGE_EVENT_GESTURE_ID_FOD_NORMAL		1
#define STM_TS_SPONGE_EVENT_GESTURE_ID_FOD_RELEASE		2
#define STM_TS_SPONGE_EVENT_GESTURE_ID_FOD_OUT		3
#define STM_TS_SPONGE_EVENT_GESTURE_ID_FOD_VI		4

#define STM_TS_ENABLE					1
#define STM_TS_DISABLE					0

#define STM_TS_SPONGE_LP_DUMP_LENGTH	70

#define STM_TS_MAX_X_RESOLUTION	4096
#define STM_TS_MAX_Y_RESOLUTION	4096
#define STM_TS_MAX_NUM_FORCE		50	/* Number of TX CH */
#define STM_TS_MAX_NUM_SENSE		50	/* Number of RX CH */

#define STM_TS_LFD_CTRL_LOCK			1
#define STM_TS_LFD_CTRL_UNLOCK			2

#define NORMAL_CX2	0	/* single driving */
#define ACTIVE_CX2	1	/* multi driving */

/* fw update */
#define CODE_ADDR_START 0x00000000

#define STM_TS_CMD_FRM_BUFF_W   0xB6
#define STM_TS_CMD_FRM_BUFF_R   0xB7

#define STM_TS_SPI_REG_W_CHUNK 128
#define STM_TS_SPI_REG_R_CHUNK 1024

#define STM_TS_CMD_REG_W		0xFA
#define STM_TS_CMD_REG_R		0xFA

#define STM_TS_CMD_SPONGE_W	0xD0

#define STM_TS_CMD_SNR_R	0x72
#define STM_TS_CMD_SNR_R_SIZE	2

#define FRAME_BUFFER_ADDR 0x8000

