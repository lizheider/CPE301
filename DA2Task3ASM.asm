// DA task 3 ASM
// Program to generate a waveform on PORTB.2 with 50% DC and 0.5 sec period 
// (Toggle and LED at every 0.25 seconds for a total period of 0.5 seconds) 

start:
	; Toggle PORTB.5 every ~1 second
	SBI	 DDRB,2			;PB.2 as an output
	LDI	 R18,0			;PB.2 = 0
	OUT	 PORTB,R18	
	LDI	 R16,0x04		;R16 = 0x20: bit 5 = 1
	LDI  	 R21, 15		;initialize loop count
Begin:
	LDI	 R19, 0x0		;load Timer0 = 0
	OUT	 TCNT0,R19		
 	OUT	 TCCR0A,R18 		;Timer0: normal mode, internal clock
	LDI	 R17,(1<<CS00) | (1<<CS01) ;Timer0: enabled, prescalar = 64
	OUT	 TCCR0B, R17
Again:	
	IN	 R20,TIFR0		;read Timer0 flags register
	SBRS	 R20,0 		;if overflow (TOV0) is set skip next instruction
	RJMP	 Again
	LDI	 R20,0x0		;stop/disable Timer0
	OUT	 TCCR0B,R20	
	LDI	 R20,(1<<TOV0)	;clear Timer0 overflow flag (TOV0)
	OUT	 TIFR0,R20	 
	DEC  	 R21			; R21--
	BRNE 	 Begin			; Repeat if Timer0 hasn't overflowed 30 times
Toggle:
	EOR	 R18,R16		;toggle bit 2 of R18
	OUT	 PORTB,R18		;toggle PB.2
	LDI  	 R21, 15		;reinitialize loop count
	RJMP	 BEGIN
