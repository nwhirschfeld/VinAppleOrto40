/* Copyright 2021 NWHirschfeld
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
  BLANK,
  AUML,
  OUML,  
  UUML,  
  SGER,
  DEMO
};

bool long_press_switcher(keyrecord_t *record, uint16_t shortkey, uint16_t longkey) {
    static uint16_t my_hash_timer;
    if(record->event.pressed) {
        my_hash_timer = timer_read();
    } else {
        if (timer_elapsed(my_hash_timer) < 200) {
            register_code(shortkey); 
            unregister_code(shortkey);// Change the character(s) to be sent on tap here
        } else {
            register_code(longkey); // Change the key to be held here
            unregister_code(longkey); // Change the key that was held here, too!
        }
        return false; // We handled this keypress
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BLANK:
            break;
        case AUML:
            long_press_switcher(record, KC_A, KC_QUOT); 
            break;
        case OUML:
            long_press_switcher(record, KC_O, KC_SCLN);  
            break;
        case UUML:
            long_press_switcher(record, KC_U, KC_LBRC);
            break;
        case SGER:
            long_press_switcher(record, KC_S, KC_MINS);
            break;
        case DEMO:
            SEND_STRING("DEMOTEST");
        default:
            break;
    }
    return true; 
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    UUML,    KC_I,    OUML,    KC_P,
        AUML,    SGER,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DOT,  KC_ENT,  KC_RSFT,
        KC_LCTL,     KC_LGUI,      KC_LALT,   MO(1),   KC_SPC,  MO(2),   KC_RALT,   KC_RCTL
    ),
    [1] = LAYOUT(
        KC_ESC,  XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_PGDN, KC_UP,   KC_PGUP, _______,
        KC_TAB,  XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_LEFT, KC_DOWN, KC_RGHT, _______,
        RESET,   XXXXXXX, KC_0,    KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX, _______, _______,
        _______,     _______,      _______,   XXXXXXX, _______, XXXXXXX, _______,   _______
    ),
    [2] = LAYOUT(
        KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUES, _______,
        KC_LT,   KC_GT,   DEMO, XXXXXXX, XXXXXXX, XXXXXXX, KC_EXLM, KC_COMM, _______, _______,
        _______,     _______,      _______,   XXXXXXX, _______, XXXXXXX, _______,   _______
    )
};
