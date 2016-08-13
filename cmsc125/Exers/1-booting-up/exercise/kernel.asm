;-----------------------------------------------------------------------------------------------------------------
; Kernel code
; This resides in a different sector, sector 2
;-----------------------------------------------------------------------------------------------------------------

start:
	mov ax, KERNEL_SEGMENT        ; Update segment registers so that access is relative to the kernel segment
	mov ds, ax                    ; see bootsector
	mov es, ax

	mov si, welcome               ; print some message
	call putstr

mainloop:
	mov si, prompt                ; show the prompt
	call putstr

	mov di, buffer                ; get commands
	call getstr
 
	mov si, buffer
	cmp byte [si], 0              ; blank line?
	je mainloop                   ; yes, ignore it
 
	mov si, buffer
	mov di, cmd_hi                ; "hi" command
	call strcmp
	jc .helloworld
 
	mov si, buffer
	mov di, cmd_help              ; "help" command
	call strcmp
	jc .help
 
	mov si, badcommand
	call putstr 
	jmp mainloop  
 
	.helloworld:
		mov si, msg_helloworld
		call putstr
		jmp mainloop
 
	.help:
		mov si, msg_help
		call putstr
		jmp mainloop
   
; Data
	welcome db 'Welcome to ICS OS!', 0x0D, 0x0A, 0
	msg_helloworld db 'Hello CMSC 125!', 0x0D, 0x0A, 0
	badcommand db 'Bad command entered.', 0x0D, 0x0A, 0
	prompt db 'user$', 0
	cmd_hi db 'hi', 0
	cmd_help db 'help', 0
	msg_help db 'Available commands: hi, help', 0x0D, 0x0A, 0
	buffer times 64 db 0

	KERNEL_SEGMENT equ 0x1000

%include "routines.asm"

times 512-($-$$) db 0
