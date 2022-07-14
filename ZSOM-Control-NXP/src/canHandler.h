/*****************************************************************************
 ** File name:		canHandler
 **
 ** Description:	Includes functions needed for the CAN interface. Additionally
 ** 				timer 32_1 is used to generate periodic interrupts.
 **
 ** Created:		29.06.2022/LA
 *****************************************************************************/

#ifndef CANHANDLER_H_
#define CANHANDLER_H_

#include "stdint.h"
#include "ccand_11xx.h"


/** \brief Setup CanCommunication
 *
 */
int initCAN();

void sendFrame(char *buffer, int size);
int send_PDO_log(const char * buf, uint8_t dlc);


#endif /* CANHANDLER_H_ */
