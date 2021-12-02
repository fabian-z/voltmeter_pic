/*
 * File:   adc.c
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 *
 * Created on 1. Dezember 2021, 09:14
 */

#include "config.h"
#include "adc.h"

// 5 Volts divided by (2^10-1) possible ADC steps 
// ADC_FACTOR = 5 / (2^10 - 1) = 0.004887585
// Conversion calculation therefore can be done with single precision (32 bit) floats
// since both ADC_FACTOR and the steps 0 - 2^10-1 can be represented without loss of precision
const float ADC_FACTOR = 0.004887585;

void init_adc(void) {
    // A/D Converter settings
    ADCON2bits.ADFM = 1; // right justify to use ADRES directly as 16bit unsigned int
    ADCON1bits.PCFG = 0b1110; // Use only AN0 as analog input
    ADCON0bits.CHS = 0b0000; // Select AN0 channel for conversion
    ADCON2bits.ACQT = 0b100; // Use 8 T-AD aquisition time (accuracy / speed tradeoff)
    ADCON2bits.ADCS = 0b100; // F-OSC/4, Datasheet Table 19-1, max. Frequency 5.71 MHz
    ADCON0bits.ADON = 1; // Enable A/D Converter Module
}

float read_adc(void) {
    ADCON0bits.GODONE = 1;
    while (ADCON0bits.GODONE == 1) {
        // Polling wait for finished conversion
        continue;
    }
    float adc = ADRES;
    return adc * ADC_FACTOR;
}