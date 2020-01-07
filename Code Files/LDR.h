#ifndef LDR_H
#define LDR_H

#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"

//Write the IOCON address of Analog Pin P0.26  ADC0.3
#define	LDR_LEFT_IOCON_ADDRESS	0x4002C068
#define LDR_LEFT_IOCON	*((volatile uint32_t*)(LDR_LEFT_IOCON_ADDRESS))
#define LDR_LEFT_CHANNEL 3
#define LDR_LEFT_IOCON_FUNC 1

//Write the IOCON address of Analog Pin P0.25  ADC0.2
#define	LDR_RIGHT_IOCON_ADDRESS	0x4002C064
#define LDR_RIGHT_IOCON	*((volatile uint32_t*)(LDR_RIGHT_IOCON_ADDRESS))
#define LDR_RIGHT_CHANNEL 2
#define LDR_RIGHT_IOCON_FUNC 1

void LDR_Init(void);
uint32_t Read_Left_LDR(void);
uint32_t Read_Right_LDR(void);

#endif
