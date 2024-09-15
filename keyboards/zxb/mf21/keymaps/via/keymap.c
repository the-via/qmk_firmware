/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>

#define layer_led_index 21

enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4
};

typedef union {
    uint32_t raw;
    struct {
        bool rgb_endble:1;
    };
} user_config_t;

user_config_t user_config;
#define USE_RGB_BLACK       0x00, 0x00, 0x00
#define USE_RGB_BLUE        0x00, 0x00, 0x90
#define USE_RGB_GREEN       0x60, 0x60, 0x00
#define USE_RGB_ORANGE      0x90, 0x40, 0x00
#define USE_RGB_RED         0x90, 0x00, 0x00
#define USE_RGB_WHITE       0x60, 0x60, 0x60
#define USE_RGB_YELLOW      0x80, 0x80, 0x00
#define USE_RGB_OFF         USE_RGB_BLACK

#define   RESET  QK_KB_0

#define LTS LT(4,KC_PMNS)

layer_state_t  layer_state;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BASE]=LAYOUT(
		KC_ESC,  KC_CALC, KC_EQL, KC_BACKSPACE,
		KC_NUM,  KC_PSLS, KC_PAST,LTS,
		KC_P7,   KC_P8,   KC_P9,
		KC_P4,   KC_P5,   KC_P6,  KC_PPLS,
		KC_P1,   KC_P2,   KC_P3,
		KC_P0,   KC_PDOT, KC_PENT),

  [_FN1]=LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

  [_FN2]=LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

  [_FN3]=LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS),

   [_FN4]=LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		RGB_HUI, RGB_VAI, RGB_MOD,
		RGB_SPD, RGB_TOG, RGB_SPI, KC_TRNS,
		RGB_HUD, RGB_VAD, RGB_RMOD,
		RESET,  KC_TRNS, EE_CLR)

};

void mf21_update_rgb_mode(void) {
    if(!user_config.rgb_endble)
      {
        for(uint8_t i=0;i<21;i++)
            {
             rgb_matrix_set_color(i, USE_RGB_OFF);
            }
        }
   }
void mf21_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
   }

void keyboard_post_init_user(void) {
    mf21_get_rgb_mode();
  }

void eeconfig_init_user(void) {
    // EEPROM is getting reset!
    user_config.raw = 0;
    mf21_update_rgb_mode();
  }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                user_config.rgb_endble=!user_config.rgb_endble;
                eeconfig_update_kb(user_config.raw);
            }
            return false;
        case RESET:
            if (record->event.pressed) {
                bootloader_jump();
            }
        return false;
        default:
            return true;
          }
 return true;
}

bool rgb_matrix_indicators_user(void)
{
  mf21_update_rgb_mode();
  switch(get_highest_layer(layer_state)) {
        case _BASE:
           rgb_matrix_set_color(layer_led_index, USE_RGB_OFF);
          break;
        case _FN1:
           rgb_matrix_set_color(layer_led_index, USE_RGB_RED);
          break;
        case _FN2:
           rgb_matrix_set_color(layer_led_index, USE_RGB_GREEN);
          break;
        case _FN3:
           rgb_matrix_set_color(layer_led_index, USE_RGB_BLUE);
          break;
        case _FN4:
           rgb_matrix_set_color(layer_led_index, USE_RGB_WHITE);
          break;
        default:
          break;
  }
  return false;
}
