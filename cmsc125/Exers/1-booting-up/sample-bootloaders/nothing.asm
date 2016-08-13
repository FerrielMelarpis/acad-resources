; Nothing boot loader

; Start matter
[BITS 16]		; Tells the compiler to make this into 16-bit code generation 
[ORG 0x7C00]		; Tells the compiler where the code is going to be
			; in memory after it has been loaded. (HEX number)

; End matter
times 510-($-$$) db 0	; Fill the rest of the sector with zero's
dw 0xAA55		; Add the boot loader signature at the end, size is 2 bytes
