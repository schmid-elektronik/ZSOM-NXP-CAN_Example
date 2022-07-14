/*****************************************************************************
 ** File name:		canHandler
 **
 ** Description:	Includes functions needed for the CAN interface. Additionally
 ** 				timer 32_1 is used to generate periodic interrupts.
 **
 ** Created:		29.06.2022/LA
 *****************************************************************************/
#include "chip.h"
#include "canopen_driver.h"
#include "CanNodeDef.h"
#include "canHandler.h"

static CCAN_MSG_OBJ_T logPDO_TX;


volatile uint8_t timeout = 0;
#define WAIT_4_TIMEOUT  while(timeout < 5) { };
#define SET_TIMEOUT    timeout = 0;


void TIMER32_1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER32_1, 1)){
		Chip_TIMER_ClearMatch(LPC_TIMER32_1, 1);
//		togglePin(LED1);
		/* CANopen 1ms tick */
		CANopen_1ms_tick();
		if (timeout < 100){
			timeout++;
		}
	}
}

/*****************************************************************************
** Function name:		initCAN()
**
** Description:			Function for the initialisation of the CAN interface
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
int initCAN()
{
	CANopenInit(100000);

    // CAN 1ms Timer setup
    /* Enable timer 0 clock */
    Chip_TIMER_Init(LPC_TIMER32_1);

    /* Timer rate is system clock rate */
    uint32_t timerFreq = Chip_Clock_GetSystemClockRate();

    /* Timer setup for match and interrupt at TICKRATE_HZ */
    Chip_TIMER_Reset(LPC_TIMER32_1);
    Chip_TIMER_PrescaleSet(LPC_TIMER32_1, timerFreq/10000); //select 100us prescale
    Chip_TIMER_MatchEnableInt(LPC_TIMER32_1, 1);
    Chip_TIMER_SetMatch(LPC_TIMER32_1, 1, 9);	// 1ms per tick
    Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_1, 1);
    Chip_TIMER_Enable(LPC_TIMER32_1);

    /* Enable timer interrupt */
    NVIC_ClearPendingIRQ(TIMER_32_1_IRQn);
    NVIC_EnableIRQ(TIMER_32_1_IRQn);

	logPDO_TX.msgobj = 11;
	logPDO_TX.mode_id = PDO_TX1;
	logPDO_TX.mask = 0;
	logPDO_TX.dlc = 8;

    CANopen_NMT_Change_MyState(NMT_CMD_START);

    initObjectDirectory();

	return 0;
}


void sendFrame(char *buffer, int size)
{
	for(int i=0; i<size; i++){
		logPDO_TX.data[i] = buffer[i];
	}
	logPDO_TX.dlc = size;
	WAIT_4_TIMEOUT;
	SET_TIMEOUT;
	CANopen_Write(&logPDO_TX);
}


int send_PDO_log(const char * buf, uint8_t dlc)
{
	int ret = 0;

	CCAN_MSG_OBJ_T msg_PDO_TX;

	msg_PDO_TX.mode_id = 0x0180 | 0x40;
	msg_PDO_TX.mask = 0x00;
	msg_PDO_TX.dlc = (dlc > 8 ? 8: dlc);
	msg_PDO_TX.msgobj = 8;

	for (int i=0; i<msg_PDO_TX.dlc; i++) {
		msg_PDO_TX.data[i] = buf[i];
	}
	WAIT_4_TIMEOUT;
	SET_TIMEOUT;
	CANopen_Write(&msg_PDO_TX);
	return ret;
}


/*****************************************************************************
** Function name:		CANopen_Init_SDO
**
** Description:			Callback function for initializing SDO parameters
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_Init_SDO(void)
{
	uint32_t i;

	error_register = 0;
	for(i=0; i<WatchListLength; i++)
	{
		WatchList[i].value = 0;
		WatchList[i].counter = 0;
	}
	CANopen_Heartbeat_Producer_Value = 0;
	CANopen_Heartbeat_Producer_Counter = 0;
}

/*****************************************************************************
** Function name:		CANopen_SDOS_Exp_Read
**
** Description:			CANopen Callback for expedited read accesses
**
** Parameters:			index: Index used in expedited read access that triggered
** 						the CANopen expedited read access Callback
** 						subindex: Sub index used in expedited read access that triggered
** 						the CANopen expedited read access Callback
** Returned value:		Return 0 for successs, SDO Abort code for error
*****************************************************************************/
uint32_t CANopen_SDOS_Exp_Read(uint16_t index, uint8_t subindex)
{
	return 0;  /* Return 0 for successs, SDO Abort code for error */
}

/*****************************************************************************
** Function name:		CANopen_SDOS_Exp_Write
**
** Description:			CANopen Callback for expedited write accesses
**
** Parameters:			index: Index used in expedited write access that triggered
** 						the CANopen expedited write access Callback
** 						subindex: Sub index used in expedited write access that triggered
** 						the CANopen expedited write access Callback
** 						dat_ptr: pointer to value_pointer as specified in OD at the
** 						specific index/subindex
** Returned value:		Return 0 for successs, SDO Abort code for error
*****************************************************************************/
uint32_t CANopen_SDOS_Exp_Write(uint16_t index, uint8_t subindex, uint8_t *dat_ptr)
{
	if(index == 0x2003 && subindex == 0x05){ // set second triggers setting the whole time date once
//		setTimeNDate = 1;
	}
	return 0;  /* Return 0 for successs, SDO Abort code for error */
}
/*****************************************************************************
** Function name:		NMT_Reset_Node
**
** Description:			NMT Reset Node callback.
** 						Called upon receiving reset node NMT command.
** 						Can be added by user
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Reset_Node_Received(void)
{

}

/*****************************************************************************
** Function name:		NMT_Reset_Comm
**
** Description:			NMT Reset Communication.
** 						Called upon CanInit / receiving reset node/communication NMT command.
**
** Parameters:			None
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Reset_Comm_Received(void)
{

}

/*****************************************************************************
** Function name:		CAN_Heartbeat_Fail
**
** Description:			CAN heartbeat fail callback.
** 						Function is executed when a heartbeat producer which
** 						is listed in the heartbeat consumer list did not
** 						send a heartbeat on time. Callback functions is executed
** 						after sending the NMT reset command.
**
** Parameters:			Node_ID. Contains the number of the Node_ID which did
** 						not respond on time.
** Returned value:		None
*****************************************************************************/
void CANopen_Heartbeat_Consumer_Failed(uint8_t Node_ID)
{

}

/*****************************************************************************
** Function name:		CANopen_NMT_Consumer_Bootup_Received
**
** Description:			CAN consumer bootup received callback.
** 						Function is executed when a node which is listed in the
** 						watchlist send a boot-up message.
**
** Parameters:			Node_ID. Contains the number of the Node_ID which send
** 						the boot-up message
** Returned value:		None
*****************************************************************************/
void CANopen_NMT_Consumer_Bootup_Received(uint8_t Node_ID)
{

}
