/*
 * HemedBot.c
 *
 * Created: 29/03/2018 10:27:36 م
 * Author : Hemed
 */ 

#include "avr_config.h"
#include "uart.h"
#include "ext_int_config.h"
volatile unsigned char recieved_data = 0 ;
volatile unsigned char transmit_data = 0 ;

int main(void)
{
	/* make eyes of hemedBot as output */
        DDRB |= (1<<PB0)|(1<<PB1) | (1<<PB2);
	/* make PD7 output */
	DDRD |=1<<PD6;
	PORTB = 0x00 ; 
	uart_init(9600);
	/* External interrupt configuration */
	setIntPins(INT0);
	enableSpecificExternalINT(INT0);
	setIntMode(INT0,LOW);
	setIntPins(INT1);
	enableSpecificExternalINT(INT1);
	setIntMode(INT1,LOW); 
	// enable global interrupt 
	sei();                                 
	
	while (1) 
	{
	if (recieved_data == '1')				PORTB |= (1<<PB1) | (1<<PB2);
	else if (recieved_data == '0')			PORTB &= (0xf9);  
	else if (recieved_data == '2')		
	{
	for (sint8 a=0 ; a<50; a++)
	{
	PORTB ^= 1<<PB0 ;
	_delay_ms(200);
	}
	}
	else if (recieved_data == '3')
	{
		for (sint8 a=0 ; a<50; a++)
		{
			PORTB ^= 1<<PB0 ;
			PORTB ^= 1<<PB1 ;
			PORTB ^= 1<<PB2 ;
			
			_delay_ms(200);
		}
	PORTB = 0x00; 
	}
	/* Turn off buzzer */
	else if(recieved_data == '9')			PORTB &=(~(1<<PB0)) ;	
	}
			 
	}


	
 


ISR (USART_UDRE_vect)
{
	UDR = transmit_data;
	//PORTB ^= 1<<PB1 ; 			// Led indicator change its state when send
}


// This is interrupt service routine for recieving one character
// ----------------------------------------------------------------
ISR (USART_RXC_vect)
{
	recieved_data = UDR ;
	//PORTB ^= 1<<PB2 ;			// Led indicator change its state when Recieve
}

/* Wake up Button */
ISR(INT0_vect){
PORTD |= 1<<PD6 ; 	
}

/* Sleep Button */
ISR(INT1_vect){
	cli();
	PORTD &= (~(1<<PD6));
	/*Enable sleep mode bit */
	MCUCR |=(1<<SE);
	sei();
	/*power down sleep mode */
	MCUCR |=(1<<SM1);
	asm ("sleep");
	/*disable sleep mode bit */
	MCUCR &=(~(1<<SE));

}
