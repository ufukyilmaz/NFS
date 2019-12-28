#include "ADC.h"

uint32_t ADC_Last_Left = 0;
uint32_t ADC_Last_Right = 0;
uint32_t ADC_Last_Trimpot = 0;
uint8_t ADC_New_Data_Available_Left = 0;
uint8_t ADC_New_Data_Available_Right = 0;
uint8_t ADC_New_Data_Available_Trimpot = 0;

void ADC_Init(volatile uint32_t *IOCON, uint32_t IOCON_FUNC, uint32_t channel) {
	//Change the function value of pin to ADC.
	uint32_t value = *IOCON;
	value &= ~7;
	value |= IOCON_FUNC;
	*IOCON = value;
	//Change the mode value of pin to mode which should be selected if Analog mode is used.
	*IOCON &= ~(1 << 3 | 1<<4);
	//Change Analog/Digital mode of pin to Analog.
	*IOCON &= ~(1 << 7);
	//Turn on ADC.
	PCONP |= (1 << 12);
	//Set the CLKDIV and make the A/D converter operational without Burst mode.
	ADC->CR |= ADC_CLKDIV << 8;
	ADC->CR &= ~(1 << 16);
	//Make the A/D converter operational
	ADC->CR |= (1 << 21);
	
	//Configure CR SEL bits for sampled and converting corresponding pin.
	ADC-> CR &= ~(1);
	ADC->CR |= (1 << channel);
	//Enable interrupt for corresponding pin.
	ADC->INTEN |= (1 << channel);
	//Enable ADC_IRQn (Interrupt Request).
	NVIC_EnableIRQ(ADC_IRQn);
	NVIC_ClearPendingIRQ(ADC_IRQn);
}

void ADC_Start () {
	//Write a code for starting A/D conversion on a rising edge on the TIMER 0 MATCH 1.
	ADC->CR |= 4 << 24;
}

uint32_t ADC_GetLastValueLeft() {
	ADC_New_Data_Available_Left = 0;
	return ADC_Last_Left;
}

uint32_t ADC_GetLastValueRight() {
	ADC_New_Data_Available_Right = 0;
	return ADC_Last_Right;
}

uint32_t ADC_GetLastValueTrimpot() {
	ADC_New_Data_Available_Trimpot = 0;
	return ADC_Last_Trimpot;
}
void ADC_IRQHandler() {
	ADC->GDR &= ~((uint32_t)1 << 31);
	
	//Write the converted data (only the converted data) to ADC_Last variable.
	ADC_Last_Left = (ADC->DR[3] >> 4) & (0xFFF); 
	ADC_Last_Right = (ADC->DR[2] >> 4) & (0xFFF); 
	ADC_Last_Trimpot = (ADC->DR[1] >> 4) & (0xFFF); 
	
	ADC_New_Data_Available_Left = 1;
	ADC_New_Data_Available_Right = 1;
	ADC_New_Data_Available_Trimpot = 1;
}
