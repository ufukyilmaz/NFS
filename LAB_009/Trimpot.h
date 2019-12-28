#ifndef TRIMPOT_H
#define TRIMPOT_H

#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"

//Write the IOCON address of Analog Pin P0.24  ADC0.1
#define	TRIMPOT_IOCON_ADDRESS	0x4002C060
#define TRIMPOT_IOCON	*((volatile uint32_t*)(TRIMPOT_IOCON_ADDRESS))
#define TRIMPOT_CHANNEL 1
#define TRIMPOT_IOCON_FUNC 1

void Trimpot_Init(void);
uint32_t Read_Trimpot(void);

#endif
