// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "leds.h"
#include "interrupt.h"
#define SW1 PORTGbits.RG13 //stop/run swith
#define SW2 PORTDbits.RD6            //? set which swith to use reset button
#define delay5 5 //delay 5ms debounce 
#define PRESS 0
#define RELEASE 1
// ******************************************************************************************* //
  typedef enum stateTypeEnum {
    ledrun, ledstop, waitRelease1, waitRelease2, waitReset, reset
 
} stateType;
volatile stateType state; 
volatile int COUNT;
void getTimeString(int timer, char *string )
{   //char *string;
    int FF;
    int SS;
    int MM;
    FF=timer%100;// mod(100) is 0.01s
    SS=(timer/100)%60; // mod(60) is 1s
    MM=(timer/100/60)%60; // 
    // sprintf write the formate data to string
    sprintf(string,"%02d:%02d:%02d",MM,SS,FF);
}
int main(void)
{   
    
    enableInterrupts();
    initSW1();
    initSW2();
    initTimer1();
    initTimer2();
    initLEDs();
    initLCD();
    COUNT=0;//count time
    char s[10];
    state = ledrun;
 
    while(1)
    {
        switch(state){
            case ledrun:
                turnOnLED(1);
                moveCursorLCD(0,0);// first line print string
                printStringLCD("Running:");
                getTimeString(COUNT,s);// every time count++ 10ms
                moveCursorLCD(1,0);// second line print string
                printStringLCD(s);
                break;
            case waitRelease1:
                
                if(SW1==PRESS)
                {
                    state=waitRelease1;
                }
                else if(SW1=RELEASE){
                    state=ledstop;
                }
                break;
            case ledstop:

                turnOnLED(2);
                moveCursorLCD(0,0);// first line print string
                printStringLCD("Stopped:");
                getTimeString(COUNT,s);// every time count++ 10ms
                moveCursorLCD(1,0);// second line print string
                printStringLCD(s);
                break;
            case waitRelease2:
                
                if(SW1==PRESS)
                {
                    state=waitRelease2;
                }
                else if(SW1=RELEASE){
                    state=ledrun;
                }
                break;
            case waitReset:
                if(SW2==PRESS)
                {
                    state=waitReset;
                }
                else if(SW2=RELEASE){
                    state=reset;
                }
            case reset:
                COUNT=0;
                turnOnLED(2);
                moveCursorLCD(0,0);// first line print string
                printStringLCD("Stopped:");
                getTimeString(COUNT,s);// every time count++ 10ms
                moveCursorLCD(1,0);// second line print string
                printStringLCD(s);
                break;
        }
              
        
    }

    
    return 0;
}
void __ISR(_TIMER_1_VECTOR, IPL3SRS)_T1Interrupt() {
    IFS0bits.T1IF = 0;
     
    if(state==ledrun)
    {
       COUNT=COUNT+1; 
    }
    
   
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
//    //TODO: Implement the interrupt to capture the press of the button
//
    IFS1bits.CNGIF=0;
    IFS1bits.CNDIF = 0; // resent press
    delayMs(5); // delay 5ms
    if(state==ledrun && SW1==PRESS){
        state=waitRelease1;
    }
    else if(state==ledstop && SW1==PRESS){
        state=waitRelease2;
    }
    else if (state==ledstop&& SW1==RELEASE && SW2==PRESS){
        state=waitReset;
    }
    else if(state==reset&&SW1==PRESS){
        state=waitRelease2;
    }
        
        
    
}


