/*
 * File:   timer.h
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 * Header for: timer.c
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef VOLTMETER_HEADER_TIMER_H
#define VOLTMETER_HEADER_TIMER_H

extern _Bool trigger_conversion;
extern uint16_t seconds;

void __interrupt() TMR1Int(void);
void init_timer(void);

#endif /* VOLTMETER_HEADER_TIMER_H */
