#include "Car.h"
#include "Led.h"
#include "Motor.h"
#include "LDR.h"
#include "Timer.h"
#include "Potentiometer.h"
#include "HM10.h"
#include "External.h"
#include "Ultrasonic.h"

Car_Status STATUS;
Operation_Mode MODE;

void Car_Init(){
	External_Init();
	HM10_Init();
	LDR_Init();
	Timer_Init();
	Potentiometer_Init();
	LED_Init();
	Motor_Init();
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();	
	Ultrasonic_Start_Trigger_Timer();

	STATUS = STOPPED;
	MODE = TEST;
}

void Car_Forward(int speed){
	LEDS_Forward();
	Motor_Forward(speed);
	STATUS = FORWARD;
}

void Car_Backward(int speed){
	LEDS_Backward();
	Motor_Backward(speed);
	STATUS = BACKWARD;
}

void Car_Right(int speed){
	LEDS_Right();
	STATUS = RIGHT;

	if(Turn_Counter >= 12){
		Car_Stop();
	} else {
		Motor_Right(speed);	
	}
}

void Car_Left(int speed){
	LEDS_Left();
	STATUS = LEFT;

	if(Turn_Counter >= 12){
		Car_Stop();
	} else {
		Motor_Left(speed);
	}
}

void Car_Stop(){
	LEDS_Off();
	Motor_Stop();
}

void Car_Execute(){
	uint32_t Left_LDR, Rigth_LDR, Speed, Distance;
	
	Distance = Read_Distance();
	Left_LDR = Read_Left_LDR();
	Rigth_LDR = Read_Right_LDR();
	Speed = Read_Potentiometer();
	
	if(Distance < 15)
		STATUS = FORWARD;
	else if(Distance < 25)
		STATUS = BACKWARD;
	else if(Distance < 35)
		STATUS = LEFT;
	else
		STATUS = RIGHT;
	
	if(Left_LDR < 300 || Rigth_LDR < 300){
		Car_Stop();
		if(MODE == AUTO){
			HM10_SendCommand("FINISH\r\n");
			STATUS = STOPPED;
		}
	} else {
		switch (STATUS){
			case STOPPED:
				Car_Stop();
				break;
			case FORWARD:
				Car_Forward(Speed);
				break;
			case BACKWARD:
				Car_Backward(Speed);
				break;
			case RIGHT:
				Car_Right(Speed);
				break;
			case LEFT:
				Car_Left(Speed);
				break;
		}
	}
	
	if(HM10NewDataAvailable){
		if(strcmp("START\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("STARTING\r\n");
				STATUS = FORWARD;
		} else if(strcmp("STOP\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("STOP\r\n");
				STATUS = STOPPED;
		} else if(strcmp("FORWARD\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("FORWARD\r\n");
				STATUS = FORWARD;
		} else if(strcmp("BACK\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("BACK\r\n");
				STATUS = BACKWARD;
		} else if(strcmp("LEFT\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("LEFT\r\n");
				STATUS = LEFT;
				Turn_Counter = 0;
		} else if(strcmp("RIGHT\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("RIGHT\r\n");
				STATUS = RIGHT;
				Turn_Counter = 0;
		} else if(strcmp("AUTO\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();
				HM10_SendCommand("AUTO\r\nAUTONOMOUS\r\n");
				MODE = AUTO;
		} else if(strcmp("TEST\r\n", HM10Buffer) == 0){
				HM10_ClearBuffer();	
				HM10_SendCommand("TEST\r\nTESTING\r\n");
				MODE = TEST;
		} else if(strcmp("STATUS\r\n", HM10Buffer) == 0){
				char stat[256];
				HM10_ClearBuffer();
				if(MODE == TEST)
					sprintf(stat, "STATUS\r\n{\"distance\":%d,\"light_level_left\":%d,\"light_level_right\":%d,\"op_mode\":\"TEST\"}\r\n", Distance, Left_LDR, Rigth_LDR);
				else
					sprintf(stat, "STATUS\r\n{\"distance\":%d,\"light_level_left\":%d,\"light_level_right\":%d,\"op_mode\":\"AUTO\"}\r\n", Distance, Left_LDR, Rigth_LDR);

				HM10_SendCommand(stat);
		}
	}
}
