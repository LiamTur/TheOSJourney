#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/amilt.kernel isodir/boot/amilt.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "amilt" {
	multiboot /boot/amilt.kernel
}
EOF
grub-mkrescue -o amilt.iso isodir

