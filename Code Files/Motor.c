#include "Motor.h"
#include "Library/GPIO.h"
#include "PWM.h"

void Motor_Init() {
	PWM_Init(MOTOR1_PWM_TYPE, &IOCON_MOTOR1, IOCON_MOTOR1_FUNC, PWM0_PCONP, MOTOR1_PWM_CHANNEL);
	PWM_Init(MOTOR2_PWM_TYPE, &IOCON_MOTOR2, IOCON_MOTOR2_FUNC, PWM0_PCONP, MOTOR2_PWM_CHANNEL);

	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);
	
	Motor_Stop();
}

void Motor_Stop(){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	GPIO_PIN_Write(IN3_PORT, IN3_MASK, LOW);
	GPIO_PIN_Write(IN4_PORT, IN4_MASK, LOW);
	
	PWM_Motor_Config(0);
}

void Motor_Forward(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	GPIO_PIN_Write(IN3_PORT, IN3_MASK, HIGH);
	GPIO_PIN_Write(IN4_PORT, IN4_MASK, LOW);
	PWM_Motor_Config(speed);
}

void Motor_Backward(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH);
	
	GPIO_PIN_Write(IN3_PORT, IN3_MASK, LOW);
	GPIO_PIN_Write(IN4_PORT, IN4_MASK, HIGH);
	PWM_Motor_Config(speed);
}

void Motor_Left(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH);

	GPIO_PIN_Write(IN3_PORT, IN3_MASK, HIGH);
	GPIO_PIN_Write(IN4_PORT, IN4_MASK, LOW);	
	PWM_Motor_Config(speed);
}

void Motor_Right(int speed){
	GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH);
	GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	
	GPIO_PIN_Write(IN3_PORT, IN3_MASK, LOW);
	GPIO_PIN_Write(IN4_PORT, IN4_MASK, HIGH);
	PWM_Motor_Config(speed);
}

void Motor_Auto(int leftSpeed, int rightSpeed){
	if(leftSpeed < 0){
		GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
		GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH);
		leftSpeed = leftSpeed * -1;
	} else{
		GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH);
		GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	}
	
	if(rightSpeed < 0){
		GPIO_PIN_Write(IN3_PORT, IN3_MASK, LOW);
		GPIO_PIN_Write(IN4_PORT, IN4_MASK, HIGH);
		rightSpeed = rightSpeed * -1;
	} else{
		GPIO_PIN_Write(IN3_PORT, IN3_MASK, HIGH);
		GPIO_PIN_Write(IN4_PORT, IN4_MASK, LOW);
	}
	
	PWM_Write(MOTOR1_PWM_TYPE, MOTOR1_PWM_CHANNEL, leftSpeed);
	PWM_Write(MOTOR2_PWM_TYPE, MOTOR2_PWM_CHANNEL, rightSpeed);
}

void PWM_Motor_Config(uint32_t T){
	PWM_Write(MOTOR1_PWM_TYPE, MOTOR1_PWM_CHANNEL, T);
	PWM_Write(MOTOR2_PWM_TYPE, MOTOR2_PWM_CHANNEL, T);
}
