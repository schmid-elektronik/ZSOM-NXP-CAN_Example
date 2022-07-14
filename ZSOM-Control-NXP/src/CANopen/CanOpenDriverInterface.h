/*
 * CanOpenDriverInterface.h
 *
 *  Created on: 04.07.2019
 *      Author: dw
 *
 *  Adapt here for specific Nodes
 *  This file is included in canopen_driver, XXXCanNodeDef, XXXCanHandler
 */

#ifndef CANOPEN_CANOPENDRIVERINTERFACE_H_
#define CANOPEN_CANOPENDRIVERINTERFACE_H_

#include <ccand_11xx.h>
#include "CanOpenDriverDataTypes.h"

// interface to specific node:
#define CAN_NODE_ID (0x40)
#define CANOPEN_TIMEOUT_VAL		100					/* in ms */


extern CCAN_CANOPENCFG_T canOpenCfg;
extern CCAN_ODENTRY_T  objectDir[];
extern WatchNode_t WatchList[];							/* for watching nodes */
extern uint8_t WatchListLength;							/* number of nodes in watchlist must be known */
extern int canOpenTimeoutVal;
extern uint32_t CANopen_Heartbeat_Producer_Value;

extern uint32_t numberConstObjectDirEntries;
extern uint32_t numberObjectDirEntries;

// we want to use them in user code to interact with transfers
uint32_t CANopen_SDOS_Exp_Read(uint16_t index, uint8_t subindex);
uint32_t CANopen_SDOS_Exp_Write(uint16_t index, uint8_t subindex, uint8_t *dat_ptr);



#endif /* CANOPEN_CANOPENDRIVERINTERFACE_H_ */
