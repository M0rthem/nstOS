#!/bin/bash

dd if=/dev/zero of=./bin/hdd.img bs=1M count=16
dd if=./bin/os-image.bin of=./bin/hdd.img conv=notrunc

qemu-system-i386 -drive format=raw,file=./bin/hdd.img,if=ide -m 128M




