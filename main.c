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
#include "switch.h"
#define delay5 5 //delay 5ms debounce 
#define PRESS 0
#define RELEASE 1
// ******************************************************************************************* //
  typedef enum stateTypeEnum {
      run, stop, debouncer
 
} stateType;
volatile stateType state, nextState; 
volatile int COUNT;
volatile int RESET;

int main(void)
{   
    
    enableInterrupts();
    initTimer1();
    initTimer2();
    initLCD();
    initSW1();
    initSW2();
    initLEDs();
    
    COUNT=0;//count time
    RESET=0; //check if reset button is being pressed
    char s[10];
    state = run;
 
    while(1)
    {
        switch(state){
            case (run):
                turnOnLED(2);
                moveCursorLCD(0,0);// first line print string
                printStringLCD("Running:");
                getTimeString(COUNT,s);// every time count++ 10ms
                moveCursorLCD(1,0);// second line print string
                printStringLCD(s);
                nextState = stop;
                break;
            case (stop):
                turnOnLED(1);
                moveCursorLCD(0,0);
                printStringLCD("Stopped:");
                getTimeString(COUNT, s);
                printStringLCD(s);
                if (RESET != 1){
                    nextState = run;
                }
                break;
            case (debouncer):
                if(stopButton == RELEASE || resetButton == RELEASE){
                    state = nextState;
                }
                break;
            default:
                state = run;
                break;
        }
              
        
    }

    
    return 0;
}
void __ISR(_TIMER_1_VECTOR, IPL3SRS)_T1Interrupt() {
    IFS0bits.T1IF = 0;
     
    if(state == run)
    {
       COUNT=COUNT+1;
    }
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
//    //TODO: Implement the interrupt to capture the press of the button
//
    IFS1bits.CNGIF = 0;
    IFS1bits.CNDIF = 0;
    int dummysw13 = stopButton;
    int dummysw6 = resetButton;
    
    delayMs(5); // delay 5ms
    
    if(resetButton == PRESS && state == stop){
        state = debouncer;
        nextState = stop;
        COUNT = 0;
    }
    if(resetButton == PRESS){
        RESET = 1;
    }
    else if (stopButton == RELEASE && RESET != 1){
        state = debouncer;
    }
    else if(resetButton == RELEASE){
        RESET = 0;
    }
}