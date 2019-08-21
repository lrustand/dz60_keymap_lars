#include QMK_KEYBOARD_H
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 2    /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000    /* Time (in ms) before the one shot key is released */
#define ______ KC_TRNS

#define LCTL_ MT(MOD_LCTL,KC_ESC)
#define RCTL_ MT(MOD_RCTL,KC_ESC)
#define SPACE LT(3,KC_SPC)

static uint8_t current_layer;

static bool shift_pressed = false;
static bool numbers_flipped = false;

enum custom_keycodes {
    MY_GRV = SAFE_RANGE,
    MY_1,
    MY_2,
    MY_3,
    MY_4,
    MY_5,
    MY_6,
    MY_7,
    MY_8,
    MY_9,
    MY_0,
    MY_MINS,
    MY_EQL,

    MY_SHFT,
    MY_FN,
};

uint16_t my_number_row[] = {
    MY_GRV,
    MY_1,
    MY_2,
    MY_3,
    MY_4,
    MY_5,
    MY_6,
    MY_7,
    MY_8,
    MY_9,
    MY_0,
    MY_MINS,
    MY_EQL,
};

uint16_t number_row[] = {
    KC_GRV,
    KC_1,
    KC_2,
    KC_3,
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_0,
    KC_MINS,
    KC_EQL,
};

int find_in_array(uint16_t val, uint16_t arr[], int size) {
    int i;
    int s = size / sizeof(arr[0]);
    for(i=0; i<s; i++) {
        if(arr[i] == val)
            return i;
    }
    return -1;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Default US QWERTY
  [0] = LAYOUT_directional(
    MY_GRV, MY_1,   MY_2,   MY_3,   MY_4,   MY_5,   MY_6,   MY_7,   MY_8,   MY_9,   MY_0,    MY_MINS, MY_EQL,  ______, KC_BSPC,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
    MY_SHFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, MY_SHFT, KC_UP,   KC_RGUI,
    LCTL_,  KC_LGUI,KC_LALT,                SPACE,  SPACE,  SPACE,          KC_RALT,RCTL_,   KC_LEFT, KC_DOWN, KC_RIGHT
    ),

  [3] = LAYOUT_directional(
    ______, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,  ______, RESET,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,  ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  ______,
    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,  ______,  KC_PGUP, ______,
    ______, ______, ______,                 MY_FN,  MY_FN,  MY_FN,          ______, ______,  KC_HOME, KC_PGDN, KC_END
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    void (*reg)(uint8_t);
    void (*unreg)(uint8_t);
    bool keydown;

    // Determine if keydown or keyup should be sent
    if (record->event.pressed) {
        reg = &register_code;
        unreg = &unregister_code;
        keydown = true;
    } else {
        reg = &unregister_code;
        unreg = &register_code;
        keydown = false;
    }

    switch (keycode) {
    case MY_SHFT:
        shift_pressed = keydown;
        reg(KC_LSFT);
        return false;
    case MY_FN:
        if (keydown)
            numbers_flipped = !numbers_flipped;
        return false;
    }

    // Handle my custom number keys
    int number = find_in_array(keycode, my_number_row, sizeof(my_number_row));
    if (number != -1) {
        uint16_t key = number_row[number];

        // Release number key before releasing shift
        if (!keydown)
            reg(key);

        // Press or release shift if needed
        if (numbers_flipped) {
            if (shift_pressed)
                unreg(KC_LSFT);
            else
                reg(KC_LSFT);
        }

        // Press number key after pressing shift
        if (keydown)
            reg(key);
    }
    return true;
}


void matrix_scan_user(void){
    uint8_t layer = biton32(layer_state);
    if (current_layer != layer) {
        current_layer = layer;
        if (layer == 0){
            rgblight_disable();
            rgblight_setrgb(0,0,0);
        }
        else {
            rgblight_enable();
            if (layer == 3)
                rgblight_setrgb(255,0,0);
        }
    }
}
/* vim: set expandtab noai ts=4 sw=4: */
