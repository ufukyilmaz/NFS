#include "LDR.h"
#include "ADC.h"

void LDR_Init(){
	ADC_Init(&LDR_RIGHT_IOCON, LDR_RIGHT_IOCON_FUNC, LDR_RIGHT_CHANNEL);
	ADC_Init(&LDR_LEFT_IOCON, LDR_LEFT_IOCON_FUNC, LDR_LEFT_CHANNEL);
	
	ADC_Start();
}

uint32_t Read_Left_LDR(){
	while(!ADC_New_Data_Available_Left);
	return ADC_GetLastValueLeft() * 1023 / 0xFFF;
}

uint32_t Read_Right_LDR(){
	while(!ADC_New_Data_Available_Right);
	return ADC_GetLastValueRight() * 1023 / 0xFFF;	
}


