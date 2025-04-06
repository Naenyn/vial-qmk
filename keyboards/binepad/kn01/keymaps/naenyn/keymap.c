/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
// #include "analog.h"
// #include "qmk_midi.h"
// #include "quantum/midi/midi_device.h"
extern MidiDevice midi_device;
extern midi_config_t midi_config;

enum {
    _L0,
    _L1
} keyboard_layers;

// !! Enum keys here, repeat in vial.json
enum naenyn_keycode {
    N_CC1_UP = QK_KB_0,
    N_CC1_DN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_ortho_1x1(
        LT(_L1, KC_MUTE)
    ),

    [_L1] = LAYOUT_ortho_1x1(
        _______
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_L0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_L1] = { ENCODER_CCW_CW(N_CC1_DN, N_CC1_UP) }  // !! <-- MAP KEYS HERE, OR IN VIAL
};

#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {

        // !! Each jey gets own functionality
		case N_CC1_UP:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 1, 65);
            }
            return false;
        case N_CC1_DN:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 1, 63);
            }
            return false;
	}

    return true;
}
