#include "Ultrasonic.h"

uint32_t ultrasonicSensorRisingCaptureTime;
uint32_t ultrasonicSensorFallingCaptureTime;

uint32_t ultrasonicSensorDuration = 0;
uint32_t ultrasonicSensorDistance = 0;
uint8_t ultrasonicSensorNewDataAvailable = 0;

uint8_t ultrasonicSensorTriggerStart = 0;
uint8_t ultrasonicSensorCaptureRisingEdge = 0;

void Ultrasonic_Init() {
	IOCON_TRIGGER |= 0x03;
	IOCON_ECHO |= 0x03;
}

void Ultrasonic_Trigger_Timer_Init() {
	//Turn on Timer2.
	
	//Change the mode of Timer2 to Timer Mode.
	
	TIMER2->TCR &= ~(1 << 0);
	
	TIMER2->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	
	//Write the Correct Configuration for EMR (LOW output value of Trigger Pin when match occurs and Initial value is LOW)
	
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	NVIC_SetPriority(TIMER2_IRQn, 5);
	
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
}

void Ultrasonic_Capture_Timer_Init() {
	//Turn on Timer3
	
	//Change the mode of Timer3 to Timer Mode
	
	TIMER3->TCR &= ~(1 << 0);
	
	TIMER3->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	
	//Change CCR value for getting Interrupt when Rising Edge Occur for CAP 1
	
	TIMER3->TCR &= ~(1 << 1);
	
	TIMER3->TCR |= (1 << 0);

	NVIC_EnableIRQ(TIMER3_IRQn);
}

void Ultrasonic_Start_Trigger_Timer() {
	//Change output value of Trigger Pin as HIGH
	
	//Give correct value to corresponding MR Register for 10 microsecond
	
	//Enable interrupt for MR3 register, if MR3 register matches the TC.
	
	//Remove the reset on counters of Timer2.
	
	//Enable Timer Counter and Prescale Counter for counting.
}

void TIMER2_IRQHandler() {
	//Write HIGH bit value to IR Register for Corresponding Interrupt
	
	if(ultrasonicSensorTriggerStart == 0) {
		//Change MR3 Register Value for Suggested Waiting
		
		ultrasonicSensorTriggerStart = 1;
	}
	else {
		TIMER2->EMR |= (1 << 3);
		TIMER2->MR3 = 10 + TIMER2->TC;
		
		ultrasonicSensorTriggerStart = 0;
	}
}

void TIMER3_IRQHandler() {
	TIMER3->IR = 1 << 5;
	
	if(ultrasonicSensorCaptureRisingEdge == 1) {
		ultrasonicSensorRisingCaptureTime = TIMER3->CR1;
		
		LPC_TIM3->CCR = (1 << 4) | (1 << 5);
		ultrasonicSensorCaptureRisingEdge = 0;
	}
	else {
		ultrasonicSensorFallingCaptureTime = TIMER3->CR1;
		ultrasonicSensorNewDataAvailable = 1;
		
		LPC_TIM3->CCR = (1 << 3) | (1 << 5);
		ultrasonicSensorCaptureRisingEdge = 1;
	}
}

