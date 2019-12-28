#include "Motor.h"
#include "Library/GPIO.h"
#include "PWM.h"

void Motor_Init() {
	PWM_Init(MOTOR1_PWM_TYPE, &IOCON_MOTOR1, IOCON_MOTOR1_FUNC, PWM0_PCONP, MOTOR1_PWM_CHANNEL);

	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	
	Motor_Stop();
}

void Motor_Stop(){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	PWM_Motor_Config(0);
}

void Motor_Forward(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	PWM_Motor_Config(speed);
}

void Motor_Backward(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH);
	
	PWM_Motor_Config(speed);
}

void Motor_Left(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH);
	
	PWM_Motor_Config(speed);
}

void Motor_Right(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	PWM_Motor_Config(speed);
}

void PWM_Motor_Config(uint32_t T){
	PWM_Write(MOTOR1_PWM_TYPE, MOTOR1_PWM_CHANNEL, T);
}
