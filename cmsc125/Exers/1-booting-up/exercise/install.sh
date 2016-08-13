#!/bin/bash

nasm -o bootsect.bin bootsect.asm
nasm -o kernel.bin kernel.asm
dd if=bootsect.bin bs=512 of=floppy.img conv=notrunc
dd if=kernel.bin bs=512 of=floppy.img seek=1 conv=notrunc
