#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 8000000UL
ISR (INT0_vect) // Interrupt Service Routine 
{
	for (int i =0; i<10; i++)
	{
		PORTB = 0x00; 
		_delay_ms(800);
		PORTB = 0xFF; 
		//_delay_ms(800);


	}
}

int main(void)
{
	DDRB = 0xFF; 

	EIMSK = 0x01; 
	EIFR = 0x01; 
	EICRA = 0x03; 
		sei(); 

		while(1) // create loop 
		{
			PORTB = 0x00; 
			_delay_ms(8000); // delay 1 ms LED OFF 
			PORTB = 0xFF;	// LED on


		}

}