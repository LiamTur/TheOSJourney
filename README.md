# OS project:
this project is aimed towards understanding C and OS on a intimate level. It is a hobby project only and is based on OSDev.

### So far:

A simple kernel and somewhat restructuring for futher development, for it to work, use a cross-compiler this project is currently using i686-elf-gcc. It is taken from the latest gcc and binutils for freestanding (duh). To test run ./header.sh then ./iso.sh and finaly ./qemu.sh.

I have not implemented a original bootloader yet and I am therefore using GRUB the boot.s is in the project so to not infringe on copyright. Qemu is not necessary any VM will do but this CANNOT run on the real system. For now only a super simple Kernel is implemented called kernel.
