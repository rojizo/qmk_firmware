#include QMK_KEYBOARD_H
#include "latex.h"

#define UNICODE_TIMEOUT (1000)

static uint16_t idle_timer = 0;

enum my_keycodes {
  STR_LTX = SAFE_RANGE,
  MY_BOOT,
  MY_RBT, 
  MY_EECLR
};

enum layers {
  __DEFAULT,
  __CONFIG
};

// Muy largo si no
#define __ltc (LT(__CONFIG,KC_APP))
//#define __tgl (ACTION_TAP_DANCE_DOUBLE(STR_LTX, KC_RCTL))

#define __tgl STR_LTX


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [__DEFAULT] = LAYOUT_tkl_ansi(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,  KC_F4,    KC_F5,    KC_F6,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR, KC_SCRL, KC_PAUS,
    KC_GRV,   KC_1,     KC_2,     KC_3,   KC_4,     KC_5,     KC_6,   KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_INS,  KC_HOME,  KC_PGUP, 
    KC_TAB,   KC_Q,     KC_W,     KC_E,   KC_R,     KC_T,     KC_Y,   KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,  KC_END,   KC_PGDN, 
    KC_CAPS,  KC_A,     KC_S,     KC_D,   KC_F,     KC_G,     KC_H,   KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT, 
    KC_LSFT,  KC_Z,     KC_X,     KC_C,   KC_V,     KC_B,     KC_N,   KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP, 
    KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC, KC_RALT,  KC_RGUI,  __ltc,  STR_LTX,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  [__CONFIG] = LAYOUT_tkl_ansi(
    KC_NO,   KC_F13,   KC_F14, KC_F15,   KC_F16,   KC_F17, KC_F18,   KC_F19, KC_F20,   KC_F21,   KC_F22, KC_F23,   KC_F24,  MY_RBT, MY_EECLR, MY_BOOT,    
    KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,   KC_NO,  BL_TOGG,  BL_ON,   BL_UP, 
    KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,   KC_NO,  BL_BRTG,  BL_OFF,  BL_DOWN,  
    KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,
    _______, KC_NO,   KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_VOLU, 
    _______, _______, _______,  KC_NO,    KC_NO,    KC_NO,  _______,  KC_NO,  KC_MPRV,  KC_VOLD,  KC_MNXT
  )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


// Teclas custom
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (timer_elapsed(idle_timer) > UNICODE_TIMEOUT) {
    if(ucis_active()) {
      ucis_cancel();
    }
  }
  idle_timer = timer_read();

  switch (keycode) {
    case STR_LTX:
      if (!record->event.pressed) {
        if (ucis_active()) {
          ucis_finish();
          wait_ms(50);
        }
        ucis_start();
      }
      return false;
    case MY_BOOT:
      if (!record->event.pressed) { // On release
        if (get_mods() == ( MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | 
                            MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)   )) {
          reset_keyboard();
        }
      }
      return false;
    case MY_RBT:
      if (!record->event.pressed) { // On release
        if (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)) ) {
          soft_reset_keyboard();
        }
      }
      return false;
    case MY_EECLR:
      if (!record->event.pressed) { // On release
        if (get_mods() == ( MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) | 
                            MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)   )) {
#ifdef NO_RESET
                eeconfig_init();
#else
                eeconfig_disable();
                soft_reset_keyboard();
#endif
        }
      }
      return false;

    default:
      return true;
  }
}

