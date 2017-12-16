#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/arkos.kernel isodir/boot/arkos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "arkos" {
	multiboot /boot/arkos.kernel
}
EOF
grub-mkrescue -o arkos.iso isodir
