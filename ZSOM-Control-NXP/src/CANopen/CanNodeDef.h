/***********************************************************************
 * $Id:: CAN_Node_Def.h 1604 2012-04-24 11:34:47Z nxp31103     $
 *
 * Project: CANopen Application Example for LPC11Cxx (slave)
 *
 * Description:
 *   CANopen definition header file
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

#ifndef _CAN_NODE_DEF_H
#define _CAN_NODE_DEF_H

#include <stdint.h>
#include "canopen_driver.h"

/* Application variables used in variable OD */

//***********************************************************************************************************
// Application variables used in variable OD
//***********************************************************************************************************
// Declare Variables here by using the extern keyword
extern uint32_t  boardTemperature;
//***********************************************************************************************************


extern uint8_t  error_register;							/* CANopen error register */
extern uint32_t CANopen_Heartbeat_Producer_Value;		/* heartbeat producer value */

void initObjectDirectory();

#endif /* _CAN_NODE_DEF_H */
