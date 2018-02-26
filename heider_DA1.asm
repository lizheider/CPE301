LDI R16, HIGH(RAMEND) // Intializing Stack Pointer
OUT SPH, R16
LDI R16, LOW(RAMEND) 
OUT SPL, R16

LDI R26, 0x22; store 0x22 into X-Low 
LDI R27, 0x02; store 0x02 into X-High 

LDI R28, 0x00 ; store 0x0400 into Y Low 
LDI R29, 0x04 ; store 0x0400 into Y High 

LDI R30, 0x00 ; store 0x0600 into Z Low 
LDI R31, 0x06 ; store 0x0600 into Z High 

LDI R20, 0x30; // Counter1 Value 50 in Dec (Branch options only work up to 60) 
LDI R22, 0x5; // Counter to RELOAD Counter1 (50*6=300)

MOV R23, R26	; copy R26 into R23 to not change value of R26 

START: 
ADD R23, R27 ; Add High and Low of Address
ST X+, R23; Store Sum into Address, Increment X as the pointer 
MOV R21, R23; Copy R23 into R21 to use R21 for subtraction/loop 

CHECK: 
SUBI R21, 0x5; Subtract 5 from R21

CPI R21, 0x00; Compare R21 to Zero 
BRLT NOTDIV; If R21 < 0 number NOT divisible by 5 / Go to function

CPI R21, 0X00; Compare R21 to zero 
BREQ DIV; if R21 = 0 Number is divisible by 5 / Go to function 

RJMP CHECK; No conditions met, jump to CHECK and restart loop 

DIV: // Function to store Numbers Divisible by 5 
ST Y+, R23; Store value of R23 into addr, inc pointer value
ADD R16, R23 ; add low bit to R16
ADC R17, R0 ; add carry to R17/High 
RJMP END ; Jump to end 

NOTDIV: // Function to store numbers not divisible by 5 
ST Z+, R23; store value into addr, inc pointer value 
ADD R18, R23 ; add low bit to R16 
ADC R19, R0 ; add carry 
RJMP END ; jump to end 

END:

SUBI R20, 0x01; /subtracting from counter  
BRPL START ; if counter > 0 branch to start 

LDI R20, 0x32;  "load" counter with value 50 
SUBI R22, 0x01; counter for reload amount 
BRPL START ; loop to start 

DONE: 

