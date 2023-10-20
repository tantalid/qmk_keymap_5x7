 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

#include "ukraine.c"


#define _QWERTY     0
#define _UA         1
#define _LOWER      2
#define _RAISE      3
#define _QWERTY2     4


enum custom_keycodes {
    SS_ARROW_FUNC = SAFE_RANGE,
    SS_THIS,
    SS_RETURN
};

// Basic macros
#define KC_LOWER   MO(_LOWER)
#define KC_RAISE   MO(_RAISE)

#define KC_UA_ALT  LM(_QWERTY2, MOD_LALT)
#define KC_UA_CTRL LM(_QWERTY2, MOD_LCTL)

// hot keys to toggle applications by number on windows bottom bar order, like LAT + TAB
#define KC_MSTEAMS LWIN(KC_8)
#define KC_BROWSER LWIN(KC_7)
#define KC_IDE     LWIN(KC_6)

#define COPY       LCTL(KC_C)
#define PASTE      LSFT(KC_INS)
#define CUT        LCTL(KC_X)
#define FIND       LCTL(KC_F)
#define FIND_ALL   LCTL(LSFT(KC_F))
#define COMMENT_LINE   C(KC_SLASH)
#define COMMENT_MULTI_LINE   LSFT(C(KC_SLASH))

#define LANG        A(KC_LSFT)
#define SEARCH_ALL  LCTL(LSFT(A(KC_6))) // Webstorm search all custom hot key


// TAP DANCE ------------------------------------------------------------------------------------
// Tap Dance declarations
// ACTION_TAP_DANCE_TAP_HOLD
//
enum tapDance {
    // tap dance items
    // ACTION_TAP_DANCE_TAP_HOLD
    TD_I_FIND,
    TD_I_COMMENT,
    // ACTION_TAP_DANCE_DOUBLE
    TD_I_ESC,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    qk_tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_I_FIND)...TD(TD_I_ESC):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case SS_ARROW_FUNC:
            if (record->event.pressed) {
                SEND_STRING("() => {}" SS_TAP(X_LEFT));
            }
            break;
        case SS_THIS:
            if (record->event.pressed) {
                SEND_STRING("this.");
            }
            break;
        case SS_RETURN:
            if (record->event.pressed) {
                SEND_STRING("return;");
            }
            break;
    }

    return true;
}

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
            #ifndef PERMISSIVE_HOLD
                && !state->interrupted
            #endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // [TD_I_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, TO(_QWERTY)),
    [TD_I_FIND] = ACTION_TAP_DANCE_TAP_HOLD(FIND, FIND_ALL),
    [TD_I_COMMENT] = ACTION_TAP_DANCE_TAP_HOLD(COMMENT_LINE, COMMENT_MULTI_LINE),
};
// #define TD_ESC           TD(TD_I_ESC)
#define TD_FIND          TD(TD_I_FIND)
#define TD_COMMENT       TD(TD_I_COMMENT)

// TAP DANCE END ------------------------------------------------------------------------------------

// COMBO ------------------------------------------------------------------------------------
enum comboEnum {
    CO_7_u,
    CO_LOWER_ENTER,

    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM u_7_combo[]    = {UA_HE, KC_7, COMBO_END};
const uint16_t PROGMEM enter_combo[]    = {KC_LOWER, KC_BSPC, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
  [CO_7_u] = COMBO(u_7_combo, UA_GE),
  [CO_LOWER_ENTER] = COMBO(enter_combo, KC_ENT),
};
// COMBO END ------------------------------------------------------------------------------------


// key_override ------------------------------------------------------------------------------------
// Add behavior for shift button
// MOD_MASK_CTRL
const key_override_t paste_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LOWER, SEARCH_ALL);

const key_override_t** key_overrides = (const key_override_t*[]){
    &paste_key_override,
    NULL
};

// key_override END ------------------------------------------------------------------------------------



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | / Bspc  /       \Space \  |RAISE |   .  |   ,  |  UA  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,        KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,       KC_7,    KC_8,    KC_9,    KC_0,      KC_EQL,
  KC_ESC,        KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,      KC_MINS,
  KC_TAB,        KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,
