#include "Led.h"
#include "Library/GPIO.h"
#include "PWM.h"

void LED_Init(){
	LEDS_Init();
	
	PWM_Init(LED_PWM_TYPE, &IOCON_LED, IOCON_LED_FUNC, PWM1_PCONP, LED_PWM_CHANNEL);
	LEDS_Off();
}

void LEDS_Init() {
	//Write code for initializing LEDs.
	GPIO_DIR_Write(LED1_PORT,LED1_MASK,OUTPUT);
	GPIO_DIR_Write(LED2_PORT,LED2_MASK,OUTPUT);
	GPIO_DIR_Write(LED3_PORT,LED3_MASK,OUTPUT);
	GPIO_DIR_Write(LED4_PORT,LED4_MASK,OUTPUT);
}

void LEDS_Off() {
	//Write code for turning off all LEDs.
	LED1_Off();
	LED2_Off();
	LED3_Off();
	LED4_Off();
	
	PWM_Config(0, 20);
}

void LEDS_On() {
	//Write code for turning on all LEDs.
	LED1_On();
	LED2_On();
	LED3_On();
	LED4_On();
	
	PWM_Config(60, 20);
}

void LEDS_Forward() {
	//Write code for led config for moving forward.
	PWM_Config(60, 20);
	LED1_On();
	LED2_On();
	LED3_Off();
	LED4_Off();
}

void LEDS_Backward() {
	//Write code for led config for moving backward.
	PWM_Config(60, 20);
	LED1_Off();
	LED2_Off();
	LED3_On();
	LED4_On();
}

void LEDS_Left() {
	//Write code for led config for moving left.
	PWM_Config(60, 500);
	LED1_On();
	LED2_Off();
	LED3_On();
	LED4_Off();
}

void LEDS_Right() {
	//Write code for led config for moving right.
	PWM_Config(60, 500);
	LED1_Off();
	LED2_On();
	LED3_Off();
	LED4_On();
}

void PWM_Config(uint32_t T, uint32_t R){
	PWM_Cycle_Rate(LED_PWM_TYPE, R);
	PWM_Write(LED_PWM_TYPE, LED_PWM_CHANNEL, T);
}

void LED1_Off() {
	//Write code for turning off LED1.
	GPIO_PIN_Write(LED1_PORT,LED1_MASK,LOW);
}

void LED2_Off() {
	//Write code for turning off LED2.
	GPIO_PIN_Write(LED2_PORT,LED2_MASK,LOW);
}

void LED3_Off() {
	//Write code for turning off LED3.
	GPIO_PIN_Write(LED3_PORT,LED3_MASK,LOW);
}

void LED4_Off() {
	//Write code for turning off LED4.
	GPIO_PIN_Write(LED4_PORT,LED4_MASK,LOW);
}

void LED1_On() {
	//Write code for turning on LED1.
	GPIO_PIN_Write(LED1_PORT,LED1_MASK,HIGH);
}

void LED2_On() {
	//Write code for turning on LED2.
	GPIO_PIN_Write(LED2_PORT,LED2_MASK,HIGH);
}

void LED3_On() {
	//Write code for turning on LED3.
	GPIO_PIN_Write(LED3_PORT,LED3_MASK,HIGH);
}

void LED4_On() {
	//Write code for turning on LED4.
	GPIO_PIN_Write(LED4_PORT,LED4_MASK,HIGH);
}
