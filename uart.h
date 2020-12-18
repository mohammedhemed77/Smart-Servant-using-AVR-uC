


#ifndef UART_H_
#define UART_H_ 

#include "avr_config.h"

void uart_init (unsigned int baud);

void uart_send_byte (const unsigned char byte) ; 

unsigned char uart_rec_byte  (void) ;  

void uart_send_string (const unsigned char *str) ; 

void uart_rec_string (unsigned char *str) ; 







#endif