#include <avr/io.h>
#include <avr/interrupt.h>
// 8Mhz clock & 64 prescaler
// global variable for keeping track of # of times Timer0 overflows
volatile int cnt;

// this interrupt service routine (ISR) runs whenever an overflow on Timer0 occurs
ISR (TIMER0_OVF_vect) {
	if (cnt == 122) {
	  PORTB ^= (1 << 2);			// Toggle PB.5
	  cnt = 0;				// reinitialize cnt
	}
	else
	  cnt++;
}

int main(void) {

	cnt = 0;				// initialize cnt to keep track of number of 
// times Timer0 overflows
	DDRB |= (1 << 2);			// connect LED to pin PB.2

	// set up Timer0 with prescaler = 64 and normal mode
	TCCR0A = 0;
	TCCR0B |= (1 << CS00)|(1 << CS01);
	
	TCNT0 = 0;				// initialize counter
	TIMSK0 |= (1 << TOIE0);		// enable overflow interrupt
	sei();					// enable global interrupts

	while(1) ;				// loop forever



