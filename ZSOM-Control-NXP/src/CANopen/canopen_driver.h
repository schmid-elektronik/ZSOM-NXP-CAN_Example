/***********************************************************************
 * $Id:: canopen_driver.h 1604 2012-04-24 11:34:47Z nxp31103     $
 *
 * Project: CANopen Application Example for LPC11Cxx
 *
 * Description:
 *   CANopen driver header file
 *
 * Copyright(C) 2012, NXP Semiconductor
 * All rights reserved.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef CANOPEN_DRIVER_H_
#define CANOPEN_DRIVER_H_

#include "chip.h"

#include "ccand_11xx.h"

#include "CanOpenDriverInterface.h"  // This is specific to the node and comes from there

/* Message buffers used by CANopen library:
CANopen driver RX		1
CANopen driver TX		2
heartbeat RX			3
heartbeat TX			4
NMT RX					5
NMT TX					6
SDO Client RX			7
SDO Client TX			8
*/

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define PDO_TX1 (0x0180 | CAN_NODE_ID)
#define PDO_TX2 (0x0280 | CAN_NODE_ID)
#define PDO_TX3 (0x0380 | CAN_NODE_ID)
#define PDO_TX4 (0x0480 | CAN_NODE_ID)
#define PDO_RX1 (0x0200 | CAN_NODE_ID)
#define PDO_RX2 (0x0300 | CAN_NODE_ID)
#define PDO_RX3 (0x0400 | CAN_NODE_ID)
#define PDO_RX4 (0x0500 | CAN_NODE_ID)

#define BYTE1(v) ((uint8_t)((v >> 24) & 0x000000FF))
#define BYTE2(v) ((uint8_t)((v >> 16) & 0x000000FF))
#define BYTE3(v) ((uint8_t)((v >>  8) & 0x000000FF))
#define BYTE4(v) ((uint8_t)((v      ) & 0x000000FF))

#define BYTEL(v) ((uint8_t)((v >>  8) & 0x00FF))
#define BYTEH(v) ((uint8_t)((v      ) & 0x00FF))


/* NMT module control command */
#define NMT_CMD_START				1
#define NMT_CMD_STOP				2
#define NMT_CMD_ENTER_PRE_OP		128
#define NMT_CMD_RESET_NODE			129
#define NMT_CMD_RESET_COMM			130

/* Node State */
#define NMT_STATE_INTIALIZING		0
#define NMT_STATE_STOPPED			4
#define NMT_STATE_OPERATIONAL		5
#define NMT_STATE_PRE_OPERATIONAL	127

/* SDOC State */
#define CANopen_SDOC_Fail			0
#define CANopen_SDOC_Succes			1
#define CANopen_SDOC_Exp_Read_Busy	2
#define CANopen_SDOC_Exp_Write_Busy	3
#define CANopen_SDOC_Seg_Read_Busy	4
#define CANopen_SDOC_Seg_Write_Busy	5

typedef struct _SDOS_Buffer_t {
	uint8_t* data;					/* pointer to buffer */
	uint32_t length;				/* length in buffer */
}SDOS_Buffer_t;


/* CANopen function typedef for callback */
typedef void (*F_CAN_OPEN_RX_CB)(CCAN_MSG_OBJ_T * msg_obj);

/* General CANopen functions */
void CANopenInit(int baudrate);
void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg);
void CANopen_1ms_tick(void);
extern void CANopen_Init_SDO(void);
/* General CAN functions */
void CAN_IRQHandler (void);
void CAN_RX(uint8_t msg_obj_num);
void CAN_TX(uint8_t msg_obj_num);
void CAN_Error(uint32_t error_info);
/* CANopen NMT / Heartbeat functions */
void CANopen_NMT_Send_CMD(uint8_t ID, uint8_t CMD);
void CANopen_NMT_Change_MyState(uint8_t NMT_Command);
void CANopen_Heartbeat_Send(void);
extern void CANopen_NMT_Reset_Node_Received(void);
extern void CANopen_NMT_Reset_Comm_Received(void);
extern void CANopen_NMT_Consumer_Bootup_Received(uint8_t Node_ID);
extern void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID);
/* CANopen SDO server-side functions. Read/write functions are called by callback mechanism */
uint32_t CANopen_SDOS_Seg_Read(uint16_t index, uint8_t subindex, uint8_t openclose, uint8_t *length, uint8_t *data, uint8_t *last);
uint32_t CANopen_SDOS_Seg_Write(uint16_t index, uint8_t subindex, uint8_t openclose, uint8_t length, uint8_t *data, uint8_t *fast_resp);
void CANopen_SDOS_Find_Buffer(uint16_t index, uint8_t subindex, SDOS_Buffer_t** SDOS_Buffer, uint8_t* access_type);
/* CANopen SDO client-side functions */
uint8_t CANopen_SDOC_Exp_Read(uint8_t node_id, uint16_t index, uint8_t subindex, uint8_t* data, uint8_t* valid_data_bytes);
uint8_t CANopen_SDOC_Exp_Write(uint8_t node_id, uint16_t index, uint8_t subindex, uint8_t* data, uint8_t length);
uint8_t CANopen_SDOC_Seg_Read(uint8_t node_id, uint16_t index, uint8_t subindex, void* buff, uint32_t buffSize);
uint8_t CANopen_SDOC_Seg_Write(uint8_t node_id, uint16_t index, uint8_t subindex, void* buff, uint32_t Length);

/* CANopen PDO send */
void CANopen_Write(CCAN_MSG_OBJ_T * msg_TX);

/* register CANopen SDO receive callback function */
void setCANOpen_RX_Callback(F_CAN_OPEN_RX_CB cb, uint8_t msgobj, uint32_t  mode_id);

/* Global Variables */
extern volatile uint8_t CANopen_NMT_MyState;		/* Present state of NMT state machine */
extern volatile uint8_t CANopen_SDOC_State;			/* Present state of SDO client state machine for controlling SDO client transfers */
extern volatile uint32_t CANopen_Heartbeat_Producer_Counter;	/* heartbeat producer counter, used for generating heartbeat */
#endif /* CANOPEN_DRIVER_H_ */
