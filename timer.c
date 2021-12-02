/*
 * File:   timer.c
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 *
 * Created on 1. Dezember 2021, 13:05
 */

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

// Global tick counter for Bresenham Algorithm (imperfect single periods with
// zero cumulative error) This assumes 1 MHz clock speed with 4 MHz XTAL, saves
// external oscillators and configuration Idea from
// https://www.romanblack.com/one_sec.htm (License is public domain) Optimized
// version (constants divided by 2^6) can use uint16
uint16_t ticks = 0;

// Indicator to trigger ADC conversion and output to UART
// Set true to start first loop iteration with conversion
_Bool trigger_conversion = true;

// Counts seconds after starting the program
// Up to 2^16-1 = 65.535 seconds = 1.092,25 Minutes
// => About 18 hours can be counted before overflow
uint16_t seconds = 0;

void __interrupt() TMR1Int(void) {
  if (PIR1bits.TMR1IF != 1) {
    // return as Timer1 overflow did not happen here
    return;
  }
  PIR1bits.TMR1IF = 0; // Clear interrupt

  ticks += 1024; // Add 65.536/64 = 1.024 ticks to Bresenham total
  if (ticks >= 15625) {
    ticks -= 15625; // Subtract one second (1.000.000 Ticks / 64 = 15.625), this
                    // retains relative error
    seconds++;
    trigger_conversion = true; // trigger ADC conversion and output in next
                               // loop, keeps interrupt servicing short
  }
  return;
}

void init_timer(void) {
  // Interrupt settings
  PIE1bits.TMR1IE = 1; // Enable Timer0 interrupt
  INTCONbits.GIE = 1;  // Globally enable interrupt
  // found on https://stackoverflow.com/a/24541065
  RCONbits.IPEN = 1; // Do not use PIC16 compatibility mode, also enables
                     // interrupt system priority feature

  // Timer settings
  T1CON = 0;            // Reset Timer1 configuration
  T1CONbits.TMR1ON = 1; // Start timer
}