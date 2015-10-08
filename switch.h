/* 
 * File:   switch.h
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */

#ifndef SWITCH_H
#define	SWITCH_H
#define stopButton PORTGbits.RG13
#define resetButton PORTDbits.RD6

void initSW1();
void initSW2();


#endif	/* SWITCH_H */

