#include "Ultrasonic.h"

uint32_t ultrasonicSensorRisingCaptureTime = 0;
uint32_t ultrasonicSensorFallingCaptureTime = 0;

uint32_t ultrasonicSensorDuration = 0;
uint32_t ultrasonicSensorDistance = 0;
uint32_t Distance = 0;

uint8_t ultrasonicSensorNewDataAvailable = 0;

uint8_t ultrasonicSensorTriggerStart = 0;
uint8_t ultrasonicSensorCaptureRisingEdge = 0;

uint32_t const dataSize = 3;
uint32_t sensorDataSample[] = {25, 25, 25,25, 25, 25,25, 25, 25,25, 25, 25,25, 25, 25,25, 25, 25,25, 25};
uint32_t sampleSize = 20;
uint32_t samplePointer = 0;
sensor_data_t sensorData[] = {25, 25, 25}; // , 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25};
uint32_t pointer = 0;

void Ultrasonic_Init() {
	IOCON_TRIGGER |= 0x03;
	IOCON_ECHO |= 0x03;
}

void Ultrasonic_Trigger_Timer_Init() {
	uint32_t temp;
	
	//Turn on Timer2.
	PCONP |= 1 << 22;	
	//Change the mode of Timer2 to Timer Mode.
	TIMER2->CTCR = 0x00;

	TIMER2->TCR &= ~(1 << 0);

	TIMER2->TCR |= (1 << 1);

	TIMER2->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000000 - 1;

	//Write the Correct Configuration for EMR (LOW output value of Trigger Pin when match occurs and Initial value is LOW)
	temp = TIMER2->EMR;
	temp &= ~(1 << 3);
	temp |= (1 << 10);
	TIMER2->EMR |= (1 << 3 | 1 << 10);

	NVIC_EnableIRQ(TIMER2_IRQn);
	
	NVIC_SetPriority(TIMER2_IRQn,5);
	
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
}

void Ultrasonic_Capture_Timer_Init() {
	//Turn on Timer3
	PCONP |= 1 << 23;	
	//Change the mode of Timer3 to Timer Mode
	TIMER3->CTCR = 0x00;
	
	TIMER3->TCR &= ~(1 << 0);
	
	TIMER3->TCR |= (1 << 1);
	
	//Change PR Register value for 1 microsecond incrementing
	TIMER3->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000000 - 1;
	
	//Change CCR value for getting Interrupt when Rising Edge Occur for CAP 0
	TIMER3->CCR |= (1 << 0  | 1 << 2);

	TIMER3->TCR &= ~(1 << 1);
	
	TIMER3->TCR |= (1 << 0);

	NVIC_EnableIRQ(TIMER3_IRQn);
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
}

void Ultrasonic_Start_Trigger_Timer() {
	//Change output value of Trigger Pin as HIGH
	TIMER2->EMR |= 1 << 3;

	//Give correct value to corresponding MR Register for 10 microsecond
	TIMER2->MR3 = 10;

	//Enable interrupt for MR3 register, if MR3 register matches the TC.
	TIMER2->MCR |= (1 << 9);
	
	//Remove the reset on counters of Timer2.
	TIMER2->TCR &= ~(1 << 1);

	//Enable Timer Counter and Prescale Counter for counting.
	TIMER2->TCR |= (1 << 0);
}

void TIMER2_IRQHandler() {
	//Write HIGH bit value to IR Register for Corresponding Interrupt
	TIMER2->IR = 1 << 3;

	if(ultrasonicSensorTriggerStart == 0) {
		//Change MR3 Register Value for Suggested Waiting
		TIMER2->MR3 = 60000 + TIMER2->TC;
		
		ultrasonicSensorTriggerStart = 1;
	}
	else {
		TIMER2->EMR |= (1 << 3);
		TIMER2->MR3 = 10 + TIMER2->TC;
		
		ultrasonicSensorTriggerStart = 0;
	}
}

void TIMER3_IRQHandler() {
	TIMER3->IR = 1 << 4;
	
	if(ultrasonicSensorCaptureRisingEdge == 1) {
		ultrasonicSensorRisingCaptureTime = TIMER3->CR0;
		
		LPC_TIM3->CCR = (1 << 1) | (1 << 2);
		ultrasonicSensorCaptureRisingEdge = 0;
	}
	else {
		ultrasonicSensorFallingCaptureTime = TIMER3->CR0;
		ultrasonicSensorNewDataAvailable = 1;
		sensorData[pointer%dataSize] = (ultrasonicSensorFallingCaptureTime - ultrasonicSensorRisingCaptureTime) / 58;
		pointer ++;
		LPC_TIM3->CCR = (1 << 0) | (1 << 2);
		ultrasonicSensorCaptureRisingEdge = 1;
	}
}

void bubbleSort(sensor_data_t* data) {
	uint8_t i, j;
	sensor_data_t temp;
	for(i=0; i<WINDOW_SIZE-1; i++) {
		for(j=i+1; j<WINDOW_SIZE; j++) {
			if(data[j] < data[i]) {
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

sensor_data_t median(sensor_data_t* data) {
	sensor_data_t sortedData[WINDOW_SIZE];
	uint8_t index;
	for(index=0; index<WINDOW_SIZE; index++) {
		sortedData[index] = data[index];
	}
	bubbleSort(sortedData);
	if(WINDOW_SIZE % 2 == 1) {
			return sortedData[WINDOW_SIZE/2];
	} else {
			return (sortedData[WINDOW_SIZE/2 - 1] + sortedData[WINDOW_SIZE/2]) / 2.0;
	}
}

int32_t Read_Distance(){
	sensorDataSample[samplePointer%sampleSize] = median(sensorData);   
	return sensorDataSample[(samplePointer++)%sampleSize];
}

int32_t Read_Difference(int edge){
	
	return sensorDataSample[((samplePointer-1) + sampleSize)%sampleSize]-sensorDataSample[((samplePointer-1) - edge + sampleSize)%sampleSize];
	
	//return median(sensorData);
}
