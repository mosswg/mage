#!/bin/sh

make -C build
mount /dev/sda1 /home/moss/usb/
cp ./build/mage_firm.uf2 /home/moss/usb/
umount /home/moss/usb/
