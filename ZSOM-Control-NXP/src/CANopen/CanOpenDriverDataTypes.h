/*
 * CanOpenDriverDataTypes.h
 *
 *  Created on: 04.07.2019
 *      Author: dw
 */

#ifndef CANOPEN_CANOPENDRIVERDATATYPES_H_
#define CANOPEN_CANOPENDRIVERDATATYPES_H_

#include <ccand_11xx.h>

typedef struct _WatchNode_t {
	uint32_t value;					/* heartbeat consumer value, accessible via SDO */
	uint32_t counter;				/* used for keeping track of heartbeat */
	uint8_t status;					/* status of node to watch, e.g. NMT_STATE_INTIALIZING, NMT_STATE_STOPPED, etc. */
	uint8_t heartbeatFail;			/* set when heartbeat was not received in time */
	uint8_t BootupAfterHBF;			/* set when bootup message has been received after a heartbeat failure */
	uint8_t NodeID;					/* when != NULL, the software will automatically reconfigure the node specified by NodeID after a heartbeat failure of the node NodeID  */
	uint16_t ProducerTime;			/* when != NULL together with NodeID != NULL, heartbeat producer time will be automatically restored after heartbeat failure of node NodeID */
	uint16_t ConsumerTime;			/* when != NULL together with NodeID != NULL, heartbeat consumer time will be automatically restored after heartbeat failure of node NodeID */
}WatchNode_t;


#endif /* CANOPEN_CANOPENDRIVERDATATYPES_H_ */
