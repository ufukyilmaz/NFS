#include "Trimpot.h"
#include "ADC.h"

void Trimpot_Init() {
	ADC_Init(&TRIMPOT_IOCON, TRIMPOT_IOCON_FUNC, TRIMPOT_CHANNEL);
}

uint32_t Read_Trimpot(){
	while(!ADC_New_Data_Available_Trimpot);
	return ADC_GetLastValueTrimpot() * 100 / 0xFFF;
}
