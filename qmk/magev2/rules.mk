
# MCU name
MCU = RP2040

MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
DEBUG_ENABLE = yes
NKRO_ENABLE = yes            # USB Nkey Rollover
UNICODE_ENABLE = yes
CUSTOM_MATRIX = lite
NO_USB_STARTUP_CHECK = yes
BOOTLOADER = rp2040

SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
