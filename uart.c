/*
 * File:   uart.c
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 *
 * Created on 1. Dezember 2021, 09:16
 */

#include "config.h"
#include <stdint.h>

// From https://microchipdeveloper.com/xc8:console-printing
void putch(unsigned char data) {
  while (!PIR1bits.TXIF) {
    // Waiting for current transmission to complete
    continue;
  }
  TXREG = data;
}

// Independent initalization, enough for simulated UART output console according
// to Microchip documentation
void init_uart(void) {
  TRISCbits.RC7 = 1; // Pins of USART are multiplexed with PORTC, set according to datasheet
  TRISCbits.RC6 = 1; // Pins of USART are multiplexed with PORTC, set according to datasheet

  TXSTAbits.TXEN = 1; // Enable transmission
  RCSTAbits.SPEN = 1; // Enable serial port (configures RX/DT and TX/CK pins as
                      // serial port pins)
}

// Initializes UART for physical connections with specified baudrate
// TODO: Untested because of lack of physical hardware
void init_uart_baud(uint32_t baudrate) {
  uint16_t reg =
      (uint16_t)_XTAL_FREQ / (4 * (baudrate + 1)); // Formula from datasheet: F-OSC / (4*(n+1))

  TXSTAbits.BRGH = 1; // Setting High Baud Rate
  TXSTAbits.SYNC = 0; // Setting Asynchronous Mode, ie UART

  BAUDCONbits.BRG16 = 1; // Use 16-bit Baud Rate Generator instead of compatibility mode

  SPBRGH = reg >> 8;    // Set high byte by right shifting 8 bits
  SPBRG = reg & 0x00FF; // Set low byte by masking to get right 8 bits

  init_uart();
}
