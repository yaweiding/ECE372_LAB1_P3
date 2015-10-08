/* 
 * File:   timer.h
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#ifndef INITTIMER_H
#define	INITTIMER_H
void delayMs(unsigned int delay);
void delayUs(unsigned int delay);
void initTimer2();
void initTimer1();
void getTimeString(int timer, char *string );

#endif	/* INITTIMER_H */

