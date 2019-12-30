#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Timer.h"

//Write IOCON Register Address of Trigger Pin.
#define IOCON_TRIGGER_ADDRESS	0x4002C024
#define IOCON_TRIGGER	*((volatile uint32_t*)(IOCON_TRIGGER_ADDRESS))

//Write IOCON Register Address of Echo Pin.
#define IOCON_ECHO_ADDRESS	0x4002C05C
#define IOCON_ECHO	*((volatile uint32_t*)(IOCON_ECHO_ADDRESS))

#define WINDOW_SIZE 3

typedef int32_t sensor_data_t;

extern const uint32_t dataSize;
extern sensor_data_t sensorData[];
extern uint32_t pointer;
	
extern uint32_t ultrasonicSensorRisingCaptureTime;
extern uint32_t ultrasonicSensorFallingCaptureTime;
extern uint32_t ultrasonicSensorDistance;
extern uint8_t ultrasonicSensorNewDataAvailable;

extern uint8_t ultrasonicSensorTriggerStart;
extern uint8_t ultrasonicSensorCaptureRisingEdge;

void Ultrasonic_Init(void);
void Ultrasonic_Trigger_Timer_Init(void);
void Ultrasonic_Capture_Timer_Init(void);

void Ultrasonic_Start_Trigger_Timer(void);

uint32_t Read_Distance();
uint32_t Read_Difference();
#endif
