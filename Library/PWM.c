#include "PWM.h"

void PWM_Init() {
    //Change the function of the pin
    PWM_
    //Turn on PWM from PCONP register

    //Enable PWM output for corresponding pin.

    //Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK

    //Configure MR0 register for giving pulse every 20 ms.

    //Reset TC, when MR0 matches TC (Reset on MR0)

    //Enable PWM Match 0 Latch.

    //Enable Counter, Enable PWM and Clear Reset on the PWM

    PWM_Write(0);
}

void PWM_Cycle_Rate(uint32_t period_In_Cycles) {
    //Write a formula that changes the MR0 register value for a given parameter.
    //For example, if period_In_Cycles 20, configure MR0 register for giving pulse every 20 ms.
    //if period_In_Cycles 1000, configure MR0 register for giving pulse every 1000ms etc.

    PWM0->LER |= 1 << 0;
}

void PWM_Write(uint32_t T_ON) {
    if(T_ON > 100) {
        T_ON = 100;
    }

    //Write a formula to calculate the match register for Green LED.
    T_ON = PWM->MR0 * (T_ON / 100.0);
    //Store the value in T_ON variable again(T_ON = ???)

    if (T_ON == PWM0->MR0) {
        T_ON++;
    }


    PWM0->MR3 = T_ON;

    PWM0->LER |= 1 << 3;
}