/*
 Name : Suraj Roy
 Date : 10/10/2022
 Description : Implement a message display using UART and CLCD 
 */

#ifndef UART_H
#define	UART_H

#define FOSC                20000000

void init_uart(unsigned long baud);
unsigned char getchar(void);
void putchar(unsigned char data);
void puts(const char *s);

#endif	/* UART_H */