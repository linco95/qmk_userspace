// Copyright 2026 Andreas Kjellqvist
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MASTER_LEFT

// Tap-hold keys: home row mods and Tab/Esc. Hold past this to get the hold action.
// Starting point from QMK's home row mods guide (docs/tap_hold.md).
#define TAPPING_TERM 250
// Replaces the removed TAPPING_FORCE_HOLD: no auto-repeat on tap-hold keys.
#define QUICK_TAP_TERM 0
// Mod activates when another key is pressed and released while it is held.
#define PERMISSIVE_HOLD
// Same-hand chords settle as taps, so rolls like "as" don't trigger mods.
#define CHORDAL_HOLD
// Tap-hold keys pressed within 150 ms of the previous letter are taps.
#define FLOW_TAP_TERM 150

// Sync key activity to the offhand half so both OLEDs and LEDs sleep together.
#define SPLIT_ACTIVITY_ENABLE

// Press both Shifts to capitalize the next word.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Mouse keys: constant speed instead of acceleration; hold MS_ACL1 for slow.
// Speed = offset px every interval ms (24 px / 16 ms ≈ 1500 px/s, 6 px ≈ 375 px/s).
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_UNMOD 24
#define MK_C_INTERVAL_UNMOD 16
#define MK_C_OFFSET_1 6
#define MK_C_INTERVAL_1 16
#define MK_W_INTERVAL_UNMOD 80 // 12 scroll steps/s; MS_ACL1 scrolls at 8/s

// crkbd font with the TimeEdit logo in place of the Corne logo.
#define OLED_FONT_H "te_glcdfont.c"

#ifdef RGB_MATRIX_ENABLE
// Solid teal at low brightness; no animations are compiled in.
// Applies on first boot or after an EEPROM reset; Adjust layer keys tweak it.
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#    define RGB_MATRIX_DEFAULT_HUE 128
#    define RGB_MATRIX_DEFAULT_SAT 255
#    define RGB_MATRIX_DEFAULT_VAL 80
#    define RGB_MATRIX_SLEEP
#    define RGB_MATRIX_TIMEOUT 600000 // 10 min idle
#endif
