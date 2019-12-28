#ifndef LED_H
#define LED_H

#include "LPC407x_8x_177x_8x.h"
#include "PWM.h"

#define LED1_PORT			PORT1
#define LED1_MASK			((uint32_t) 1 << 6)

#define LED2_PORT			PORT0
#define LED2_MASK			((uint32_t) 1 << 23)

#define LED3_PORT			PORT1
#define LED3_MASK			((uint32_t) 1 << 23)

#define LED4_PORT			PORT1
#define LED4_MASK			((uint32_t) 1 << 24)

#define IOCON_LED_ADDRESS 	0x4002C0D0
#define IOCON_LED	*((volatile uint32_t*)(IOCON_LED_ADDRESS))
#define IOCON_LED_FUNC  0x2
#define LED_PWM_CHANNEL 2
#define LED_PWM_TYPE 1

void LED_Init(void);
void LEDS_Init(void);

void LEDS_Off(void);
void LEDS_On(void);

void LEDS_Forward(void);
void LEDS_Backward(void);
void LEDS_Left(void);
void LEDS_Right(void);

void PWM_Config(uint32_t T, uint32_t R);

void LED1_Off(void);
void LED2_Off(void);
void LED3_Off(void);
void LED4_Off(void);

void LED1_On(void);
void LED2_On(void);
void LED3_On(void);
void LED4_On(void);
#endif
