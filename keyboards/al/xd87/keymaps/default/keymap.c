#include QMK_KEYBOARD_H

const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("Poop", 0x1F923),                // 🤣
    UCIS_SYM("alpha", 0x03B1),                // 🤣
    UCIS_SYM("alpha1", 0x1F4A9),                // 🤣
    UCIS_SYM("Alpha", 0x0391)
);


enum my_keycodes {
  STR_LTX = SAFE_RANGE
};

enum layers {
  __DEFAULT,
  __LATEX,
  __CONFIG
};

// Muy largo si no
#define __ltc (LT(__CONFIG,KC_APP))
#define __tgl (TG(__LATEX))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [__DEFAULT] = LAYOUT_tkl_ansi(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,  KC_F4,    KC_F5,    KC_F6,  KC_F7,   KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR, KC_SCRL, KC_PAUS,
    KC_GRV,   KC_1,     KC_2,     KC_3,   KC_4,     KC_5,     KC_6,   KC_7,    KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_INS,  KC_HOME,  KC_PGUP, 
    KC_TAB,   KC_Q,     KC_W,     KC_E,   KC_R,     KC_T,     KC_Y,   KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,  KC_END,   KC_PGDN, 
    KC_CAPS,  KC_A,     KC_S,     KC_D,   KC_F,     KC_G,     KC_H,   KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT, 
    KC_LSFT,  KC_Z,     KC_X,     KC_C,   KC_V,     KC_B,     KC_N,   KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP, 
    KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC, KC_RALT,  KC_RGUI,  __ltc,  KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  [__LATEX] = LAYOUT_tkl_ansi(
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, STR_LTX, _______, _______, _______, 
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [__CONFIG] = LAYOUT_tkl_ansi(
    QK_RBT, KC_F13,   KC_F14, KC_F15,   KC_F16,   KC_F17, KC_F18,   KC_F19, KC_F20,   KC_F21,   KC_F22, KC_F23,   KC_F24,   KC_NO, KC_NO, QK_BOOT, 
    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_BRID,  KC_BRIU,  KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,  
    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,  KC_NO,    __tgl,    KC_NO,  KC_NO,    KC_NO,
    KC_NO,  KC_UNDO,  KC_CUT, KC_COPY,  KC_PSTE,  KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_VOLU, 
    KC_NO,  KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  _______,  KC_NO,  KC_MPRV,  KC_VOLD,  KC_MNXT
  )
};



#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


// Teclas custom
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case STR_LTX:
      if (record->event.pressed) { // pressed
      } else { // released
        ucis_start();
      }
      break;
  }
  return true;
}


