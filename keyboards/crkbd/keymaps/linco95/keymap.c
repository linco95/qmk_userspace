// Copyright 2019 @foostan
// Copyright 2020 Drashna Jaelre <@drashna>
// Copyright 2026 Andreas Kjellqvist
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>

// MACROS

enum custom_keycodes {
    OPENTERMINAL = SAFE_RANGE,
    SWEDISH_AA,
    SWEDISH_AE,
    SWEDISH_OE,
};
#define CC_OTRL OPENTERMINAL
#define sweAA SWEDISH_AA
#define sweAE SWEDISH_AE
#define sweOE SWEDISH_OE

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

// LAYERS
enum crkbd_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT, KC_BSPC,   MO(2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, CC_OTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   sweAA,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_MPLY, KC_MNXT,   sweOE,   sweAE, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,  KC_DEL,   MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, KC_BSPC, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11,  KC_F12,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, KC_BSPC, _______
                                      //`--------------------------'  `--------------------------'
  )
};
// clang-format on

#ifdef OLED_ENABLE
// Rotation of the offhand display and the keylog are handled by keyboards/crkbd/crkbd.c.

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
        default:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

void oled_render_TE_logo(void) {
    // clang-format off
        static const char PROGMEM te_logo[] = {// 'TImeeditTE', 128x32px
                                           0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0x03, 0x03, 0x03, 0xe3, 0xe3, 0xe3, 0xe7, 0x03, 0x03, 0x03, 0x63, 0x63, 0x63, 0x63, 0x63, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xe3, 0xe3, 0xe3, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x70, 0xf0, 0xe0, 0xe0, 0xc0, 0xe0, 0x60, 0x70, 0xf0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0x60, 0x70, 0x70, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x03, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf0, 0x70, 0x60, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe3, 0xe7, 0xe3, 0x00, 0x00, 0x60, 0xff, 0xff, 0xff, 0xff, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00,
                                           0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x8c, 0x9c, 0x9c, 0x9c, 0x9c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xe6, 0xc6, 0x86, 0x86, 0xc6, 0xe7, 0xe7, 0x67, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x00, 0x3f, 0xff, 0xff, 0xf1, 0xc0, 0xc0, 0xc0, 0xc0, 0xe1, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    oled_write_raw_P(te_logo, sizeof(te_logo));
    // clang-format on
}

static void oled_render_custom_text(void) {
    char wpm_str[10];
    snprintf(wpm_str, sizeof(wpm_str), "WPM: %03d", get_current_wpm());

    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("Andreas Kjellqvist"), false);
    oled_write_ln(wpm_str, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_custom_text();
        oled_render_layer_state();
    }
    // Skip the keyboard-level default rendering.
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case CC_OTRL:
            SEND_STRING(SS_LCTL(SS_LSFT("5")));
            return false;
        case SWEDISH_AA:
            send_swedish_char(LALT(KC_A), KC_NO);
            return false;
        case SWEDISH_AE:
            send_swedish_char(KC_A, LALT(KC_U));
            return false;
        case SWEDISH_OE:
            send_swedish_char(KC_O, LALT(KC_U));
            return false;
    }

    return true;
}
