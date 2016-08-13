-----------------------------------------------------------------------------------------------------------------------------------------------------------------
What's Inside?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
1. kernel.asm 		[DO NOT EDIT THIS] This simulates an OS KERNEL. 
			Performs basic tasks such as (1) greeting the user and (2) listing available commands.

2. routines.asm		[DO NOT EDIT THIS] This is a library of functions used by the KERNEL (kernel.asm). 
			HINT: Use this as reference for creating your BOOTLOADER exercise.

3. bootsect.asm		This simulates the BOOTLOADER. 
			This is your EXERCISE. You'll just have to edit this code. :)

4. floppy.img		Acts as the primary DISK / HARD DISK where the KERNEL and the BOOTLOADER will be installed. 
			You can think of this as your "HARD DISK".

5. install.sh		[DO NOT EDIT THIS] Shell script for compiling the KERNEL and the BOOTLOADER and installing them in the HARD DISK (floppy.img).

6. answer.img		This is the "answer key" for your exercise. You should be able to implement its behavior by just editing the BOOTLOADER (bootsect.asm).
			In this "HARD DISK", the KERNEL and the BOOTLOADER are already installed for your reference. :)


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
How to load the working HARD DISK (answer.img) to the EMULATOR (QEMU)?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
In your terminal just type the following commands:
	For 64-bit: $ qemu-system-x86_64 -fda answer.img 
	For 32-bit: $ qemu-system-i386 -fda answer.img


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
How to compile, and install the KERNEL and the BOOTLOADER in your own HARD DISK (floppy.img)?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
In your terminal just type the following commands:
	$ chmod 755 install.sh
	$ ./install.sh
	
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
How to run the EMULATOR (QEMU) and load your HARD DISK (with the KERNEl and BOOTLOADER installed in it)?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
In your terminal just type the following commands:
	For 64-bit: $ qemu-system-x86_64 -fda floppy.img 
	For 32-bit: $ qemu-system-i386 -fda floppy.img
