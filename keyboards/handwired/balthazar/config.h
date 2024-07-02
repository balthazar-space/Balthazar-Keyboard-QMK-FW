/*
BALTHAZAR 2020/21

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED 
#define PRODUCT_ID      0xBAFE
#define DEVICE_VER      0x0001
#define MANUFACTURER    BALTHAZAR
#define PRODUCT         USB Keyboard
#define DESCRIPTION     QMK_77KEYS

/*
To use QMK keyboard on android or windows - use VID and PID from some more popular device - like Logitech G413. 
Hm, not ok
                 VID          PID
Logitech G413 -> 0x046D       0xC33A
Logitech G815 -> 0x046D       0xC33F

*/

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

//#define NO_ACTION_LAYER // disable layers totally
#define NO_ACTION_TAPPING // disable tap dance and other tapping features
#define NO_ACTION_ONESHOT // disable one-shot modifiers

// we can define DIRECT_PINS or matrix DIODE_DIRECTION
// they are mutually exclusive -> DIODE_DIRECTION denotes a matrix operation
// 7x11 ROW2COL
#define DIODE_DIRECTION ROW2COL

// key matrix size: we are forking to left and right 
#define MATRIX_COLS 11	 // pulled-up cols are inputs (unselected) and outputs: selecting - low = selected row; input high = unselected row
#define MATRIX_ROWS 7 //  pulled-up rows are inputs for reading - key pressed = low detected for selected col

// selected COL pins are switched to output mode and to low; when unselected they are input mode pulled-up = high
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D6, D4, D7, D5, D2, D3 } // these are ok

// ROW pins are input pulled-up high pins; they are read according to the selected COL
#define MATRIX_ROW_PINS { F0, F1, F4, F5, F6, F7, E6 } 
// port F is problematic? Port F4,F5,F7 are also for JTAG testing interface - PF7 on one board not ok
// JTAG-capable MCUs come from the factory with the JTAGEN fuse set, and it takes over certain pins of the MCU that the board may be using for the switch matrix, LEDs, etc. - hfuse 0x99 (JTAG enabled) or 0xD9 (JTAG disabled)
// By default, with QMK the JTAG debugging interface is disabled as soon as the keyboard starts up. 
// defined in tmk_core/common/keyboard.c as function disable_jtag
// port F pins are tristated just after reset. If JTAG activated pullup on F7, F5, F4 will be active even on reset. 
// Port F pins now ok - pulled-up inputs - E6 can also be left pulled down - 
// NO: can this be because of conflict with QMK DFU bootloader //#define QMK_LED E6

/**
INT6/AIN0 – Port E, Bit 6
INT6, External Interrupt source 6: The PE6 pin can serve as an external interrupt source.
AIN0 – Analog Comparator Negative input. This pin is directly connected to the negative input of the Analog
Comparator.
• HWB – Port E, Bit 2
HWB allows to execute the bootloader section after reset when tied to ground during external reset pulse. The
HWB mode of this pin is active only when the HWBE fuse is enable. During normal operation (excluded Reset),
this pin acts as a general purpose I/O.
Overriding Signals for Alternate Functions PE6, PE2
Signal Name PE6/INT6/AIN0     PE2/HWB
PUOE          0                   0
PUOV          0                   0
DDOE          0                   0
DDOV          0                   1
PVOE          0                   0
PVOV          0                   0
DIEOE         INT6 ENABLE         0
DIEOV         1                   0
DI            INT6 INPUT*         HWB
AIO           AIN0                INPUT*

**/

// pins unused by the keyboard for reference
#define UNUSED_PINS {}
//#define UNUSED_PINS  { E2, B0 }
// HWB/PE2 pin to ground - can be set as input only - never as output!

// Debounce reduces chatter (unintended double-presses) - default: 5; set 0 if debouncing is not needed
#define DEBOUNCE 5 //5

// delay in microseconds when between changing matrix pin state and reading values 
// in matrix.c: just after select_col(current_col) and before reading rows for current_col
#define MATRIX_IO_DELAY 30 //default 30; 100, 1000 is 1ms, 1000000 is 1s

// sets the USB polling rate in milliseconds for the keyboard, mouse, and shared (NKRO/media keys) interfaces
//#define USB_POLLING_INTERVAL_MS 10

// sets the I2C clock rate speed for keyboards using I2C. The default is 400000L 
// we may use it for PSU module
//#define F_SCL 100000L

//#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BTN_MIDDLE) // Default

//#define DEBUG_MATRIX_SCAN_RATE   // we get 1200 Hz to 500 Hz

/* 
 PB0 ISP ss - slave (SPI communication not used)  
 PB1 ISP sclk  
 PB2 ISP mosi  
 PB3 ISP miso	
 
 now PS/2:
 PB1 ps/2 clock PCINT1
 PB7 ps/2 data
*/

																																		
// disable these deprecated features by default
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//#define LOCKING_SUPPORT_ENABLE
// Locking resynchronize hack
//#define LOCKING_RESYNC_ENABLE
//#define BACKLIGHT_PIN B0 -> SS

