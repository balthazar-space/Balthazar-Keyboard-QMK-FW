/*
BALTHAZAR 2020-21 default

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

#include QMK_KEYBOARD_H

// debug -> CONSOLE_ENABLE yes // in rules.mk 

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    //uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    if(record->event.pressed > 0) {
	uprintf("KL: keycode: 0x%04X, col: %u, row: %u, pressed: %b\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    }	
#endif 
  return true;
}
*/

/**
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
**/


/**
we have left and right split to 7 active pins (rows)
per each split row we have 11 cols to be read
all 77 matrix nodes are used 
we could add another row or rather col

Programming usage is our focus:

Esc is ok, Tab is ok
 
Left Shift key is important - switches between:
- numbers and  ¨ ! " # $ % & / ( ) = ? *
- small letters and their capitals 
- < and > ...

Cap is of secondary importance

Ctrl and Alt are ok

GUI is important - switches between views

Right Shift key (KC_RSFT) can be used for something else AltGr -> KC_RALT or KC_ROPT or KC_ALGR

In the middle F6 and F7 act as mouse left and right buttons, 6 is middle button (scrolling) - above is touchpad 
to the far left and right are loudspeakers

   ┌──────┐                 ┌───────────┐                 ┌──────┐
   │      │                 │           │                 │      │
   │      │                 │           │                 │      │
                            │           │		
 *  rows are verticals      │           │
 *    1   2   3   4   5   6 │ 7       1 │ 2   3   4   5   6   7
 *  ┌───┬───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┬────┐
 *  │Esc│F1 │F2 │F3 │F4 │F5 │F6 │   │F7 │F8 │F9 │F10│F11│F12│PScr│
 * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
 * │ Tab│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Del │
 * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
 * │Shft│Cap│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Back│
 * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
 * │Ctrl│Alt│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │Entr│
 *      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
 *      │GUI│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │UP │AltG│
 *        ┌───┬───┐   ┌───┐                ┌───┐    ┌───┬───┬────┐
 *        │Spc│Spc│   │Spc│                │Spc│    │LFT│DWN│RGHT│
 *          space keys are four parallel keys
 *
 * 7x11 = 7 rows scanning + 11 cols reading
 * 
 * row 1 = Esc, Grave, Tab , Caps, Shift, Ctrl, N, J, U, 7, F1
 * row 2 = F1,  1,     Q,   A,    Nubs,  Alt,  M, K, I, 8, F8
 * etc.
**/

/* We have:
 DIODE_DIRECTION ROW2COL
 MATRIX_ROWS 7
 MATRIX_COLS 11
 COLS: Left to right, ROWS: Top to bottom

 matrix.h says:
 - according to number of cols (<8, <16 or <32) we create a binary 8 bit, 16 bit or 32 bit variable to hold all row values that were read 
 - for each col - get all row values 
 - col to row: Set row, read cols -> read_cols_on_row
 - row to col: Set col, read rows -> read_rows_on_col
 - matrix.c sets all row and col pins to pulled-up input mode, sets the selected active pin (set row or set col) as output low
 - then reads the (read cols or rows) for 0 -> button pushed on that input pin -> pulled down via diode    
 
 In my situation i wanted to have COL as active select/ unselect outputs with high as selected and reading ROWS inputs as normally LOW for HIGH state - the diodes face COL2ROW and additional resistors are there to pull down inputs. Now resistors are not needed.
 If i changed the direction of diodes - all would be ok: 7 LOW scanning outputs would be as envisioned
  
 So i adapted to QMK: Our scanning output pins COLS become input reading pins ROWS and our input pins ROWS become scanning output pins COLS. We always have 7 input reading pins and 11 output scanning pins. 
 - we can exchange definitions of COLS pins and ROWS pins and then define diode direction to COLS2ROWS  MATRIX_ROWS 11 MATRIX_COLS 7
 - or keep it as now defined : diode direction ROWS2COLS MATRIX_ROWS 7 MATRIX_COLS 11
 - in both we have 11 scanning outputs and 7 inputs to remember 
 - if another set of keys needed i would add 8th input line with options for 11 more keys (88) 
 - or 12th output line with option for 7 more keys (84)
 - or have 8 x 10 = 80 - 3 more keys 
 - but 7 x 11 = 77 is ideal
*/


// direct matrix description - without macro -> ROW2COL
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = { // 7x11 ISO
          { KC_ESC, KC_GRV, KC_TAB,  KC_CAPS, KC_LSFT, KC_LCTL,  KC_N,    KC_J,    KC_U,    KC_7,    KC_F7 },    
          { KC_F1,  KC_1,   KC_Q,    KC_A,    KC_NUBS, KC_LALT,  KC_M,    KC_K,    KC_I,    KC_8,    KC_F8 },
          { KC_F2,  KC_2,   KC_W,    KC_S,    KC_Z,    KC_LGUI,  KC_COMM, KC_L,    KC_O,    KC_9,    KC_F9 }, 
          { KC_F3,  KC_3,   KC_E,    KC_D,    KC_X,    KC_SPC,   KC_DOT,  KC_SCLN, KC_P,    KC_0,    KC_F10 },
          { KC_F4,  KC_4,   KC_R,    KC_F,    KC_C,    KC_LEFT,  KC_SLSH, KC_QUOT, KC_LBRC, KC_MINS, KC_F11  }, 
          { KC_F5,  KC_5,   KC_T,    KC_G,    KC_V,    KC_DOWN,  KC_UP,   KC_NUHS, KC_RBRC, KC_EQL,  KC_F12 },    
          { KC_F6,  KC_6,   KC_Y,    KC_H,    KC_B,    KC_RIGHT, KC_ALGR, KC_ENT,  KC_BSPC, KC_DEL,  KC_PSCR  },
  } 
  
 };

