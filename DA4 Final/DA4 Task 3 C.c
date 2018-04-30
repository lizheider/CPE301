#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint16_t adc_val;

int main(void)
{
	// Set PORTB As output Port 
	// Set Fast PWM, ICR1 at TOP, Update 0CR1A at Bottom 
	DDRB |= 0xFF;
	TCCR1A |= (1<<COM1A0) | (1<<COM1A1) | (1<<WGM11); 
	TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS10);
	
	ICR1 = 19999;	//Sets TOP to 19999.
	
	// Enable ADC, Enable Interrupt, Set Prescalar 16
	// Vref is Internal 1.1V Vref 
	ADCSRA |= (1<<ADEN)| (1<<ADIE)| (1<<ADPS2);
	ADMUX |= (1<<REFS1) | (1<<REFS0);
	
	sei();
	
	// Start Conversions 
	ADCSRA |= (1<<ADSC);
	
	// Create Variables For Conversion 
	float upper = 2400;
	float lower = 800;
	float diff = (upper-lower)/1023;
	
	// Slope intercept form y = mx + b 
	// YAY math!! 
	while(1)
	{
		OCR1A = ICR1 - ((diff*adc_val) + lower);
	}
}

//Load value of ADC into adc_low.
//Set value to be used in setting OCR1A in while loop (main).
//Enable ADC Conversions 
ISR(ADC_vect)
{
	uint8_t adc_low = ADCL; 
	adc_val = (ADCH<<8) | adc_low;	
	ADCSRA |= (1<<ADSC);	
}
