.org 0 
	
	SBI DDRB, 2; Set Portb.2 as an output 
	LDI R17, 0x00; 
	LDI R18, 0x05; // prescalar value to 1024 [101]
	STS TCCR1B, R18; // presc value to register 

	STS PORTB, R18; // 

toggle:  
	RCALL delay; 
	EOR R17, R18; toggle 
	OUT PORTB, R18; 
	RJMP toggle

delay:
	LDS R29, TCNT1H; 
	LDS R28, TCNT1L; 

	CPI R28, 0xF3; // 0xF3 = 243 
	BRSH body 
	RJMP delay 

body: 
	CPI R29, 0x00; 
	BRSH done
	RJMP delay 

done: 
	LDI R20, 0x00; 
	STS TCNT1H, R20; 
	STS TCNT1L, R20; 

RET 
