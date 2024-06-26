/*
Copyright 2024 Jurij Podgoršek <jurij@kompot.si>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef OLED_ENABLE

/*
static void print_status(void) {
     // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
*/

// Show logo (in custom font)
static void render_logo(void) {
    static const char PROGMEM balthazar_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(balthazar_logo, false);
}

// Possible states
enum boot_state {
    STATE_SPLASH = 0,
    STATE_PASSWORD_SET = 10,
    STATE_PASSWORD_SET_SUCCESS = 15,
    STATE_PASSWORD_ENTER = 20,
    STATE_PASSWORD_INVALID = 25,
    STATE_BOOT_MENU = 30,
    STATE_STARTING = 40
};

static uint16_t state_timer;
enum boot_state current_state = STATE_SPLASH;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return rotation;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Timer to show logo on start
    state_timer = timer_read();

    return rotation;
}

void progress_state(void) {
    switch (current_state) {
    case STATE_SPLASH:
        current_state = STATE_PASSWORD_SET;
        break;

    case STATE_PASSWORD_ENTER:
        // @TODO Check if pw ok!
        if (true) {
            current_state = STATE_BOOT_MENU;
        } else {
            current_state = STATE_PASSWORD_INVALID;
        }
        break;
    case STATE_PASSWORD_INVALID:
        current_state = STATE_PASSWORD_ENTER;
        break;
    case STATE_PASSWORD_SET:
        current_state = STATE_PASSWORD_SET_SUCCESS;
    case STATE_PASSWORD_SET_SUCCESS:
        current_state = STATE_BOOT_MENU;
        break;
    case STATE_BOOT_MENU:
        current_state = STATE_STARTING;
        break;
    case STATE_STARTING:
        // TODO actual boot!
        break;
    }
    state_timer = timer_read();
}

const int TRANSITION_TIME = 3000;
bool state_confirm = false;

bool oled_task_user(void) {
    switch (current_state) {

    // Show splash for 3 seconds
    case STATE_SPLASH:
        render_logo();
        oled_write_P(PSTR("Open hardware laptop"), false);
        if (timer_elapsed(state_timer) > TRANSITION_TIME) {
            progress_state();
        }
        break;

    case STATE_PASSWORD_ENTER:
        render_logo();
        oled_write_P(PSTR("Enter password: "), false);
        // @TODO capture input, compare with EEPROM
        break;

    case STATE_PASSWORD_SET:
        render_logo();
        oled_write_P(PSTR("Set new password: "), false);
        // @TODO capture input, save to EEPROM
        break;

    case STATE_PASSWORD_SET_SUCCESS:
        render_logo();
        oled_write_P(PSTR("Password set successfully!"), false);

        if (timer_elapsed(state_timer) > TRANSITION_TIME) {
            progress_state();
        }
        break;

    case STATE_PASSWORD_INVALID:
        render_logo();
        oled_write_P(PSTR("Invalid password. Try again"), false);

        if (timer_elapsed(state_timer) > TRANSITION_TIME) {
            progress_state();
        }
        break;

    case STATE_BOOT_MENU:
        if (state_confirm) {
            oled_write_P(PSTR("Choose boot option:"), false);
            // @TODO list options, keyboard selection
            progress_state();
        }
        break;

    case STATE_STARTING:
        oled_write_P(PSTR("Starting up."), false);
        if (timer_elapsed(state_timer) % 3000 > 1000) {
            oled_write_P(PSTR("."), false);
        }
        if (timer_elapsed(state_timer) % 3000 > 2000) {
            oled_write_P(PSTR("."), false);
        }
        break;
    }

    return false;
}

#endif // end OLED_ENABLE
