; Character on the screen boot loader

; Start matter
[BITS 16]		; Tells the compiler to make this into 16-bit code generation
[ORG 0x7C00]		; Tells the compiler where the code is going to be
			; in memory after it has been loaded. (HEX number)

;Main program
main:
	mov ah,0x0E	; This is the function number in the BIOS to execute
			; This function is 'put character on screen function'

	mov bh,0x00	; Page number, just leave it to zero

	mov bl,0x50	; Text attribute (Controls the background and foreground colour
			; and possibly some other options)
			; 07 = White text, black background.
			; Feel free to play with this value as it shouldn't harm anything

	mov al,65	; This should (in theory) put a ASCII value into al to be
			; displayed. (This is not the normal way to do this)

	int 0x10	; Call the BIOS video interrupt.

	jmp $		; Put it into a coninuous loop to stop it running off into
			; the memory running any junk it may find there.

; End matter
times 510-($-$$) db 0	; Fill the rest of the sector with zero's
dw 0xAA55		; Add the boot loader signature at the end, size is 2 bytes
