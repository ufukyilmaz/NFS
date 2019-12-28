#include "Potentiometer.h"
#include "ADC.h"

void Potentiometer_Init() {
	ADC_Init(&POTENTIOMETER_IOCON, POTENTIOMETER_IOCON_FUNC, POTENTIOMETER_CHANNEL);
}

uint32_t Read_Potentiometer(){
	while(!ADC_New_Data_Available_Potentiometer);
	return ADC_GetLastValuePotentiometer() * 100 / 0xFFF;
}
