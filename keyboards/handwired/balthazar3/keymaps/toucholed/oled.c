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

#include "md5.c"

char md5chars[] = "0123456789abcdef";

#define PASSWORD_MAX_LEN 32

char entryBuffer[PASSWORD_MAX_LEN] = {};
int entryBufferIndex = 0;
uint8_t entryHash[16];

// EEPROM space to store password (hash)
typedef struct PACKED {
  bool password_set;
  uint8_t password_hash[16];
} balthazar_config_t;

balthazar_config_t balthazar_config;

char *sumhex;
char * md5str (uint8_t *hash) {
  char *result = (char *)malloc(33 * sizeof(char));
  sprintf(result, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
          hash[0],
          hash[1],
          hash[2],
          hash[3],
          hash[4],
          hash[5],
          hash[6],
          hash[7],
          hash[8],
          hash[9],
          hash[10],
          hash[11],
          hash[12],
          hash[13],
          hash[14],
          hash[15]);
  result[32] = '\0';
  return result;
}

// read EEPROM
void keyboard_post_init_kb(void) {
  eeconfig_read_kb_datablock(&balthazar_config);

  // Call user init
  keyboard_post_init_user();
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  balthazar_config.password_set = false;
  memset(&balthazar_config.password_hash, 0, sizeof(balthazar_config.password_hash));
  // Save to eeprom
  eeconfig_update_kb_datablock(&balthazar_config);

  eeconfig_init_user();
}

// Print password (using * to conceal password)
void printEntryBufferR(char replaceChar) {
  for (int i = 0; i < sizeof entryBuffer; i++) {
    if (entryBuffer[i] != '\0') {
      if (replaceChar == '\0') {
        oled_write_char(entryBuffer[i], false);
      } else {
        oled_write_char('*', false);
      }
    }
  }
}
void printEntryBuffer(void) {
  printEntryBufferR('\0');
}

void clearEntryBuffer(void) {
  memset(&entryBuffer, 0, sizeof(entryBuffer));
}

void savePassword(void) {
  // Save password hash to EEPROM
  md5String(entryBuffer, entryHash);
  // Copy to config
  memcpy(&balthazar_config.password_hash, &entryHash, sizeof(balthazar_config.password_hash));
  balthazar_config.password_set = true;

  // Save config to EEPROM
  eeconfig_update_kb_datablock(&balthazar_config);
}

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

bool check_password(void) {
  // Hash the entry buffer
  md5String(entryBuffer, entryHash);

  // Compare with EEPROM stored hash
  for (int i = 0; i < 16; i++) {
    if (entryHash[i] != balthazar_config.password_hash[i]) {
      return false;
    }
  }
  return true;
  // Faster?
  return memcmp(&entryHash, &balthazar_config.password_hash, sizeof(entryHash)) == 0;
}

void progress_state(void) {
  switch (current_state) {
  case STATE_SPLASH:
    oled_clear();
    current_state =
      // @TODO testing
      (balthazar_config.password_set == true)
    //false
      // If password is set, show entry prompt
      ? STATE_PASSWORD_ENTER
      // Otherwise, set a new password
      : STATE_PASSWORD_SET;
    break;

  case STATE_PASSWORD_ENTER:
    oled_clear();
    current_state =
      (check_password())
      ? STATE_BOOT_MENU
      : STATE_PASSWORD_INVALID;
    break;

  case STATE_PASSWORD_INVALID:
    oled_clear();
    current_state = STATE_PASSWORD_ENTER;
    break;

  case STATE_PASSWORD_SET:
    savePassword();
    clearEntryBuffer();
    oled_clear();
    current_state = STATE_PASSWORD_SET_SUCCESS;
    break;

  case STATE_PASSWORD_SET_SUCCESS:
    clearEntryBuffer();
    oled_clear();
    // @TODO testing
    current_state = STATE_PASSWORD_ENTER;
    //current_state = STATE_PASSWORD_SET;
    break;

  case STATE_BOOT_MENU:
    oled_clear();
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
    oled_write_ln_P(PSTR("Enter password:"), false);
    printEntryBufferR('*');
    break;

  case STATE_PASSWORD_SET:
    /*
    sumhex = md5str(balthazar_config.password_hash);
  for (int i = 0; i < 32; i++) {
    oled_write_char((char) sumhex[i], false);
  }
  */
    oled_write_ln_P(PSTR("No password found."), false);
    oled_write_ln_P(PSTR("Set new password:"), false);
    printEntryBufferR('*');
    break;

  case STATE_PASSWORD_SET_SUCCESS:
    oled_write_ln_P(PSTR("New password set!"), false);

    /*
    sumhex = md5str(entryHash);
  for (int i = 0; i < 32; i++) {
    oled_write_char((char) sumhex[i], false);
  }
  */
    /*
    for (int i = 0; i < sizeof(entryHash); i++) {
      oled_write_char(md5chars[i], false);
    }
    */

    if (timer_elapsed(state_timer) > TRANSITION_TIME) {
      progress_state();
    }
    break;

  case STATE_PASSWORD_INVALID:
    oled_write_ln_P(PSTR("Invalid password."), false);
    oled_write_ln_P(PSTR("Try again."), false);
    clearEntryBuffer();

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

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (current_state) {

  case STATE_PASSWORD_ENTER:
  case STATE_PASSWORD_SET:
    // Password input states
    if (record->event.pressed) {
      // Backspace?
      if (keycode == KC_BSPC && entryBufferIndex > 0) {
        entryBuffer[entryBufferIndex] = '\0';
        entryBufferIndex -= 1;
        // Submit entry
      } else if (keycode == KC_ENT || keycode == KC_T) {
        progress_state();
        // Save current character
      } else if (keycode < 60) {
        // @TODO broaden from lowercase chars and numbers
        entryBuffer[entryBufferIndex] = code_to_name[keycode];
        entryBufferIndex += 1;
      }
    }

    return false;

  case STATE_SPLASH:
  case STATE_PASSWORD_INVALID:
  case STATE_PASSWORD_SET_SUCCESS:
    // Just ignore input in these states
    return false;

  case STATE_BOOT_MENU:
    // @TODO choose boot option

  case STATE_STARTING:
    // Pass input through normally otherwise
    return true;
  }

  return true;
}

#endif // end OLED_ENABLE
