# Mage keyboard (V2 Coming Soon)

# Pictures (with kailh choc robins and MBK Legend Keycaps from [MKUltra Corporation](https://mkultra.click))
![Mage keyboard with one side angled inward](https://cdn.mossx.net/mage_keyboard/mage_stacked_medium.png)
![Mage keyboard halfs side by side](https://cdn.mossx.net/mage_keyboard/mage_side_by_side_medium.png)
![Mage keyboard plugged into an off screen computer](https://cdn.mossx.net/mage_keyboard/mage_plugged_in_medium.png)

## Design principles
 - Resistor grid keyboards are annoying to design and build
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
7. [Program the xiao with the firmware](#program-the-xiao)
8. Write the [default configuration](#default-configuration) and make any [desired modifications](#configuration-modification).
9. Plug everything in and test it
10. [Troubleshoot](#troubleshooting) if needed

## Configuration
All configuration is done with the configurator tool. There is a cli and tui interface.
### Configuration Build
Navigate into the configurator folder and run:
```
cmake -B build
cmake --build build
```
The configurator tool will then be in the build folder as 'mage_configurator'.

### Default Configuration
The default config can be uploaded to the mage with the command:
```
./configurator default
```
This does not [save](#configuration-save) the configuration to the flash memory so upon loss of power or reset the config will revert to the last saved.

### Configuration Save
The current config can be saved to flash with the command:
```
./configurator save
```
This means that the configuration will be perserved over reset. Without saving the config will have to be rewritten to the mage.

### Configuration Modification
The config can be modified with the command:
```
./configurator change [state] [column] [row] [key]
```
This command set the provided state, column, row as the key. All arguments are case insensitive.
State can be "high", "normal", "low", "control" or numbers 0-3 respectively.
Column and row are 1 index numbers. For example, the first column third row (default right arrow) would be referenced with "1 3".
Key is the name of the key that should be at the provided position. This can be the full name or a shortening. For example, The escape key can be "escape" or "ESC". A full list of names is available in the `configurator/keycode.h` file.

The config can also be modified with the tui. This is accessed with:
```
./configurator
```
The tui with the default config looks like this:
```
UP             `               F1             F2              F3             F4              F5              F6              F7             F8              F9              F10             [              ESC             
LEFT           SPACE           1              2               3              4               5               6               7              8               9               0               ]              DEL             
RIGHT          LCTRL           =              NONE            NONE           NONE            NONE            NONE            NONE           NONE            NONE            NONE            NONE           TAB             
DOWN           LSHFT           ;              NONE            NONE           NONE            NONE            NONE            NONE           NONE            NONE            NONE            =              RSHFT           
                                                                                                                                                                                                                           
UP             ESC             1              2               3              4               5               6               7              8               9               0               ]              ESC             
LEFT           TAB             Q              W               E              R               T               Y               U              I               O               P               [              DEL             
RIGHT          LCTRL           A              S               D              F               G               H               J              K               L               ;               '              TAB             
DOWN           LSHFT           Z              X               C              V               B               N               M              ,               .               /               -              RSHFT           
                                                                                                                                                                                                                           
UP             `               NONE           NONE            NONE           NONE            NONE            NONE            NONE           NONE            NONE            NONE            NONE           `               
LEFT           SPACE           F1             F2              F3             F4              F5              F6              F7             F8              F9              F10             F11            F12             
RIGHT          LCTRL           ESC            NONE            NONE           NONE            NONE            BKSP            LEFT           UP              DOWN            RIGHT           NONE           TAB             
DOWN           LSHFT           NONE           NONE            NONE           NONE            NONE            NONE            NONE           NONE            NONE            NONE            NONE           NONE            
                                                                                                                                                                                                                           
                                              RAISE           LGUI           LCTRL           SPACE           LOWER           BKSP           RCTRL           ENTER                                                          
```
Each key is interactable and the enter key allow them to take keyboard input and the name input will be sent to the mage. If the key name is invalid the old key will come back, the box will turn red and the new key is not sent to the mage.

### Configuration Revertion
If the modifications to the config should be discarded, instead of resetting the xiao the revert command can be used:
```
./configurator revert
```
This will get the configuration from flash and write it to the working configuration of the mage. This loses all modifications so be sure you want to discard them all.



## Troubleshooting
### None of the keys are working
Ensure the microcontroller's 5V, Ground, SDA and SCK pins are fully connected and not shorted. There is a normal connection with resistance between the 5V and ground pins but they should not be shorted. Also make sure the microcontroller is working. These 4 pins are the only needed pin for the mage to work and if any of them are disconnected the entire keyboard will not work.
### A region of keys (16 keys) are not working
This usually means that one of the I/O expanders is not working. Make sure that the 5V, Ground, SDA, and SCK pin are fully connected to the pads on the board.
### A one key/a few keys are not working
This usually means that the keys that aren't working are not connected to the I/O expander. Most often this is because the pin of the I/O expander for that key is not connected properly.
