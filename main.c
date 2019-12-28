#include "LPC407x_8x_177x_8x.h"

#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
//#include "Library/Timer.h"

void init() {
	//Ultrasonic_Init();
	//Ultrasonic_Trigger_Timer_Init();
	//Ultrasonic_Capture_Timer_Init();
	
	LED1_Init();
	LED2_Init();
	LED3_Init();
	LED4_Init();
	
	LED1_Off();
	LED2_Off();
	LED3_Off();
	LED4_Off();
	
	//Ultrasonic_Start_Trigger_Timer();
}

//Calculate distance from duration. (Also write the formula to paper)
//When Ultrasonic Sensor detects obstacles which are closer than 7cm, turn on all the LEDs.
//When Ultrasonic Sensor detects obstacles which are in the range of 7cm and 12cm , turn on LED1, LED2 and LED3.
//When Ultrasonic Sensor detects obstacles which are in the range of 12cm and 20cm , turn on LED1 and LED2.
//When Ultrasonic Sensor detects obstacles which are in the range of 20cm and 30cm , turn on LED1.
//When Ultrasonic Sensor detects obstacles which are far from 30 cm, turn off all the LEDs.

void update() {
	LED1_On();
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

