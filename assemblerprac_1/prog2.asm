

MAIN  	SEGMENT
	ASSUME  CS : MAIN 

	MOV  DL, 'A'
	MOV  AH,  2
	INT  21H  

	MOV  AH,  4CH
	INT  21H 

MAIN  	ENDS
	END
