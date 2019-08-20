#include QMK_KEYBOARD_H
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 2    /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000    /* Time (in ms) before the one shot key is released */
#define ______ KC_TRNS

#define LCTL_ MT(MOD_LCTL,KC_ESC)
#define RCTL_ MT(MOD_RCTL,KC_ESC)
#define SPACE LT(3,KC_SPC)
#define SH(x) LSFT(x)

bool has_layer_changed = false;
static uint8_t current_layer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Default US QWERTY
  [0] = LAYOUT_directional(
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_MINS, KC_EQL,  ______, KC_BSPC,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT, KC_UP,   KC_RGUI,
    LCTL_,  KC_LGUI,KC_LALT,                SPACE,  SPACE,  SPACE,          KC_RALT,RCTL_,   KC_LEFT, KC_DOWN, KC_RIGHT
    ),

  // Flipped numbers
  [1] = LAYOUT_directional(
    KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_UNDS, KC_PLUS, ______, ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,
    MO(2),  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  MO(2),   ______,  ______,
    ______, ______, ______,                 ______, ______, ______,         ______, ______,  ______,  ______,  ______
    ),

  // Shifted letters
  [2] = LAYOUT_directional(
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  KC_MINS, KC_EQL,  ______, ______,
    SH(KC_TAB), SH(KC_Q),   SH(KC_W),   SH(KC_E),   SH(KC_R),   SH(KC_T),   SH(KC_Y),   SH(KC_U),   SH(KC_I),   SH(KC_O),   SH(KC_P),  SH(KC_LBRC), SH(KC_RBRC), SH(KC_BSLS),
    SH(KC_CAPS),SH(KC_A),   SH(KC_S),   SH(KC_D),   SH(KC_F),   SH(KC_G),   SH(KC_H),   SH(KC_J),   SH(KC_K),   SH(KC_L),   SH(KC_SCLN), SH(KC_QUOT), SH(KC_ENT),
    SH(KC_LSFT),SH(KC_Z),   SH(KC_X),   SH(KC_C),   SH(KC_V),   SH(KC_B),   SH(KC_N),   SH(KC_M),   SH(KC_COMM),SH(KC_DOT), SH(KC_SLSH), SH(KC_RSFT), SH(KC_UP),   SH(KC_RGUI),
    SH(LCTL_),  SH(KC_LGUI),SH(KC_LALT),        SH(SPACE),  SH(SPACE),  SH(SPACE),      SH(KC_RALT),SH(RCTL_),   SH(KC_LEFT), SH(KC_DOWN), SH(KC_RIGHT)
    ),


  // F# Keys and PGUP/PGDN, HOME/END
  [3] = LAYOUT_directional(
    ______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  ______, RESET,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  KC_PGUP, ______,
    ______, ______, ______,                 TG(1),  TG(1),  TG(1),          ______, ______,  KC_HOME, KC_PGDN, KC_END
    ),
};

void matrix_scan_user(void){
    uint8_t layer = biton32(layer_state);
    if (current_layer == layer) {
        has_layer_changed = false;
    } else {
        has_layer_changed = true;
        current_layer = layer;
        if (layer == 0){
            rgblight_disable();
            rgblight_setrgb(0,0,0);
        }
        else {
            rgblight_enable();
            if (layer == 1 || layer == 2){
                rgblight_setrgb(255,0,0);
            }
            else if (layer == 3){
                rgblight_setrgb(0,255,0);
            }
        }
    }
}
/* vim: set expandtab noai ts=4 sw=4: */
