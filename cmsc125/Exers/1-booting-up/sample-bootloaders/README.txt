-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Available Sample Bootloaders
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
1. nothing.asm		Does nothing! :))
2. loop.asm		Infinite loop @.@
3. character.asm	Prints a single character, by default 'A'. Can you change it to 'B'? Weh? ;)
4. string.asm		Prints a string, by default "Hello World". Can you change it to "Happy New Year"


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
How to compile, and install BOOTLOADER in your own HARD DISK (floppy.img)?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
1. Edit the install.sh, comment out the desired bootloader to use. (Remove the '#')
2. In your terminal just type the following commands:
	$ chmod 755 install.sh
	$ ./install.sh
	
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
How to run the EMULATOR (QEMU) and load your HARD DISK (with the KERNEl and BOOTLOADER installed in it)?
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
In your terminal just type the following commands:
	For 64-bit: $ qemu-system-x86_64 -fda floppy.img 
	For 32-bit: $ qemu-system-i386 -fda floppy.img
