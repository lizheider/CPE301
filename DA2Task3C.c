
// DA task 3 ASM
// Program to generate a waveform on PORTB.2 with 50% DC and 0.5 sec period
// (Toggle and LED at every 0.25 seconds for a total period of 0.5 seconds)
#include <avr/io.h>

int main(void) {

	unsigned char count = 0;		// count to keep track of timer0 overflows
	DDRB |= (1 << 2);			// connect LED to pin PB.2
	PORTB = 0;				// PB.2 LED is off

	while (1) {
		// set up Timer0 with prescaler = 64 and normal mode
		TCCR0A = 0;
		TCCR0B |= (1 << CS01)|(1 << CS00);
		
		TCNT0 = 0;				// initialize counter

		while( (TIFR0 & 0x1) == 0 ) ;	// wait until overflow flag is set
		TCCR0B = 0;				// stop/disable Timer 0
		TIFR0 |= 1;				// clear overflow flag
		if (count == 15)
		{
			PORTB ^= 0x04;		// toggle PB.2
			count = 0;			// reset counter
		}
		else
		count++;				// increment counter
	}
}


