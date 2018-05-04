#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "nrf24l01.h"
#include "ioe.h"
#include "nrf24l01-mnemonics.h"


#define UBRR_2400 207

nRF24L01 *setup_rf(void);
void process_message(char *message);
inline void prepare_led_pin(void);
inline void  set_led_high(void);
inline void  set_led_low(void);
void USART_INIT(unsigned int ubrr);
void USART_tx_string(char* data);

volatile bool rf_interrupt = false;
char* outs[20];

int main(void) {
	usart0_init_();
	_delay_ms(2000);

	uint8_t address[5] = { 0x11, 0x11, 0x11, 0x11, 0x11 };
	printm("Address INIT\r\n");
	prepare_led_pin();
	printm("LED PREP\r\n");

	sei();
	nRF24L01 *rf = setup_rf();
	nRF24L01_listen(rf, 0, address);
	uint8_t addr[5];
	nRF24L01_read_register(rf, CONFIG, addr, 1);

	while (true) {
		if (rf_interrupt) {
			rf_interrupt = false;
			while (nRF24L01_data_received(rf)) {
				nRF24L01Message msg;
				nRF24L01_read_received_data(rf, &msg);
				process_message((char *)msg.data);
			}

			nRF24L01_listen(rf, 0, address);
		}
	}

	return 0;
}

nRF24L01 *setup_rf(void) {
	nRF24L01 *rf = nRF24L01_init();
	rf->ss.port = &PORTB;
	rf->ss.pin = PB2;
	rf->ce.port = &PORTB;
	rf->ce.pin = PB1;
	rf->sck.port = &PORTB;
	rf->sck.pin = PB5;
	rf->mosi.port = &PORTB;
	rf->mosi.pin = PB3;
	rf->miso.port = &PORTB;
	rf->miso.pin = PB4;
	// interrupt on falling edge of INT0 (PD2)
	EICRA |= _BV(ISC01);
	EIMSK |= _BV(INT0);
	nRF24L01_begin(rf);
	return rf;
}

void process_message(char *message) {
	printm(message);
}

inline void prepare_led_pin(void) {
	DDRB |= _BV(PB0);
	PORTB &= ~_BV(PB0);
}

inline void set_led_high(void) {
	PORTB |= _BV(PB0);
}

inline void set_led_low(void) {
	PORTB &= ~_BV(PB0);
}

// nRF24L01 interrupt
ISR(INT0_vect) {
	rf_interrupt = true;
}

void USART_INIT(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<TXEN0);

	UCSR0C = (1<<UCSZ00);
}

void USART_tx_string(char* data){
	while((*data != '\0')){
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data;
		data++;
	}
}