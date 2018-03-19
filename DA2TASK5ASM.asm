.org 0
	RJMP begin

.org 0x06
	RJMP int0_isr

begin: 
	; initiate stack pointer
	LDI R20, low(RAMEND) 
	OUT SPL, R20
	LDI R20, high(RAMEND)
	OUT SPH, R20; 
	SBI DDRB, 0x05; // PortB.5 set as output 
	LDI R17, 0x00; // 
	LDI R20, 0x01; // 
	OUT EIMSK, R20 ; INT0 set to 1 in EIMSK Register, ext interrupt 					activated

	SEI 

loop:
	JMP loop 

int0_isr: 
	LDI R20, 0x01; 
	LDI R16, 0x20; 
	EOR R17, R16; XOR to toggle bits 
	OUT PORTB, R17; Output toggle onto LED 
	LDI R18, 0xF3; TCNT = 243 

check: 
	SUBI R18, 0x01; 
	CPI R18, 0x00; 
	BRNE check 
	LDI R20, 0x00 ; reset 
	STS TCNT0, R20 ;
	RETI 

