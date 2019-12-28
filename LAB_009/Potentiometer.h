#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"

//Write the IOCON address of Analog Pin P0.24  ADC0.1
#define	POTENTIOMETER_IOCON_ADDRESS	0x4002C060
#define POTENTIOMETER_IOCON	*((volatile uint32_t*)(POTENTIOMETER_IOCON_ADDRESS))
#define POTENTIOMETER_CHANNEL 1
#define POTENTIOMETER_IOCON_FUNC 1

void Potentiometer_Init(void);
uint32_t Read_Potentiometer(void);

#endif
