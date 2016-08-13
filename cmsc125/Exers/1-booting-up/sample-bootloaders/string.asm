; Display-the-whole-string boot loader

; Start matter
[BITS 16]				; Tells the compiler to make this into 16-bit code generation 
[ORG 0x7C00]				; Tells the compiler where the code is going to be
					; in memory after it has been loaded. (HEX number)

; Main program
main:					; Label for the start of the main program
	mov ax,0x0000			; Setup the Data Segment registers
					; Location of data is DS:Offset
						
	mov ds,ax			; This can not be loaded directly it has to be in two steps.
					; 'mov ds, 0x0000' will NOT work due to limitations on the CPU
						
	mov si, HelloWorld		; Load the string into position for the procedure.
	
	call PutStr			; Call/start the procedure
	
	jmp $				; Never ending loop

; Procedures
PutStr:					; Procedure label/start

	; Set up the registers for the interrupt call
	
	mov ah,0x0E			; The function to display a chacter (teletype)

	mov bh,0x00			; Page number
	
	mov bl,0x07			; Normal text-attribute
	
	.nextchar			; Internal label (needed to loop round for the next character)
	
	lodsb				; LOaD String Block
					; Loads [SI] into AL and increases SI by one

	; Check for end of string '0'
	
	or al,al			; Sets the zero flag if al = 0
					; (OR outputs 0's where there is a zero bit in the register)

	jz .return			; If the zero flag has been set go to the end of the procedure.
					; Zero flag gets set when an instruction returns 0 as the answer.
	
	int 0x10			; Calls the BIOS video interrupt
	
	jmp .nextchar 			; Loop back round tothe top
	
	.return				; Label at the end to jump to when complete
	ret				; Return to main program
	
; Data
	HelloWorld db 'Hello World',13,10,0	; This is a string

; End Matter
	times 510-($-$$) db 0	; Fill the rest of the sector with zero's
	dw 0xAA55		; Add the boot loader signature at the end, size is 2 bytes
