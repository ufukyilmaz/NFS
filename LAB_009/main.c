#include "LPC407x_8x_177x_8x.h"

#include "Car.h"
#include "Library/Ultrasonic.h"

void init() {
	//Ultrasonic_Init();
	//Ultrasonic_Trigger_Timer_Init();
	//Ultrasonic_Capture_Timer_Init();
	Car_Init();
	//Ultrasonic_Start_Trigger_Timer();
}

void update() {
	Car_Execute();
}

int main() {
	init();
	while(1) {
		update();
	}
}
