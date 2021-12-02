/*
 * File:   uart.h
 * Author: Jennifer L. Krueger, Fabian Zaremba
 * IDE: MPLAB X v5.5
 * Compiler: XC8 v2.32
 * Target device: PIC18F4520
 * Header for: uart.c
 */

#include <stdint.h>

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef VOLTMETER_HEADER_UART_H
#define VOLTMETER_HEADER_UART_H

void putch(unsigned char data);
void init_uart_baud(uint32_t baudrate);
void init_uart(void);

#endif /* VOLTMETER_HEADER_UART_H */