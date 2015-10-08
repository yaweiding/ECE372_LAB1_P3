/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <xc.h>
#include "switch.h"

void initSW1(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
      //TODO: Initialize switch 1
    
    TRISGbits.TRISG13=1;// Enable input for switch
    CNCONGbits.ON=1;       // Turn on CN device
    
    CNENGbits.CNIEG13 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNGIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNGIF = 0;         // Put Interrupt flag down
    IPC8bits.CNIP = (unsigned int)4;
    IPC8bits.CNIS = (unsigned int)4;
    
    CNPUGbits.CNPUG13=1;// Enable Interal Pull-up resistor
    
}
// initialize the reset switch   on board RD6
void initSW2(){
    //TODO: Initialize switch 1
    TRISDbits.TRISD6=1;// Enable input for switch
    CNCONDbits.ON=1;       // Turn on CN device
    
    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    IPC8bits.CNIP = 4;
    IPC8bits.CNIS = 5;
    
    CNPUDbits.CNPUD6=1;// Enable Interal Pull-up resistor
    
}