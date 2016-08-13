#!/bin/bash

# For 'Nothing Boot Loader'
	#nasm -o nothing.bin nothing.asm
	#dd if=nothing.bin bs=512 of=floppy.img conv=notrunc

# For 'Never-ending loop Boot Sector'
	#nasm -o loop.bin loop.asm
	#dd if=loop.bin bs=512 of=floppy.img conv=notrunc

# For 'Character-on-the-screen Boot Loader'
	nasm -o character.bin character.asm
	dd if=character.bin bs=512 of=floppy.img conv=notrunc

# For 'Display-the-whole-string Boot Loader'
	#nasm -o string.bin string.asm
	#dd if=string.bin bs=512 of=floppy.img conv=notrunc
