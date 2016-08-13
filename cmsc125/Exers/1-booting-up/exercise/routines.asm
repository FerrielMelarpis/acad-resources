;----------------------------------------------------------------------------------------------
; A set of useful functions
;----------------------------------------------------------------------------------------------

;----------------------------------------------------------------------------------------------
;
; FUNCTION 1: Prints a 0-terminated string (SI = pointer to string)
;
;----------------------------------------------------------------------------------------------
putstr:
  lodsb                   ;Load byte at address DS:(E)SI into AL
  or al,al                ;is it the NULL(0) character?
  jz short putstrd        ;then it is the end of the string
  mov ah,0x0E             ;no? so we display the character using this BIOS video service
  mov bx,0x0007
  int 0x10
  jmp putstr              ;load the next character to AL
putstrd:
  ret                  
;----------------------------------------------------------------------------------------------
;
; FUNCTION 2: Gets a string (DI = pointer to buffer)
;
;----------------------------------------------------------------------------------------------
getstr:
  xor cl, cl              ;zero out cl, will be used as counter
 .loop:
  mov ah, 0
  int 0x16                ; wait for keypress
  cmp al, 0x08            ; backspace pressed?
  je .backspace           ; yes, handle it
 
  cmp al, 0x0D            ; enter pressed?
  je .done                ; yes, we're done
 
  cmp cl, 0x3F            ; 63 chars inputted?
  je .loop                ; yes, only let in backspace and enter
 
  mov ah, 0x0E
  int 0x10                ; print out character
 
  stosb                   ; Store AL at address ES:(E)DI
  inc cl                  ; one character in
  jmp .loop

 .backspace:
  cmp cl, 0	            ; beginning of string?
  je .loop	            ; yes, ignore the key
 
  dec di                  ; backup 1 character
  mov byte [di], 0        ; delete character
  dec cl                  ; decrement counter as well
 
  mov ah, 0x0E
  mov al, 0x08
  int 10h                 ; backspace on the screen
 
  mov al, ' '
  int 10h                 ; blank character out
 
  mov al, 0x08
  int 10h                 ; backspace again
 
  jmp .loop               ; go to the main loop
 
 .done:
  mov al, 0               ; null terminator
  stosb
 
  mov ah, 0x0E
  mov al, 0x0D
  int 0x10
  mov al, 0x0A
  int 0x10               ; newline
 
  ret
;----------------------------------------------------------------------------------------------
; FUNCTION 3: Compare two strings SI and DI 
; 				if equal: 'carry flag' is set
; 				if not equal: 'carry flag' is not set

; NOTE: You will need to use 'jc' in the program who called this routine to check the status of
;	   the 'carry flag' 
; 	   (JUMP IF CARRY [flag is set], SYNTAX: jc <label>)
;----------------------------------------------------------------------------------------------
strcmp:
 .loop:
  mov al, [si]            ; grab a byte from SI
  mov bl, [di]            ; grab a byte from DI
  cmp al, bl              ; are they equal?
  jne .notequal           ; nope, we're done.
 
  cmp al, 0               ; are both bytes (they were equal before) null?
  je .done                ; yes, we're done.
 
  inc di                  ; increment DI
  inc si                  ; increment SI
  jmp .loop               ; loop!
 
 .notequal:
  clc                     ; not equal, clear the carry flag
  ret
 
 .done: 	
   stc                    ; equal, set the carry flag
   ret
   
