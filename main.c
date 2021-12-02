/*
 * File:   main.c
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 *
 * Created on 29. November 2021, 13:10
 */

#include "adc.h"
#include "config.h"
#include "timer.h"
#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void main(void) {
  init_uart();  // Initialize UART debug console
  init_adc();   // Initialize A/D converter
  init_timer(); // Initialize Timer1 with interrupts

  // Output settings (conversion indicator)
  TRISBbits.RB0 = 0; // Set PortB pin0 to output mode
  LATBbits.LB0 = 0;  // Default to no conversion in progress (logical 0)

  while (true) {
    if (!trigger_conversion) {
      continue;
    }
    trigger_conversion = false; // Reset trigger

    LATBbits.LB0 = 1;
    float val = read_adc();
    LATBbits.LB0 = 0;

    printf("\n%u: %.2f V\n", seconds, val);
  }

  return;
}