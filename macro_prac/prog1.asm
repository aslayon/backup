KM	MACRO
	I HAVE
	A DREAM
KM	ENDM
	

LM	MACRO
	I DO NOT
	HAVE A DREAM
LM	ENDM


MAIN   SEGMENT
ASSUME  CS:MAIN, DS:MAIN
       	MOV     AX, CS
     	MOV     DS, AX
       	MOV     CX, 1

		KM
		LM

     	MOV     AX, 0
LOOP1:  ADD     AX, CX
	INC     CX
	CMP     CX, 10
	JBE     LOOP1
	MOV     SUM, AX
	MOV     AH, 4CH
	INT     21H
	SUM   DW       ?
MAIN  	ENDS
	END