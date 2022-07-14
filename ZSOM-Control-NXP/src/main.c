/*****************************************************************************
 ** Function name:		main
 **
 ** Description:		C entry. Initializes HW and starts application code
 **
 ** Parameters:			None
 ** Returned value:		None
 *****************************************************************************/
/*****************************************************************************
 * How to add new Variables to the CanOpen dictionary
 *****************************************************************************
 * in the file "CANopen\CAN_Node_Def.c":
 *	1. Define the Variable
 * 	2. Add the Variable to the Can object dictionary
 * 	3. Set the initialisation values
 *
 * in the file "CANopen\CAN_Node_Def.h":
 *	1. Declare the Variable by using the "extern" keyword
 *
 */

#include "chip.h"
#include "canopen_driver.h"
#include "CanNodeDef.h"
#include "canHandler.h"
#include <math.h>

//*********************************************************************************
// function prototypes
//*********************************************************************************
void timerInit(void);
void adcInit(void);
uint16_t adcGetValue(void);

void sendFrame(char *buffer, int size);
int send_PDO_log(const char * buf, uint8_t dlc);

//*********************************************************************************
// defines
//*********************************************************************************
#define TICKRATE_HZ 2			//decides how often Timer16_1 creates an interrupt

//*********************************************************************************
// Timer interrupt routine
//*********************************************************************************
//Interrupt launches Periodically at the Rate defined by TICKRATE_HZ
void TIMER16_1_IRQHandler(void)
{
	if (Chip_TIMER_MatchPending(LPC_TIMER16_1, 1))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_1, 1);			//Clear Interrupt

		//Formula to calculate the board temperature based on the value of the NTC resistor
		float valueNTC = 10000 / (1024./adcGetValue() - 1);
		float temperatureFloat = 1007747 / (298.15 * log(valueNTC / 10000) + 3380)-273.15;
		boardTemperature = (int) ((temperatureFloat * 10)+0.5);	//round value and set to one decimal place by multiplying with 10
	}
}

//*********************************************************************************
// main
//*********************************************************************************
int main(void)
{
	SystemCoreClockUpdate();

	Chip_GPIO_Init(LPC_GPIO);

	initCAN();												//initialisation
	timerInit();
	adcInit();

	while(1)
	{
		__WFI();											//Enter sleep mode
	}
	return 0;
}

//*********************************************************************************
// Other Functions
//*********************************************************************************

void timerInit(void)
{
	Chip_TIMER_Init(LPC_TIMER16_1);

	//Timer konfigurieren
	Chip_TIMER_Reset(LPC_TIMER16_1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 1);
	Chip_TIMER_SetMatch(LPC_TIMER16_1, 1, (Chip_Clock_GetSystemClockRate() / TICKRATE_HZ));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_1, 1);
	Chip_TIMER_Enable(LPC_TIMER16_1);

	//Enable Timer Interrupt
	NVIC_ClearPendingIRQ(TIMER_16_1_IRQn);
	NVIC_EnableIRQ(TIMER_16_1_IRQn);
}

void adcInit(void)
{
	static ADC_CLOCK_SETUP_T ADCSetup;

	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_0, FUNC2);

	Chip_ADC_Init(LPC_ADC, &ADCSetup);
}


// Reads the Value of ADC1 that is connected to the NTC resistor
uint16_t adcGetValue(void)
{
	uint16_t dataADC;
	Chip_ADC_EnableChannel(LPC_ADC, 1, ENABLE);
	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	while (Chip_ADC_ReadStatus(LPC_ADC, 1, ADC_DR_DONE_STAT) != SET){}				// wait for measurement to complete
	Chip_ADC_ReadValue(LPC_ADC, 1, &dataADC);
	Chip_ADC_EnableChannel(LPC_ADC, 1, DISABLE);
	return dataADC;
}

/******************************************************************************
 **                            End Of File
 ******************************************************************************/