// PS2 trackpad
/*https://docs.qmk.fm/#/feature_ps2_mouse*/
/*
trackpad without native buttons. A touch on trackpad changes the F6, F7 keys to left and right buttons 
*/

#ifdef PS2_MOUSE_ENABLE

// interrupt PS/2 touchpad
// You can use any INT or PCINT pin for clock, and any pin for data.

#ifdef PS2_USE_INT

  #define PS2_CLOCK_PORT  PORTB //PORTD
  #define PS2_CLOCK_PIN   PINB //PIND
  #define PS2_CLOCK_DDR   DDRB //DDRD
  #define PS2_CLOCK_BIT   1

  #define PS2_DATA_PORT   PORTB //PORTD
  #define PS2_DATA_PIN    PINB //PIND
  #define PS2_DATA_DDR    DDRB //DDRD
  #define PS2_DATA_BIT    7

  #define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
  } while (0)
  #define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
  } while (0)
  #define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
  } while (0)
  #define PS2_INT_VECT   INT2_vect

#endif  // end  PS2_USE_INT


// usart PS/2 touchpad - we use interrupt above

#ifdef PS2_USE_USART
  #define PS2_CLOCK_PORT  PORTD
  #define PS2_CLOCK_PIN   PIND
  #define PS2_CLOCK_DDR   DDRD
  #define PS2_CLOCK_BIT   5

  #define PS2_DATA_PORT   PORTD
  #define PS2_DATA_PIN    PIND
  #define PS2_DATA_DDR    DDRD
  #define PS2_DATA_BIT    2

  // synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge.
  // Set DDR of CLOCK as input to be slave 

  #define PS2_USART_INIT() do {   \
	    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
	    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
	    UCSR1C = ((1 << UMSEL10) |  \
		      (3 << UPM10)   |  \
		      (0 << USBS1)   |  \
		      (3 << UCSZ10)  |  \
		      (0 << UCPOL1));   \
	    UCSR1A = 0;                 \
	    UBRR1H = 0;                 \
	    UBRR1L = 0;                 \
	} while (0)

	#define PS2_USART_RX_INT_ON() do {  \
	    UCSR1B = ((1 << RXCIE1) |       \
		      (1 << RXEN1));        \
	} while (0)

	#define PS2_USART_RX_POLL_ON() do { \
	    UCSR1B = (1 << RXEN1);          \
	} while (0)

	#define PS2_USART_OFF() do {    \
	    UCSR1C = 0;                 \
	    UCSR1B &= ~((1 << RXEN1) |  \
		        (1 << TXEN1));  \
	} while (0)

	#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
	#define PS2_USART_RX_DATA       UDR1
	#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
	#define PS2_USART_RX_VECT       USART1_RX_vect

#endif // end PS2_USE_USART

// Additional mouse/ trackpad settings

// Use remote mode instead of the default stream mode 
//#define PS2_MOUSE_USE_REMOTE_MODE

// Enable the scrollwheel or scroll gesture on your mouse or touchpad 
#define PS2_MOUSE_ENABLE_SCROLLING
// Some mice will need a scroll mask to be configured. The default is 0xFF
//#define PS2_MOUSE_SCROLL_MASK 0x0F
// Applies a transformation to the movement before sending to the host
//#define PS2_MOUSE_USE_2_1_SCALING
// The time to wait after initializing the ps2 host
//#define PS2_MOUSE_INIT_DELAY 1000 // Default 

// The available buttons for (trackpoint) are:
//#define PS2_MOUSE_BTN_LEFT      0
//#define PS2_MOUSE_BTN_RIGHT     1
//#define PS2_MOUSE_BTN_MIDDLE    2

// we use trackpad without native buttons - use F6 (KC_F7), F7 (KC_F7) and 6 (KC_6) buttons
// - once we sense movement on touchpad

//Scroll Button
//To disable the scroll button feature:
//#define PS2_MOUSE_SCROLL_BTN_MASK 0

//invert the X and Y axes:
//#define PS2_MOUSE_INVERT_X
//#define PS2_MOUSE_INVERT_Y

//reverse the scroll axes:
//#define PS2_MOUSE_INVERT_H
//#define PS2_MOUSE_INVERT_V


//Rotate Mouse Axes
//Transform the output of the device with a clockwise rotation of 90, 180, or 270 degrees.
//#define PS2_MOUSE_ROTATE 270 // Compensate for East-facing device orientation.
//#define PS2_MOUSE_ROTATE 180 // Compensate for South-facing device orientation.
//#define PS2_MOUSE_ROTATE 90 // Compensate for West-facing device orientation.

#endif  // end PS2_MOUSE_ENABLE


