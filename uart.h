// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef VOLTMETER_HEADER_UART_H
#define	VOLTMETER_HEADER_UART_H

void putch(unsigned char data);
void init_uart_baud(uint32_t baudrate);
void init_uart(void);

#endif	/* VOLTMETER_HEADER_UART_H */