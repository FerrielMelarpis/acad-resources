; Never-ending loop bootloader

; Start matter
[BITS 16]		; Tells the compiler to make this into 16-bit code generation 
[ORG 0x7C00]		; Tells the compiler where the code is going to be
			; in memory after it has been loaded. (HEX number)

main:			; Main code label (Not really needed now but will be later)
jmp $			; Jump to the start of the instruction (never ending loop)
			; An alternative would be 'jmp main' that would have the exact same effect

; End matter
times 510-($-$$) db 0	; Fill the rest of the sector with zero's
dw 0xAA55		; Add the boot loader signature at the end, size is 2 bytes
