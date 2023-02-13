.8086
.MODEL small, stdcall
.stack 100h

.DATA
	array byte 0, 2, 9, 3, 1
	
	findMax PROTO pArray: PTR byte

.CODE 
start:
	mov AX, @DATA
	mov DS, AX
	
	invoke findMax, offset array
	
	mov AX, 4Ch
	int 21h
	
findMax proc pArray:PTR byte
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
	
	ret

findMax ENDP 

end start