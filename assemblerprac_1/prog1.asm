MAIN   SEGMENT
ASSUME  CS:MAIN, DS:MAIN
       	MOV     AX, CS
     	MOV     DS, AX
       	MOV     CX, 1
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