#include "External.h"

uint32_t Turn_Counter = 0;

void External_Init() {
	//Change the functionality of the push button as EINT0
	uint32_t temp = IOCON_SPEEDOMETER;
	temp &= ~7;
	temp |= 1;
	IOCON_SPEEDOMETER = temp;
	//Change the External interrupt mode as Edge Sensitive
	EXT->EXTMODE |= 1;
	
	//Change polarity of the External Interrupt as Low-active
	EXT->EXTPOLAR |= 1;
	
	//Enable interrupt for EINT0_IRQn
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_ClearPendingIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler() {
	//Clear interrupt for EINT0
	EXT->EXTINT |= 1;
	
	Turn_Counter = Turn_Counter + 1;
}
