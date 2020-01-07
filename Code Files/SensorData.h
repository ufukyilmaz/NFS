#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "LPC407x_8x_177x_8x.h"

#define WINDOW_SIZE 3

typedef int32_t sensor_data_t;

const uint32_t dataSize = 21;
sensor_data_t sensorData[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32_t pointer = 0;
	
#endif
