#ifndef MOTOR_H
#define MOTOR_H

#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"

// P1.2 PWM0[1]
#define IOCON_MOTOR1_ADDRESS 0x4002C088
#define IOCON_MOTOR1 *((volatile uint32_t *) IOCON_MOTOR1_ADDRESS)
#define IOCON_MOTOR1_FUNC 0x3
#define MOTOR1_PWM_CHANNEL 1
#define MOTOR1_PWM_TYPE 0

// IN1 PIN
#define IN1_PORT PORT1
#define IN1_MASK ((uint32_t) 1 << 30)

// IN2 PIN
#define IN2_PORT PORT1
#define IN2_MASK ((uint32_t) 1 << 31)

// P1.3 PWM0[2]
#define IOCON_MOTOR2_ADDRESS 0x4002C08C
#define IOCON_MOTOR2 *((volatile uint32_t *) IOCON_MOTOR2_ADDRESS)
#define IOCON_MOTOR2_FUNC 0x3
#define MOTOR2_PWM_CHANNEL 2
#define MOTOR2_PWM_TYPE 0

// IN3 PIN
#define IN3_PORT PORT0
#define IN3_MASK ((uint32_t) 1 << 4)

// IN4 PIN
#define IN4_PORT PORT0
#define IN4_MASK ((uint32_t) 1 << 5)

void Motor_Init(void);
void Motor_Stop(void);
void Motor_Forward(int speed);
void Motor_Backward(int speed);
void Motor_Left(int speed);
void Motor_Left_Half(int speed);
void Motor_Right(int speed);
void Motor_Right_Half(int speed);

void PWM_Motor_Config(uint32_t T);
#endif
