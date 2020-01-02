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
uint32_t Left_LDR = 900, Right_LDR = 900, Speed = 90, Logger = 0, status = 0;
int32_t Sonar_Distance = 25;
double Sonar_Difference = 0, Error = 0;

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
	HM10_SendCommand("TESTING\r\n");
}

void Car_Forward(int speed){
	LEDS_Forward();
	Motor_Forward(speed);
	STATUS = FORWARD;
}

void Car_Forward_Auto(int speed, int turn){
	LEDS_Forward();
	STATUS = FORWARD;
	
	if(Turn_Counter >=  turn){
		Turn_Counter = 0;
		status  = 5;
	} else {
			Motor_Forward(speed);
	}
}

void Car_Backward(int speed){
	LEDS_Backward();
	Motor_Backward(speed);
	STATUS = BACKWARD;
}

void Car_Right(int speed, int turn){
	LEDS_Right();
	STATUS = RIGHT;

	if(Turn_Counter >= turn){
		if(MODE == TEST)
			Car_Stop();
		else
			Car_Forward(Speed);
	} else {
		Motor_Right(speed);	
	}
}

void Car_Right_Auto(int speed, int turn){
	LEDS_Right();
	STATUS = RIGHT;

	if(Turn_Counter >= turn){
		Turn_Counter = 0;
		status  = 5;
	} else {
		Motor_Right(speed);
	}
}

void Car_Left(int speed, int turn){
	LEDS_Left();
	STATUS = LEFT;

	if(Turn_Counter >= turn){
		if(MODE == TEST)
			Car_Stop();
		else
			Car_Forward(Speed);
	} else {
		Motor_Left(speed);
	}
}

void Car_Left_Auto(int speed, int turn){
	LEDS_Left();
	STATUS = LEFT;

	if(Turn_Counter >= 3 * turn){
		Turn_Counter = 0;
		status  = 5;
	} else if(Turn_Counter >= turn){
		Car_Forward(Speed);
	} else {
		Motor_Left(speed);
	}
}

void Car_Auto(int leftSpeed, int rightSpeed){
	if(leftSpeed >  70 && rightSpeed > 70)
		LEDS_Forward();
	else if(leftSpeed > 70)
		LEDS_Right();
	else if(rightSpeed > 70)
		LEDS_Left();
	
	Motor_Auto(leftSpeed, rightSpeed);
	STATUS = FORWARD;
}
void Car_Stop(){
	LEDS_Off();
	Motor_Stop();
}

void Execute_Test_Mode(){
	if(Left_LDR < 650 || Right_LDR < 650){
		Car_Stop();
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
				Car_Right(Speed, 6);
				break;
			case LEFT:
				Car_Left(Speed, 6);
				break;
		}
	}
}

void Execute_Auto_Mode(){
	if(STATUS != STOPPED){
		if(Left_LDR < 650 || Right_LDR < 650){
			if(Logger == 0){
				Car_Stop();
				HM10_SendCommand("FINISH\r\n");
				STATUS = STOPPED;
				Logger = Logger + 1;
			}
		} else if(Sonar_Distance < 10){
				if(Sonar_Difference > 0){
					Car_Auto(60, 40);
				}else{
					Car_Auto(100, -10);
				}
		} else if(Sonar_Distance < 20 ){
			if(Sonar_Difference > 0){
					Car_Auto(50, 50);
				}else{
					Car_Auto(100, 30);
				}
		}	else if(Sonar_Distance > 35){
			if(Sonar_Difference>=0){
				Car_Auto(10, 100);
			}
			else{
					Car_Auto(30, 30);
			}
		}else if( Sonar_Distance > 25 ){
			if(Sonar_Difference >= 0){
					Car_Auto(25, 100);		
				}else{
					Car_Auto(45, 45);
				}
		} 
		else { 
			Car_Auto(90, 90);
		}
	}
}

void Car_Execute(){	
	Sonar_Distance = Read_Distance();
	Error =  Sonar_Distance - 25;
	Sonar_Difference = (Read_Difference(12) + Read_Difference(6)) * 0.5;
	Left_LDR = Read_Left_LDR();
	Right_LDR = Read_Right_LDR();
	Speed = Read_Potentiometer();
	
	if(HM10NewDataAvailable){
		if(MODE == TEST){
			if(strcmp("STOP\r\n", HM10Buffer) == 0){
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
					STATUS = STOPPED;
					MODE = AUTO;
					Logger = 0;
			} else if(strcmp("STATUS\r\n", HM10Buffer) == 0){
					char stat[256];
					HM10_ClearBuffer();
					sprintf(stat, "STATUS\r\n{\"distance\":%d,\"light_level_left\":%d,\"light_level_right\":%d,\"op_mode\":\"TEST\"}\r\n", Sonar_Distance, Left_LDR, Right_LDR);
					
					HM10_SendCommand(stat);
			} else {
				HM10_ClearBuffer();
			}
		} else if(MODE == AUTO){
			if(strcmp("START\r\n", HM10Buffer) == 0){
					HM10_ClearBuffer();
					HM10_SendCommand("STARTING\r\n");
					STATUS = FORWARD;
			} else if(strcmp("TEST\r\n", HM10Buffer) == 0){
					HM10_ClearBuffer();	
					HM10_SendCommand("TEST\r\nTESTING\r\n");
					STATUS = STOPPED;
					MODE = TEST;
			} else if(strcmp("STATUS\r\n", HM10Buffer) == 0){
					char stat[256];
					HM10_ClearBuffer();
					sprintf(stat, "STATUS\r\n{\"distance\":%d,\"light_level_left\":%d,\"light_level_right\":%d,\"op_mode\":\"AUTO\"}\r\n", Sonar_Distance, Left_LDR, Right_LDR);

					HM10_SendCommand(stat);
			} else {
				HM10_ClearBuffer();
			}
		}
	}
		
	if(MODE == TEST)
		Execute_Test_Mode();
	else
		Execute_Auto_Mode();
}
