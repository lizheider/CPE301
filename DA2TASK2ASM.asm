.org 0 

main: 
	LDI R16, 0x20; 
	SBI DDRB, 0x05; // PortB.5 Set as output 

	LDI R17, 0x00;
	LDI R18, 0x00; 
	OUT DDRD, R18; // input to DDRD 

	LDI R20, 13; 
	STS TCCR1B, R20; // prescalar 1024 
	IN R20, PIND; 

	ANDI R20, 0x02; 
	CPI R20, 0x02; 

	BRNE main

begin: 
	RCALL delay 
	EOR R17, R16
	OUT PORTB, R17
	RJMP begin 

delay: 
	LDS R29, TCNT1H ;
	LDS R28, TCNT1L ;
	CPI R28, 0xF3;
	BRSH body ;
	RJMP delay ;

body: 
	CPI R29, 0x00; 
	BRSH done
	RJMP delay 

done: 
	LDI R20, 0x00;
	STS TCNT1H, R20; 
	LDI R20, 0x00; 
	STS TCNT1L, R20; 
	RET
