#!/bin/sh

"sudo" echo -n
make -C build && "sudo" mount /dev/sda1 /home/moss/usb/ && "sudo" cp ./build/firmware/mage_firm.uf2 /home/moss/usb/ && "sudo" umount /home/moss/usb/
