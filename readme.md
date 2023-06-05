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


## Firmware
#### TODO: Find a better name for the mage firmware
Choose to either use [QMK](#QMK) (more resources and better for beginners) or [mage firmware](#mage-firmware) (more hackable and on the go configuration).

### QMK
Follow the [QMK Getting Started Guide](https://docs.qmk.fm/#/newbs_getting_started) and setup your enviroment. Then, copy `magev2` from this project's `qmk` directory into your `qmk/keyboards/` folder. [Flash the firmware](https://docs.qmk.fm/#/newbs_flashing). The rest of this guide is for the mage firmware. To configure with QMK continue reading their docs.

### Mage Firmware
Initialize the cmake project with `cmake -B build`. Then, build the firmware with `cmake --build build`. Put the microcontroller into bootloader mode by holding the boot button (Labeled 'B' on the xiao) then pressing the reset button (Labeled 'R' on the xiao). Use the `install.sh` script or mount the drive and copy `build/mage_firmware.uf2` to the drive. The configuration must then be written. I recommend using the [default](#default-configuration) at first then changing whatever you see fit.

## Configuration
All configuration is done with the configurator tool. There is a cli and tui interface.
### Building the configurator
Navigate into the configurator folder and run:
```
cmake -B build
cmake --build build
```
The configurator tool will then be in the build folder as 'mage_configurator'.

### Command arguments
Some commands take arguments. For the description of the command required arguments are surrounded by `[]` and optional arguments are surrounded by `<>`. For example:
```
configurator command [required] <optional>
```
Additionally, many commands take an `<index>` argument. This tells the command which config to reference. There are 16 configs to choose from and they can be switch with the CONFIG0-CONFIGF keys.


### Default Configuration
```
configurator default
```
Uploads the default config (defined in `configurator/serial.h`). Does not [save](#Saving-the-config) the config.

### Saving the config
```
configurator save <index>
```
Saves the working config to the given index. If no index is provided saves to the current config index.

### Configuration Modification
```
configurator change [state] [column] [row] [key]
```
Sets the provided state, column, row to the key. All arguments are case insensitive.
State can be "high", "normal", "low", "control" or numbers 0-3 respectively.
Column and row are index numbers. For example, the first column third row (default right arrow) would be referenced with "1 3".
Key is the name of the key that should be at the provided position. This can be the full name or a shortening. For example, The escape key can be "escape" or "ESC". A full list of names is available in the `configurator/keycode.h` file.

```
configurator
```
Opens the working config in the TUI. Each key is interactable and pressing the enter key allow them to take the name of a keycode as input. If the key name is invalid the input will be reverted to the old value and the box will turn red.

### Configuration Restoration
```
configurator restore <index>
```
Pulls from the provided index's config from flash into the working config. The working config will not be saved by this command and the config index is not changed.

### Fetch the config
```
configurator fetch
```
Fetchs the working config from the mage and prints it out.

### Configuration index
```
configurator index <set-index>
```
If `<set-index>` is provided then pull the config at that index and set the current config index to it. Otherwise, prints the current config index.

### File commands
```
configurator download [filename]
```
Saves the current working config as a file with the provided file name.

```
configurator upload [filename]
```
Uploads the config in the file with the provided file name to the mage.

```
configurator edit [filename]
```
Opens the provided file in the TUI and saves to the original file on exit.



## Troubleshooting
### None of the keys are working
Ensure the microcontroller's 5V, Ground, SDA and SCK pins are fully connected and not shorted. There is a normal connection with resistance between the 5V and ground pins but they should not be shorted. Also make sure the microcontroller is working. These 4 pins are the only needed pins on the microcontroller for the mage to work and if any of them are disconnected the entire keyboard will not work.
### A region of keys (16 keys) are not working
This usually means that one of the I/O expanders is not working. Make sure that the 5V, Ground, SDA, and SCK pin are fully connected to the pads on the board.
### A one key/a few keys are not working
This usually means that the keys that aren't working are not connected to the I/O expander. Most often this is because the pin of the I/O expander for that key is not connected properly.
