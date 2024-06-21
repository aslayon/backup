MAIN   SEGMENT
ASSUME  CS:MAIN, DS:MAIN

       	MOV     CX, 1
     	MOV     AX, 0

LOOP1:  ADD     AX, CX
	INC     CX
	CMP     CX, 10

	JBE     LOOP1
	MOV     SUM, AX

SUM   DW    1234H

MAIN  	ENDS
	END