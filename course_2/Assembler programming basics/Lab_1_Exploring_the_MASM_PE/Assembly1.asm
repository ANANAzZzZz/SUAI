.8086
.MODEL small
.DATA
     v1 word 0AAAAh
     v2 dword 0CBAFh
	 v3 dword 0AFAFAFAh
	 v4 byte  10h

.CODE  
start:
	  mov ax,@DATA          
	  mov ds,ax
	 
	  mov ax, offset v1
	  mov bx, offset v2
	  mov cx, offset v3
	  mov dx, offset v4
	  
	  mov ah,4Ch
	  int 21h     
	  
END start 
