#ifndef PWM_H
#define PWM_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"

//Correctly define PWM_TypeDef struct.
typedef struct {
    volatile uint32_t MR0;
    volatile uint32_t MR1;
    volatile uint32_t MR2;
    volatile uint32_t MR3;
    uint32_t RESERVED0;
    volatile uint32_t LER;
} PWM_TypeDef;

//0x00000000 is a dummy value, write the correct address
#define IOCON_LED_ADDRESS    0x00000000
#define IOCON_LED    *((volatile uint32_t*)(IOCON_LED_ADDRESS))

#define PWM0_BASE    0x40014000
#define PWM1_BASE    0x40018000

#define PWM0    ((PWM_TypeDef*) PWM0_BASE)
#define PWM1    ((PWM_TypeDef*) PWM1_BASE)

void PWM_Init(void);

void PWM_Cycle_Rate(uint32_t period_In_Cycles);

void PWM_Write(uint32_t T_ON);

#endif