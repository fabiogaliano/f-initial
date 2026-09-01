# League of Legends layers — history

Removed from `keymap.c` in the 7-layer redesign (DESIGN.md, Rejected), then restored
as the temporary LoL stack in the current keymap. This file preserves the original
Oryx version: layer 7 (layer switcher), 9 (LoL base), 10 (LoL alt/smartcast), and
11 (LoL chat).

Full original file: `git show 6d06790:keymap.c`.

## Layer 7 — layer switcher

```c
  [7] = LAYOUT_voyager(
    TO(0),          TO(2),          TO(3),          TO(1),          TO(4),          TO(5),                                          TO(6),          KC_NO,          KC_NO,          KC_NO,          KC_NO,          TO(9),
    KC_NO,          RGB_SPI,        RGB_SAI,        RGB_VAI,        RGB_HUI,        RGB_MODE_FORWARD,                               RGB_TOG,        KC_NO,          KC_MEDIA_PREV_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,
    KC_NO,          RGB_SPD,        RGB_SAD,        RGB_VAD,        RGB_HUD,        RGB_SLD,                                        TOGGLE_LAYER_COLOR,KC_NO,        KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE, KC_AUDIO_VOL_UP,KC_NO,          KC_NO,          KC_LEFT_GUI,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
```

Reached by double-tapping `TD(DANCE_0)` on the bottom-right key. `TO(9)` on the
top-right entered the LoL stack.

## Layer 9 — LoL base

```c
  [9] = LAYOUT_voyager(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_NO,          KC_NO,          KC_T,           KC_NO,          KC_NO,          TO(0),
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_6,                                           KC_Y,           KC_U,           KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    MO(10),         KC_Z,           KC_NO,          CHAT_ENTER,     KC_V,           KC_B,                                           KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          TD(DANCE_0),
                                                    KC_SPACE,       KC_LEFT_CTRL,                                   KC_P,           KC_NO
  ),
```

## Layer 10 — LoL smartcast (hold left outer row 3)

```c
  [10] = LAYOUT_voyager(
    KC_TRANSPARENT, LALT(KC_1),     LALT(KC_2),     LALT(KC_3),     LALT(KC_4),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LALT(KC_Q),     LALT(KC_W),     LALT(KC_E),     LALT(KC_R),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_D),     LALT(KC_F),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_P,                                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
```

## Layer 11 — LoL chat

```c
  [11] = LAYOUT_voyager(
    CHAT_CANCEL,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    CHAT_SEND,      KC_TRANSPARENT,                                 KC_BSPC,        KC_TRANSPARENT
  ),
```

## Chat flow keycodes

```c
enum custom_keycodes {
  CHAT_ENTER,   // Enter, then jump to the chat layer
  CHAT_SEND,    // Enter, then back to the LoL base layer
  CHAT_CANCEL,  // Escape, then back to the LoL base layer
};

    case CHAT_ENTER:
      if (record->event.pressed) {
        tap_code16(KC_ENTER);
        layer_move(11);
      }
      return false;
    case CHAT_SEND:
      if (record->event.pressed) {
        tap_code16(KC_ENTER);
        layer_move(9);
      }
      return false;
    case CHAT_CANCEL:
      if (record->event.pressed) {
        tap_code16(KC_ESCAPE);
        layer_move(9);
      }
      return false;
```

## Current adaptation

The current keymap assigns `LOL`, `LOL_SMARTCAST`, and `LOL_CHAT` to layers 7–9.
`LOL_TOGGLE` on the bottom-right key uses a double-tap toggle, replacing the old
layer switcher and its `TO(9)` entry. Smartcast is `MO(LOL_SMARTCAST)`. Chat uses
`layer_on(LOL_CHAT)` and `layer_off(LOL_CHAT)` rather than `layer_move()`, which
preserves the toggled LoL layer when chat opens and closes.
