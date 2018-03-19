#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;	// Set PortB as an OUTPUT
	DDRD = 0x00;	// Set Port D as an INPUT
	
	while (1)
	{
		if((PIND&0b00000100)==0b00000100)
		{
			PORTB = 0xFF;		//LED on when pushbutton is pressed
			_delay_ms(1000);	//1 second delay, turn off LED after
		}
		
		else
		PORTB = 0x00;	//Turns off LED when button is not pressed.
	}
	return 0;
}
