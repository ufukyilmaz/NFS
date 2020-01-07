#ifndef SYSTEM_STRUCTURES_H
#define SYSTEM_STRUCTURES_H

//Write the address of Power Control for Peripherals Register 
#define PCONP_ADDRESS	0x400FC0C4
#define PCONP	*((volatile uint32_t*)(PCONP_ADDRESS))

//Write PCLK Frequency
#define PERIPHERAL_CLOCK_FREQUENCY 0x3938700

#endif
