#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


void init_adc(void); // ADC functions
void timer0_init(); // ADC function for Timer 0 CTC 

int control = 0; // converted ADC value to control motor speed 

int main()
{
	
	DDRD = 0xFF; // Set Port D for outputs
	int wait = 0; // Wait is the delay 
	
	init_adc(); // Initialize ADC conversions 
	timer0_init(); // Initialize timer0 CTC function 
	
	while(1)
	{
		while((ADCSRA&(1<<ADIF))==0);
		control = ADC*80/100; // ADC Conversion
		
		// Stepper Motor function in half stepper mode (7 commands vs 4) 
		
		if (control < 1) // when control < 1 potentiometer is lowest voltage 
		{
			wait = 0; // wait is the delay that controls the 
			
			PORTD = 0x0C;
			_delay_ms (wait);
			PORTD = 0x04;
			_delay_ms (wait);
			PORTD = 0x06;
			_delay_ms (wait);
			PORTD = 0x02;
			_delay_ms (wait);
			PORTD = 0x01;
			_delay_ms (wait);
			PORTD = 0x09;
			_delay_ms (wait);
			PORTD = 0x08;
			_delay_ms (wait);
		}
		else if (control < 3)
		{
			wait = 100;
			
			PORTD = 0x0C;
			_delay_ms (wait);
			PORTD = 0x04;
			_delay_ms (wait);
			PORTD = 0x06;
			_delay_ms (wait);
			PORTD = 0x02;
			_delay_ms (wait);
			PORTD = 0x01;
			_delay_ms (wait);
			PORTD = 0x09;
			_delay_ms (wait);
			PORTD = 0x08;
			_delay_ms (wait);
		}
		else if (control < 4)
		{
			wait = 50;
			
			PORTD = 0x0C;
			_delay_ms (wait);
			PORTD = 0x04;
			_delay_ms (wait);
			PORTD = 0x06;
			_delay_ms (wait);
			PORTD = 0x02;
			_delay_ms (wait);
			PORTD = 0x01;
			_delay_ms (wait);
			PORTD = 0x09;
			_delay_ms (wait);
			PORTD = 0x08;
			_delay_ms (wait);
		}
		
		else if (control > 4) // when control > 4 potentiometer at max value 
		{
			wait = 10;
			
			PORTD = 0x0C;
			_delay_ms (wait);
			PORTD = 0x04;
			_delay_ms (wait);
			PORTD = 0x06;
			_delay_ms (wait);
			PORTD = 0x02;
			_delay_ms (wait);
			PORTD = 0x01;
			_delay_ms (wait);
			PORTD = 0x09;
			_delay_ms (wait);
			PORTD = 0x08;
			_delay_ms (wait);
		}
		
	}
}

void init_adc(void) // Initiate ADC function
{
	ADMUX = (1<<REFS0); // Reference voltage at Aref
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// from ADCRSA we Enable ADC, Start Conversion, Set prescalar as 128
}


//  Using a timer in CTC mode to control the delay 
void timer0_init()
{
	TCCR0B |= (1 << WGM12)|(1 << CS11)|(1 << CS10); // Prescalar 64 set CTC mode 
	TCCR0A |= (1 << COM1A0); // Set timer in OCOA Pin Toggle Mode 
	TCNT0 = 0; // Initialize Counter 
	OCR0A = control; // OCROA reading ADC converted value 
}