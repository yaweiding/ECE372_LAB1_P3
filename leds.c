/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"

#define OUTPUT 0
#define INPUT 1
void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
  
    TRISGbits.TRISG12=OUTPUT;//run led
    TRISGbits.TRISG14=OUTPUT;//stop led
    
    
        LATGbits.LATG12=1;
        LATGbits.LATG14=1;
}
/*make LATG to logic low to produce differece voltage to light led */
void turnOnLED(int led){
    if(led==1)// RUN LED LIGHT
    {  
        LATGbits.LATG12=0;
        LATGbits.LATG14=1;
       
 
    }  
    if(led==2)// STOP LED LIGHT
    {
   
        LATGbits.LATG12=1;
        LATGbits.LATG14=0;
    }
}
