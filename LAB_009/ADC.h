#ifndef ADC_H
#define ADC_H

#include "LPC407x_8x_177x_8x.h"

#include "Library/SystemStructures.h"

typedef struct {
  volatile	uint32_t CR;
  volatile	uint32_t GDR;
						uint32_t RESERVED0;
  volatile	uint32_t INTEN;
  volatile	uint32_t DR[8];
  volatile	uint32_t STAT;
  volatile	uint32_t TRM;
} ADC_TypeDef;

#define ADC_CLOCK_FREQUENCY 1000000

//Write the max value of ADC.
#define ADC_MAX_VALUE 0xFFF

//Define a ADC_CLKDIV variable for given ADC_CLOCK_FREQUENCY.
#define ADC_CLKDIV 59

#define ADC_BASE	0x40034000
#define ADC	((ADC_TypeDef*) ADC_BASE)

extern uint32_t ADC_Last_Left;
extern uint32_t ADC_Last_Right;
extern uint32_t ADC_Last_Potentiometer;
extern uint8_t ADC_New_Data_Available_Left;
extern uint8_t ADC_New_Data_Available_Right;
extern uint8_t ADC_New_Data_Available_Potentiometer;

void ADC_Init(volatile uint32_t *IOCON, uint32_t IOCON_FUNC, uint32_t channel);
void ADC_Start(void);
void ADC_Stop(void);
uint32_t ADC_GetLastValueLeft(void);
uint32_t ADC_GetLastValueRight(void);
uint32_t ADC_GetLastValuePotentiometer(void);

#endif
