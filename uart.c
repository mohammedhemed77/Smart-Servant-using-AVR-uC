/*
uart library to interface AVR UART Module 
mohammed hemed
*/
#include "uart.h"
void uart_init (unsigned int baud)
{
	unsigned int UBBR  ;
	/*
	baud rate configuration :
	lrint is a function to approximiate the number 
	*/
	UBBR = lrint(F_CPU / (8L * baud)) -1  ; 
	UBRRH = (unsigned char)(UBBR>>8);
	UBRRL = (unsigned char)UBBR;
	/*Double speed mode */
	UCSRA |= (1<<U2X) ; 
	/*Enable Rx - Tx - Enable interrupt */
	UCSRB |=(1<<RXCIE) |(1<<TXCIE)|(1<<UDRIE)|(1<<RXEN)|(1<<TXEN) ;
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

void uart_send_byte (const unsigned char byte) {
while (!(UCSRA & (1<<TXC))) ; 
UDR = byte ; 
} 

unsigned char uart_rec_byte  (void) 
{
while (!(UCSRA & (1<<RXC))) ;
return UDR ; 
}

void uart_send_string (const unsigned char *str)  
{
unsigned char i = 0 ; 
while (str [i] != '\0')
{
uart_send_byte (str[i]) ; 
i++ ; 
}
}

void uart_rec_string (unsigned char *str) 
{
unsigned char i = 0 ;
str[i] = uart_rec_byte() ;
while (str [i] != '#') 
{
i++ ;
str [i] = uart_rec_byte ();

}
str[i] = '\0' ; 
}
