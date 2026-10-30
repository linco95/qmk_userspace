// Copyright 2026 Andreas Kjellqvist
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MASTER_LEFT

// Only tap-hold key is Tab/Esc; hold past this to get Esc.
#define TAPPING_TERM 200
// Replaces the removed TAPPING_FORCE_HOLD: no auto-repeat on tap-hold keys.
#define QUICK_TAP_TERM 0

// Sync key activity to the offhand half so both OLEDs and LEDs sleep together.
#define SPLIT_ACTIVITY_ENABLE

// Press both Shifts to capitalize the next word.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

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
