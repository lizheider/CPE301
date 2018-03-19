#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// 1 MHZ clock , 64 prescalar
	// set LED out port
	// set timer prescaler

	DDRB = 0xFF;
	PORTB = 0x10; // PortB.2

	TCCR1B = 0b00000011; // prescaler set to 64

	while (1)
	{
		if (TCNT1 >= 3905)
		{
			PORTB = PORTB ^ 0xFF; // toggle LED
			TCNT1 = 0; // Reset Counter
		}
	}
}

