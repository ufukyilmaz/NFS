#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "External.h"
#include "Library/SystemStructures.h"

#include "LPC407x_8x_177x_8x.h"

void Speedometer_Init(void);

//Write IOCON Register Address of Trigger Pin.
#define IOCON_TRIGGER_ADDRESS	0x4002C024
#define IOCON_TRIGGER	*((volatile uint32_t*)(IOCON_TRIGGER_ADDRESS))

extern uint8_t speedometerSensorCaptureRisingEdge;
#endif


