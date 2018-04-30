#define F_CPU 8000000UL // clock is 8MHz 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_adc(void);
int control; // controlling the motor with potentiometer 
int toggle = 0; // to toggle the motor with the switch 

int main()
{
	DDRD = 0xFB; // set Port D as outputs, leave INT1(PD3) as interrupt 
	PORTD = 0x00; // pull-up pins 

	EIMSK = 0x02; // enable INT1
	EIFR = 0x02; // enable interrupt flag
	EICRA = 0X0C; // set interrupt on rising edge

	sei(); // enable interrupts 
	init_adc(); // initiate adc stuff 
	TCCR0A=0x83; // set fast PWM // clear OCR0A on MATCH
	TCCR0B=0x03; // set prescaler to 1024
	
	while (1)
	{
		while((ADCSRA&(1<<ADIF))==0); // wait for conversion 
		control = ADC*80/100; // ADC Conversion 
		OCR0A = control; // Output to converted value to 0CR0A 
		
		if(toggle == 0) // when switch is NOT pressed (I THINK) 
		{
			PORTD = 0x00; //honestly not sure what I did but it worked?
		}
	}
}
void init_adc(void) // Initiate ADC function 
	{
	ADMUX = (1<<REFS0); // Reference voltage at Aref 
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// from ADCRSA we Enable ADC, Start Conversion, Set prescalar as 128 
	}

ISR(INT1_vect)
{
	toggle ^= 1; // toggle switch on INT1 Interrupt
}
