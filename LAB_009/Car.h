#ifndef CAR_H
#define CAR_H

typedef enum {
	STOPPED,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
} Car_Status;

typedef enum {
	AUTO,
	TEST
} Operation_Mode;

#define LDR_THRESHOLD 650
#define CAR_TEST_TURN_COUNT 6

void Car_Init(void);
void Car_Forward(int speed);
void Car_Backward(int speed);
void Car_Right(int speed, int turn);
void Car_Left(int speed, int turn);
void Car_Stop(void);

void Car_Execute(void);
#endif
