# Mage keyboard

# Pictures (with kailh choc robins and MBK Legend Keycaps from [MKUltra Corporation](mkultra.click)
![Mage keyboard with one side angled inward](https://cdn.mossx.net/mage_keyboard/mage_stacked_medium.png)
![Mage keyboard halfs side by side](https://cdn.mossx.net/mage_keyboard/mage_side_by_side_medium.png)
![Mage keyboard plugged into an off screen computer](https://cdn.mossx.net/mage_keyboard/mage_plugged_in_medium.jpg)

## Design principles
 - Grid keyboards are annoying to design and build
 - Finger movement should be reduced as much as possible

## Inspiration
 - MiRage keyboard by Voidstar Labs (Zack Freedman): My motivation for making this
 - Ergodox: Control groups for thumbs
 - Lily58: The basis of the default layout

## Required Materials
 - Seeedstudio Xiao rp2040
 - x4 mcp23017 i/o expander
 - x4 3k Ohm 1204 SMD resistor
 - x4 10k Ohm 1204 SMD resistor
 - x2 3.5mm TRRS Jack
 - TRRS Cable
 - USB-C Cable
 - x64 kaihl choc v1 or v2 switch

## Build guide
1. Solder the R1 and R2 3kOhm resistors
2. Solder the R3 and R4 10kOhm resistors
3. Solder the I/O expanders
4. Solder the Xiao rp2040 on the left half
5. Solder the TRRS Jack
6. Solder on the switches
7. Program the xiao with the [mage firmware](https://github.com/mosswg/mage_firmware)
8. Plug everything in and test it
9. [Troubleshoot](#troubleshooting) if needed


## Troubleshooting
### None of the keys are working
Ensure the microcontroller's 5V, Ground, SDA and SCK pins are fully connected and not shorted. There is a normal connection with resistance between the 5V and ground pins but they should not be shorted. Also make sure the microcontroller is working. These 4 pins are the only needed pin for the keyboard to work and if any of them are disconnected the entire keyboard will not work.
### A region of keys (16 keys) are not working
This usually means that one of the I/O expanders is not working. Make sure that the 5V, Ground, SDA, and SCK pin are fully connected to the pads on the board.
### A one key/a few keys are not working
This usually means that the keys that aren't working are not connected to the I/O expander. Most often this is because the pin of the I/O expander for that key is not connected properly.
