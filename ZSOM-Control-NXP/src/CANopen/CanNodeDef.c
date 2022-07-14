/***********************************************************************
 * $Id:: CAN_Node_Def.c 1604 2012-04-24 11:34:47Z nxp31103     $
 *
 * Project: CANopen Application Example for LPC11Cxx (slave)
 *
 * Description:
 *   CANopen definition source file
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

#include <CanNodeDef.h>
#include <stdint.h>


/* Application variables used in variable OD */

//************************************************************************************************
// Custom Variables
//************************************************************************************************
// TODO
// Define variables for communication here

uint32_t boardTemperature;		//10 times the Temperature in Celsius

//************************************************************************************************

uint8_t  error_register;


int canOpenTimeoutVal = CANOPEN_TIMEOUT_VAL;


volatile uint8_t Version_Data[] = "KB-GPS;V1.11";
volatile SDOS_Buffer_t SDOS_Version =
{
	(uint8_t*)Version_Data,
	sizeof(Version_Data),
};

uint32_t CANopen_Heartbeat_Producer_Value;
WatchNode_t WatchList[1];
uint8_t WatchListLength = sizeof(WatchList)/sizeof(WatchList[0]);



/*	CANopen read-only (constant) Object Dictionary (OD) entries
	Used with Expedited SDO only. Lengths = 1/2/4 bytes */
CCAN_ODCONSTENTRY_T constObjectDir [] =
{
	/* index, subindex,	length,	value */
	{ 0x1000, 0x00, 	4, 		0x00000000UL },
	{ 0x1018, 0x00, 	1, 		0x00000001UL },		/* only vendor ID is specified */
	{ 0x1018, 0x01, 	4, 		0x000002DCUL },		/* NXP vendor ID for CANopen */
};
uint32_t numberConstObjectDirEntries = sizeof(constObjectDir)/sizeof(constObjectDir[0]);

/*	CANopen list of variable Object Dictionary (OD) entries
	Expedited SDO with length=1/2/4 bytes and segmented SDO */
CCAN_ODENTRY_T objectDir [] =
{
	/* index, subindex,	access_type | length,	value_pointer */
	{ 0x1001, 0x00, 	OD_EXP_RO | 1,			(uint8_t *)&error_register },
	{ 0x1016, 0x00,     OD_EXP_RO | 1,          (uint8_t *)&WatchListLength},
	{ 0x1016, 0x01,     OD_EXP_RW | 4,          (uint8_t *)&WatchList[0].value},
	{ 0x1017, 0x00,     OD_EXP_RW | 2,          (uint8_t *)&CANopen_Heartbeat_Producer_Value},

	//************************************************************************************************
	// Can object directory
	//************************************************************************************************
	// TODO
	// Add more entries in the following format:
	// { 0x2000, 0x00,     OD_EXP_RW | 1,          (uint8_t *)&LEDArray},

		{ 0x2000, 0x00,     OD_EXP_RO | 4,          (uint8_t *)&boardTemperature},

	//************************************************************************************************

	{ 0x100a, 0x00,		OD_SEG_RW,				(uint8_t *)&SDOS_Version},
};

uint32_t numberObjectDirEntries = sizeof(objectDir)/sizeof(objectDir[0]);

/* CANopen configuration structure */
CCAN_CANOPENCFG_T canOpenCfg =
{
	CAN_NODE_ID,							/* node_id */
	1,										/* msgobj_rx */
	2,										/* msgobj_tx */
	1,										/* isr_handled */
	(uint32_t)NULL,			/* od_const_num, set to right value in CANopen initialization */
	(CCAN_ODCONSTENTRY_T *)constObjectDir,	/* od_const_table */
	(uint32_t)NULL,					/* od_num, set to right value in CANopen initialization */
	(CCAN_ODENTRY_T *)objectDir,			/* od_table */
};

void initObjectDirectory()
{
	//************************************************************************************************
	// initialisation values
	//************************************************************************************************
	// TODO
	// Set values for initialisation here

	boardTemperature = 0;

	//************************************************************************************************

}
