//
// Created by ufuky on 11.12.2019.
//

#ifndef CLK_H
#define CLK_H

#include "LPC407x_8x_177x_8x.h"

//0x00000000 and 0x000 are the dummby values. Write the correct values.
#define CLKSRCSEL_ADDRESS             0x400FC10C
#define CCLKSEL_ADDRESS               0x400FC104
#define PCLKSEL_ADDRESS               0x400FC1A8
#define EMCCLKSEL_ADDRESS             0x400FC100
#define USBCLKSEL_ADDRESS             0x400FC108
#define SPIFICLKSEL_ADDRESS           0x400FC1B4

#define CLKSRCSEL                     *((volatile uint32_t*)(CLKSRCSEL_ADDRESS))
#define CCLKSEL                       *((volatile uint32_t*)(CCLKSEL_ADDRESS))
#define PCLKSEL                       *((volatile uint32_t*)(PCLKSEL_ADDRESS))
#define EMCCLKSEL                     *((volatile uint32_t*)(EMCCLKSEL_ADDRESS))
#define USBCLKSEL                     *((volatile uint32_t*)(USBCLKSEL_ADDRESS))
#define SPIFICLKSEL                   *((volatile uint32_t*)(SPIFICLKSEL_ADDRESS))


#endif //NFS_CLK_H
