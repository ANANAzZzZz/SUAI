.8086
.MODEL small
.stack 100h

.DATA
	array byte 1, 4, 3, 6, 15
.CODE
	start:
	mov AX, @DATA
	mov DS, AX
	mov CX, 5
	
	mov SI, offset array 
	mov BX, 0
	@m1:
		lodsb 
		cmp AL, BH
		jg max 
		jmp @@m2 
		max:
			mov BH, AL
		@@m2:
			loop @m1 
	mov AH, 4ch
	int 21h
end start