OSM(MOD_LSFT),   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, _______,    _______,KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_NUHS,
                 KC_LGUI,KC_LALT, KC_LCTL, KC_LOWER,KC_BSPC,          KC_SPC, KC_RAISE,   KC_DOT,  KC_COMM, TG(_UA)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,           KC_F3,          KC_F4,          KC_F5,        KC_F6,                              KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,
  KC_SLSH, KC_MSTEAMS,      KC_IDE,         KC_BROWSER,     SS_THIS,      SS_ARROW_FUNC,                      _______,    _______,    _______,    _______,    _______,   KC_MINS,
  KC_SPC,  S(KC_LBRC),      S(KC_9),        S(KC_0),        S(KC_RBRC),   SS_RETURN,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_SCLN, KC_QUOT,
  _______,  KC_EQL,         KC_MINS,        KC_PLUS,        KC_LBRC,      KC_RBRC,       _______,    _______, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT,  KC_SLSH, KC_NUHS,
                                                _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |   |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |--------|   |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  KC_F1,    KC_F2,   KC_F3,     KC_F4,   KC_F5,     KC_F6,                            KC_F7,        KC_F8,          KC_F9,          KC_F10,     KC_F11,         KC_F12,
  _______, _______,  _______,   _______, _______,  _______,                           KC_HOME,      KC_PGDN,        KC_PGUP,        KC_END,     _______,        _______,
  _______, _______,  _______,   KC_MPLY, KC_VOLD,  KC_VOLU,                           KC_LEFT,      KC_DOWN,        KC_UP,          KC_RGHT,    _______,        _______,
  _______, _______,  KC_DEL,    KC_PSCR, KC_INS,   KC_DEL,   _______,       _______,  LCTL(KC_LEFT),LCTL(KC_DOWN),  LCTL(KC_UP),LCTL(KC_RGHT),  _______,        _______,
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

/*(())
 * UA
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  '/₴ |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ї   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   й  |   ц  |   у  |   к  |   е  |                    |   н  |   г  |   ш  |   щ  |   з  |  х   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   ф  |   і  |   в  |   а  |   п  |-------.    ,-------|   р  |   о  |   л  |   д  |   ж  |  є   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   я  |   ч  |   с  |   м  |   и  |-------|    |-------|   т  |   ь  |   б  |   ю  |   /? |  Ы/Ё |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */

[_UA] = LAYOUT(
  UA_APOS,  KC_1,   KC_2,       KC_3,       KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    UA_YI,
  _______,  UA_YOT, UA_TSE,     UA_U,       UA_K,    UA_E,                                        UA_N,    UA_HE,   UA_SH,   UA_SHCH, UA_Z,    UA_KH,
  _______,  UA_F,   UA_I,       UA_V,       UA_A,    UA_P,                                        UA_R,    UA_O,    UA_L,    UA_D,    UA_ZH,   UA_YE,
  _______,  UA_YA,  UA_CHE,     UA_S,       UA_M,    UA_Y, _______,                       _______,UA_T,    UA_SOFT, UA_B,    UA_YU,   KC_SLSH, UA_YOYR,
           _______, KC_UA_ALT,  KC_UA_CTRL, _______, _______,                             _______, _______, _______, _______, _______
),


/*
 * QWERTY2 - for hot keys which use eng keys on _UA layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY2] = LAYOUT(
  KC_GRV,     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,       KC_7,    KC_8,    KC_9,    KC_0,      KC_EQL,
  _______,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,      KC_MINS,
  _______,    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,
  _______,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, _______,    _______,KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_NUHS,
                 _______,_______, _______, _______,_______,          _______, _______, _______,  _______, _______
),

};


#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);

// _UA,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_ua_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 58, HSV_YELLOW}
);
// _LOWER,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_lower_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 58, HSV_BLUE}
);
// _RAISE,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_raise_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 58, HSV_MAGENTA}
);
// QWERTY2,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty2_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 58, HSV_WHITE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights,
	layer_ua_lights,// overrides layer 1
	layer_lower_lights,
    layer_raise_lights
);

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
	rgblight_set_layer_state(1, layer_state_cmp(state, _UA));
	rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
	rgblight_set_layer_state(4, layer_state_cmp(state, _QWERTY2));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way
}
#endif
