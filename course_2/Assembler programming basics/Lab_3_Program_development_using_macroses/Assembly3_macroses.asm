.8086
.MODEL small, stdcall
.stack 100h

.DATA
     array byte 0, 2, 9, 3, 1

dSeg macro
	mov AX, @DATA
	mov DS, AX
ENDM
  
exit macro	
 	mov AX, 4Ch
 	int 21h
ENDM  
	
findMax macro array
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
	
ENDM 

.CODE             
start:

dSeg
findMax offset array
exit

end start