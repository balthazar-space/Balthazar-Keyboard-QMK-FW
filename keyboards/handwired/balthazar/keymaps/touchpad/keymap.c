/*
BALTHAZAR 2020 turbo

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

/*
we have left and right split 7 cols
per each split col we have 11 rows
all 77 matrix nodes are used 
we could add another row
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

In the middle F6 and F7 act as mouse left and right buttons - above is touchpad 
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
 * row 1 = Esc, Grave, Tab, Caps, Shift, Ctrl, N, J, U, 7, F1
 * row 2 = F1,  1,     Q,   A,    Nubs,  Alt,  M, K, I, 8, F8
 * etc.
 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = { // 7x11 ISO
          { KC_ESC, KC_GRV, KC_TAB,  KC_CAPS, KC_LSFT, KC_LCTL,  KC_N,    KC_J,    KC_U,    KC_7,    KC_F7 },    
          { KC_F1,  KC_1,   KC_Q,    KC_A,    KC_NUBS, KC_LALT,  KC_M,    KC_K,    KC_I,    KC_8,    KC_F8 },
          { KC_F2,  KC_2,   KC_W,    KC_S,    KC_Z,    KC_LGUI,  KC_COMM, KC_L,    KC_O,    KC_9,    KC_F9 }, 
          { KC_F3,  KC_3,   KC_E,    KC_D,    KC_X,    KC_SPC,   KC_DOT,  KC_SCLN, KC_P,    KC_0,    KC_F10 },
          { KC_F4,  KC_4,   KC_R,    KC_F,    KC_C,    KC_LEFT,  KC_SLSH, KC_QUOT, KC_LBRC, KC_MINS, KC_F11  }, 
          { KC_F5,  KC_5,   KC_T,    KC_G,    KC_V,    KC_DOWN,  KC_UP,   KC_NUHS, KC_RBRC, KC_EQL,  KC_F12 },    
          { KC_F6,  KC_6,   KC_Y,    KC_H,    KC_B,    KC_RIGHT, KC_ALGR, KC_ENT,  KC_BSPC, KC_DEL,  KC_PSCR  },
  },        
  [1] = { // 7x11 ISO mouse layer
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_BTN2 },    
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }, 
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }, 
          { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },    
       { KC_MS_BTN1, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  }, 
   
};

// Movement Hook
// Process mouse movement in the keymap before it is sent to the host. Example uses include filtering noise, adding acceleration, and automatically activating a layer. 
void ps2_mouse_moved_user(report_mouse_t *mouse_report){
	// here we have sensed the movement and need to activate layer index 1 
	layer_on(1);
}

/*
 * We want to have F6 and F7 keys become Left and Right trackpad (mouse) buttons when cursor movement detected
 * number 6 KC_6 can be middle scrolling activator - when pushed and trackpad movement detected - scroll screen instead of cursor move 
 * this is done with additional layer having so-called transparent keys everywhere but on the L anad R mouse keys  
 * Valid ways to denote transparency on a given layer:
    KC_TRANSPARENT
    KC_TRNS (alias)
    _______ (alias)
    
    KC_MS_BTN1 	KC_BTN1 	Mouse Button 1
    KC_MS_BTN2 	KC_BTN2 	Mouse Button 2
    KC_MS_BTN3 	KC_BTN3 	Mouse Button 3  // should be middle button
**/

/**    
  Advanced option is keyboard as midi controller / step sequencer
  https://docs.qmk.fm/#/feature_sequencer
  
  Add the following line to your rules.mk:
  SEQUENCER_ENABLE = yes

  By default the sequencer has 16 steps, but you can override this setting in your config.h:
  #define SEQUENCER_STEPS 32

Resolutions

While the tempo defines the absolute speed at which the sequencer goes through the steps, the resolution defines the granularity of these steps (from coarser to finer).
Resolution 	Description
SQ_RES_2 	Every other beat
SQ_RES_2T 	Every 1.5 beats
SQ_RES_4 	Every beat
SQ_RES_4T 	Three times per 2 beats
SQ_RES_8 	Twice per beat
SQ_RES_8T 	Three times per beat
SQ_RES_16 	Four times per beat
SQ_RES_16T 	Six times per beat
SQ_RES_32 	Eight times per beat

Keycodes
Keycode 	Description
SQ_ON 		Start the step sequencer
SQ_OFF 	Stop the step sequencer
SQ_TOG 	Toggle the step sequencer playback
SQ_SALL 	Enable all the steps
SQ_SCLR 	Disable all the steps
SQ_S(n) 	Toggle the step n
SQ_TMPD 	Decrease the tempo
SQ_TMPU 	Increase the tempo
SQ_R(n) 	Set the resolution to n
SQ_RESD 	Change to the slower resolution
SQ_RESU 	Change to the faster resolution
SQ_T(n) 	Set n as the only active track or deactivate all  

**/
 

