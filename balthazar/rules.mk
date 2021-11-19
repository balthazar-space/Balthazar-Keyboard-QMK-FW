# MCU name
MCU = atmega32u4

# defaults
#F_CPU = 16000000
#ARCH = AVR8
#F_USB = $(F_CPU)
#OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp

#BOOTLOADER = atmel-dfu
BOOTLOADER = caterina # promicro
#BOOTLOADER = lufa-dfu
#QMK maintains a fork of the LUFA DFU bootloader that additionally performs a simple matrix scan for exiting the bootloader
#and returning to the application, as well as flashing an LED/making a ticking noise 
#BOOTLOADER = qmk-dfu


# Build Options
#   change yes to no to disable

PS2_MOUSE_ENABLE = no 		# use ps/2 touchpad - not yet
MOUSEKEY_ENABLE = no        	# Mouse keys - we dont use buttons on mousepad, but on keyboard
#To use USART on the ATMega32u4, you have to use PD5 for clock and PD2 for data. 
#If one of those are unavailable, you need to use interrupt version.
#PS2_USE_INT = yes  		# first we us this one
#PS2_USE_USART = yes		# later we will use this one

MIDI_ENABLE = no            # MIDI support - might be usefull - need to declare keymap layer
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

# optional small i2c OLED 128x32
OLED_ENABLE = yes 	# enable optional small i2c OLED
OLED_DRIVER = SSD1306	   # default for both SSD1306 and SH1106
 
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality / -> #define BACKLIGHT_PIN B7 in config.h
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
UNICODE_ENABLE = no         # Unicode - mabye?
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches

#ISSI_ENABLE = yes	     # If the I2C pullup resistors aren't installed this must be disabled
#WATCHDOG_ENABLE = yes	     # Resets keyboard if matrix_scan isn't run every 250ms

#CUSTOM_MATRIX 		# Allows replacing the standard matrix scanning routine with a custom one.
#DEBOUNCE_TYPE			# Allows replacing the standard key debouncing routine with an alternative or custom one.
#WAIT_FOR_USB  = yes		#Forces the keyboard to wait for a USB connection to be established before it starts up
#NO_USB_STARTUP_CHECK  = yes	#Disables usb suspend check after keyboard startup. Usually the keyboard waits for the host to wake it up before any tasks are performed. This is useful for split keyboards as one half will not get a wakeup call but must send commands to the master.

