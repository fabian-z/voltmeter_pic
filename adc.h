/*
 * File:   adc.h
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 * Header for: adc.c
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef VOLTMETER_HEADER_ADC_H
#define VOLTMETER_HEADER_ADC_H

void init_adc(void);
float read_adc(void);

#endif /* VOLTMETER_HEADER_ADC_H */
