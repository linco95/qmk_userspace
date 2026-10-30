// Copyright 2019 @foostan
// Copyright 2020 Drashna Jaelre <@drashna>
// Copyright 2026 Andreas Kjellqvist
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// LAYERS
enum crkbd_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

// MACROS

enum custom_keycodes {
    SE_AA = SAFE_RANGE,
    SE_AE,
    SE_OE,
};
// Tap for Tab, hold for Esc. Hold action is overridden in process_record_user.
#define TAB_ESC LT(0, KC_TAB)

// Home row mods, CAGS order: Ctrl, Option, Cmd, Shift from the pinky inwards.
#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)
#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L RALT_T(KC_L)
#define HM_SCLN RCTL_T(KC_SCLN)
// Tap for G, hold for the mouse layer.
#define G_MOUSE LT(_MOUSE, KC_G)

// SWEDISH CHARACTERS
//
// Typed as macOS US-layout Option sequences instead of Unicode Hex Input
// (UC_MAC). Unicode Hex Input holds Option while tapping four hex digits, and
// Chromium-based browsers drop the last digit; macOS then zero-pads the
// partial code point, so ä/Ä arrive as à/À and ö/Ö as garbage.

#define SWEDISH_TAP_DELAY 15

static void send_swedish_char(uint16_t base_key, uint16_t dead_key) {
    const uint8_t saved_mods   = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    const bool    shifted      = (saved_mods | oneshot_mods) & MOD_MASK_SHIFT;

    clear_mods();
    clear_oneshot_mods();

    if (dead_key != KC_NO) {
        tap_code16(dead_key);
        wait_ms(SWEDISH_TAP_DELAY);
    }
    tap_code16(shifted ? S(base_key) : base_key);
    wait_ms(SWEDISH_TAP_DELAY);

    set_mods(saved_mods);
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      TAB_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    HM_A,    HM_S,    HM_D,    HM_F, G_MOUSE,                         KC_H,    HM_J,    HM_K,    HM_L, HM_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_LOWR,  KC_SPC,     KC_ENT, KC_BSPC, TL_UPPR
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   SE_AA,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_MPLY, KC_MNXT,   SE_OE,   SE_AE, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,  KC_DEL, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11,  KC_F12,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, KC_BSPC, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Held via G. Right hand: scroll on Y U I O, move on H J K L, click on N M ,
  // Left thumb clicks too (Space = left, Lower = right, GUI = middle), so a
  // button can be held for dragging while the right hand moves the cursor.
  // Outer left Shift position = hold for slow movement (Shift on F stays Shift).
  [_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_WHLL, MS_WHLU, MS_WHLD, MS_WHLR, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MS_ACL1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MS_BTN3, MS_BTN2, MS_BTN1,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

// Shift + Backspace sends Delete.
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &delete_key_override,
};

// Thumb keys are exempt from Chordal Hold's opposite-hands rule, so a home row
// mod still holds when combined with Space or a layer key on the same hand.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x6_3(
    'L', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*',      '*', '*', '*'
);
// clang-format on

#ifdef OLED_ENABLE
// Rotation of the offhand display is handled by keyboards/crkbd/crkbd.c.

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
    }
}

// TimeEdit logo, 21x4 tiles of glyphs 0x80-0xB0 in te_glcdfont.c.
static void oled_render_te_logo(void) {
    // clang-format off
    static const char PROGMEM te_logo[] = {
        0x80, 0x81, 0x81, 0x81, 0x82, 0x83, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x99, 0x9a, 0x9b, 0x9c,
        0x81, 0x9d, 0x9e, 0x9f, 0xa0, 0x89, 0x20, 0xa1, 0x20, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad,
        0xae, 0x81, 0x81, 0x81, 0xaf, 0xb0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0
    };
    // clang-format on
    oled_write_P(te_logo, false);
}

static void oled_render_custom_text(void) {
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("Andreas Kjellqvist"), false);
    oled_write_P(PSTR("WPM: "), false);
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
}

bool oled_task_user(void) {
    // The driver's own timeout tracks screen updates and local keypresses only,
    // so the static logo would sleep early and never wake from the other half.
    // Drive power from input activity instead, which SPLIT_ACTIVITY_ENABLE syncs.
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }
    oled_on();

    if (is_keyboard_master()) {
        oled_render_custom_text();
        oled_render_layer_state();
    } else {
        oled_render_te_logo();
    }
    // Skip the keyboard-level default rendering.
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == TAB_ESC) {
        if (record->event.pressed && !record->tap.count) {
            tap_code(KC_ESC);
            return false;
        }
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case SE_AA:
            send_swedish_char(LALT(KC_A), KC_NO);
            return false;
        case SE_AE:
            send_swedish_char(KC_A, LALT(KC_U));
            return false;
        case SE_OE:
            send_swedish_char(KC_O, LALT(KC_U));
            return false;
    }

    return true;
}
