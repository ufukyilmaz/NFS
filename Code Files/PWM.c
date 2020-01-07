#include "PWM.h"

void PWM_Init(uint32_t PWM_Type, volatile uint32_t *IOCON, uint32_t IOCON_FUNC, uint32_t PCONP_MASK, uint32_t channel) {
	
	PWM_TypeDef	*PWM = (PWM_Type == 0) ? PWM0 : PWM1; 

	uint32_t value = *IOCON;
	value &= ~7;
	value |= IOCON_FUNC;
	*IOCON = value;

	PCONP |= PCONP_MASK;
	
	//Enable PWM output for corresponding pin.
	PWM->PCR |= 1 << (channel + 8); 
	
	PWM->TCR = 1 << 1;
		
	PWM->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	
	//Reset TC, when MR0 matches TC. Also generate an interrupt when MR0 matches the value in the TC.
	PWM->MCR = 1 << 1;
	
	PWM->LER |= 1 << 0;
	
	value = PWM->TCR;
	value &= ~(1<<1);
	value |= (1 << 0 | 1 << 3);
	PWM->TCR = value;
}

void PWM_Cycle_Rate(uint32_t PWM_Type, uint32_t period_In_Cycles) {
	PWM_TypeDef	*PWM = (PWM_Type == 0) ? PWM0 : PWM1; 
	
	PWM->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;
	PWM->LER |= 1 << 0;
}

void PWM_Write(uint32_t PWM_Type, uint32_t channel, uint32_t T_ON) {	
	PWM_TypeDef	*PWM = (PWM_Type == 0) ? PWM0 : PWM1; 
	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	T_ON = (uint32_t)(((PWM->MR0) * T_ON) / 100);
	
	if (T_ON == PWM->MR0) {
		T_ON++;
	}
	
	// Calculate the match register for channel
	if (channel == 1) PWM->MR1 = T_ON;
	else if (channel == 2) PWM->MR2 = T_ON;
	else if (channel == 3) PWM->MR3 = T_ON;
	else if (channel == 4) PWM->MR4 = T_ON;
	else if (channel == 5) PWM->MR5 = T_ON;
	else if (channel == 6) PWM->MR6 = T_ON;

	// Enable PWM Match Register Latch for channel
	PWM->LER |= 1 << channel;
}
