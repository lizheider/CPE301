;DA2 TASK4 
; Task 1 Using TIMER0_OVF_vect interrupt mechanism 
.org 0
	jmp  main
.org 0x20
	jmp  T0_OVF			; Timer0 overflow interrupt vector

main:
	
	SBI	 DDRB,2		;PB.2 as an output 
	LDI	 R18,0			;PB.2 = 0
	OUT	 PORTB,R18	
	LDI	 R16,0x04		; 
	LDI  	 R21, 15		;initialize loop count to 30
Begin:
	LDI	 R19, 0x0		;load Timer0 = 0
	OUT	 TCNT0,R19		
 	OUT	 TCCR0A,R18 		;Timer0: normal mode, internal clock
	LDI	 R17,(1<<CS00) | (1<<CS01) ;Timer0: enabled, prescalar = 64
	OUT	 TCCR0B, R17

	;enable interrupts
	LDI 	 R20, 0x01 		;can also use (1<<TOIE0)
	STS  	 TIMSK0, R20 		;interrupt overflow enabled 
	SEI 				;global interrupts enabled 
Loop: 	
	RJMP 	 LOOP			;LOOP INFINITELY!!!! 


T0_OVF:
	LDI	 R20,0x0		;stop/disable Timer0
	OUT	 TCCR0B,R20	
	LDI	 R20,(1<<TOV0)	;R20 = 0x01
	OUT	 TIFR0,R20		;clear TOV0 flag 
	DEC  	 R21			;R21--
	BRNE 	 finish			;repeat if Timer0 hasn't overflowed 30 times

	LDI  	 R21, 15		;reinitialize loop count to 30
	EOR	 R18,R16		;toggle bit 5 of R18
	OUT	 PORTB,R18		;toggle PB.5
finish:
	LDI	 R19, 0		;load Timer0 = 0
	OUT	 TCNT0,R19		
	LDI	 R17,(1<<CS00) | (1<<CS01) ;Timer0: enabled, prescalar = 1024
	OUT	 TCCR0B, R17
	RETI				;Interrupts Enabled