/**
// indirect with row and cols role reversed -> COL2ROW
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR,   
    KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, 
    KC_TAB, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, 
    KC_CAPS, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
    KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C,  KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_ALGR, 
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_LEFT, KC_DOWN, KC_RGHT
  ),
};
**/

/**

AltGr (KC_ALGR) prints:
~ @ [] \ | € { } § ł

In addition, keycodes in the range of 0xA5-DF are reserved for internal use:
Key 			Aliases 		Description
KC_NO 			XXXXXXX 		Ignore this key (NOOP)
KC_TRANSPARENT 	KC_TRNS, _______ 	Use the next lowest non-transparent key

* DENOTES SELECTED

Key 			Aliases 		Description
*KC_ENTER 		KC_ENT 		Return (Enter)
*KC_ESCAPE 		KC_ESC 		Escape
*KC_BSPACE 		KC_BSPC 		Delete (Backspace)
*KC_TAB 					Tab
*KC_SPACE 		KC_SPC 		Spacebar
*KC_MINUS 		KC_MINS 		- and _
*KC_EQUAL 		KC_EQL 		= and +
*KC_LBRACKET 		KC_LBRC 		[ and {
*KC_RBRACKET 		KC_RBRC 		] and }
KC_BSLASH 		KC_BSLS 		\ and |
KC_NONUS_HASH 		KC_NUHS 		Non-US # and ~
KC_SCOLON 		KC_SCLN 		; and :
*KC_QUOTE 		KC_QUOT 		' and "
*KC_GRAVE 		KC_GRV, KC_ZKHK 	` and ~, JIS Zenkaku/Hankaku
*KC_COMMA 		KC_COMM 		, and <
*KC_DOT 					. and >
KC_SLASH 		KC_SLSH 		/ and ?
KC_NONUS_BSLASH 	KC_NUBS 		Non-US \ and |

Lock Keys
Key 			Aliases 		Description
*KC_CAPSLOCK 		KC_CLCK, KC_CAPS 	Caps Lock
KC_SCROLLLOCK 		KC_SLCK, KC_BRMD 	Scroll Lock, Brightness Down (macOS)
KC_NUMLOCK 		KC_NLCK 		Keypad Num Lock and Clear
KC_LOCKING_CAPS 	KC_LCAP 		Locking Caps Lock
KC_LOCKING_NUM 	KC_LNUM 		Locking Num Lock
KC_LOCKING_SCROLL 	KC_LSCR 		Locking Scroll Lock

Modifiers
Key 			Aliases 		Description
*KC_LCTRL 		KC_LCTL 		Left Control
*KC_LSHIFT 		KC_LSFT 		Left Shift
*KC_LALT 		KC_LOPT 		Left Alt (Option)
*KC_LGUI 		KC_LCMD, KC_LWIN 	Left GUI (Windows/Command/Meta key)
KC_RCTRL 		KC_RCTL 		Right Control
KC_RSHIFT 		KC_RSFT 		Right Shift
KC_RALT 		KC_ROPT, KC_ALGR 	Right Alt (Option/AltGr)
KC_RGUI 		KC_RCMD, KC_RWIN 	Right GUI (Windows/Command/Meta key)

Commands
Key 			Aliases 			Description
*KC_PSCREEN 		KC_PSCR 			Print Screen
KC_PAUSE 		KC_PAUS, KC_BRK, KC_BRMU 	Pause, Brightness Up (macOS)
KC_INSERT 		KC_INS 			Insert
KC_HOME 						Home
KC_PGUP 						Page Up
*KC_DELETE 		KC_DEL 			Forward Delete
KC_END 						End
KC_PGDOWN 		KC_PGDN 			Page Down
*KC_RIGHT 		KC_RGHT 			Right Arrow
*KC_LEFT 						Left Arrow
*KC_DOWN 						Down Arrow
*KC_UP 						Up Arrow
KC_APPLICATION 	KC_APP 			Application (Windows Context Menu Key)
KC_POWER 		System Power
KC_EXECUTE 		KC_EXEC 			Execute
KC_HELP 						Help
KC_MENU 						Menu
KC_SELECT 		KC_SLCT 			Select
KC_STOP 		Stop
KC_AGAIN 		KC_AGIN		 	Again
KC_UNDO 						Undo
KC_CUT 						Cut
KC_COPY 						Copy
KC_PASTE 		KC_PSTE 			Paste
KC_FIND 						Find
KC__MUTE 						Mute
KC__VOLUP 						Volume Up
KC__VOLDOWN 						Volume Down
KC_ALT_ERASE 		KC_ERAS 			Alternate Erase
KC_SYSREQ 						SysReq/Attention
KC_CANCEL 						Cancel
KC_CLEAR 		KC_CLR			 	Clear
KC_PRIOR 						Prior
KC_RETURN 						Return
KC_SEPARATOR 						Separator
KC_OUT 						Out
KC_OPER 						Oper
KC_CLEAR_AGAIN 					Clear/Again
KC_CRSEL 						CrSel/Props
KC_EXSEL 						ExSel

**/

