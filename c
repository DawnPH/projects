NAME    T5                    
OUTPORT EQU    0CFB0H         
SAVE    EQU    55H            
CSEG    AT     0000H
        LJMP   START
CSEG AT 4003H
        LJMP   INT
CSEG AT 4100H
START:  SETB   IT0
        SETB   EX0
        SETB   EA
        MOV    A,#11H        
        MOV    SAVE,A        
        ACALL  DISP         
        ACALL  DE3S          
LLL:    MOV    A,#12H       
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE10S        
        MOV    A,#10H       
        MOV    SAVE,A
        ACALL  DISP  
        MOV    R2,#05H      
TTT:    MOV    A,#14H
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S
        MOV    A,#10H
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S
        DJNZ   R2,TTT
        MOV    A,#11H       
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S        
        MOV    A,#21H       
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE10S        
        MOV    A,#01H       
        MOV    SAVE,A
        ACALL  DISP  
        MOV    R2,#05H     
GGG:    MOV    A,#41H
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S
        MOV    A,#01H
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S
        DJNZ   R2,GGG
        MOV    A,#11H      
        MOV    SAVE,A
        ACALL  DISP  
        ACALL  DE02S       
        JMP    LLL         
DE10S:  MOV    R5,#100     
        JMP    DE1
DE3S:   MOV    R5,#30     
        JMP    DE1
DE02S:  MOV    R5,#02      
DE1:    MOV    R6,#200
DE2:    MOV    R7,#126
DE3:    DJNZ   R7,DE3
        DJNZ   R6,DE2
        DJNZ   R5,DE1
        RET
INT:    CLR    EA
		PUSH   ACC         
        PUSH   PSW
        MOV    A,R5
        PUSH   ACC
        MOV    A,#11H     
        ACALL  DISP  
DEL10S: MOV    R3,#100    
DEL1:   MOV    R2,#200
DEL2:   MOV    R5,#126
DEL3:   DJNZ   R5,DEL3
        DJNZ   R4,DEL2
        DJNZ   R3,DEL1
        MOV    A,SAVE    
        ACALL  DISP  
        POP    ACC       
        MOV    R5,A
        POP    PSW
        POP    ACC
        SETB   EA        
        RETI
DISP:   MOV    DPTR,#OUTPORT
		CPL    A
        MOVX   @DPTR,A
        RET
END
