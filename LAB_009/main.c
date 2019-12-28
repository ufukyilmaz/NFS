#include "LPC407x_8x_177x_8x.h"

#include "Car.h"

void init() {
	Car_Init();
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
