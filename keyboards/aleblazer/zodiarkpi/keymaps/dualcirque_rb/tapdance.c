//. Example 5: Using tap dance for advanced mod-tap and layer-tap keys
//  https://docs.qmk.fm/features/tap_dance#example-5

/*Tap dance can be used to emulate MT() and LT() behavior when the tapped code is not a basic keycode. This is useful to send tapped keycodes that normally require Shift, such as parentheses or curly braces—or other modified keycodes, such as Control + X.
Below your layers and custom keycodes, add the following:
Wrap each tapdance keycode in TD() when including it in your keymap, e.g. TD(ALT_LP)*/


// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3)  {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    } else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void td_alt_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LALT);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_TAP: // Allow double tap of keys
            register_code16(KC_LALT);
            register_code16(KC_LALT);
            break;
        case TD_DOUBLE_HOLD: // Allow nesting of 2 parens `((` within tapping term
            layer_on(_NUMPAD);
            register_mods(MOD_BIT(KC_LALT));
            break;
        default:
            break;
    }
}

void td_alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LALT);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_LALT);
            break;
        case TD_DOUBLE_HOLD: // Allow nesting of 2 parens `((` within tapping term
            layer_off(_NUMPAD);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_alt_finished, td_alt_reset),
    [TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, C(A(KC_DEL))),
    [TD_BSPC] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, C(KC_BSPC)),
};
