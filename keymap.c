#include QMK_KEYBOARD_H
#include "version.h"

#include "features/achordion.h"
#include "features/select_word.h"

enum layers {
  BASE,
  NAV,
  NUM,
  SYM,
  ACC,
  MEDIA,
  MOUSE,
};

// ML_SAFE_RANGE, not SAFE_RANGE: the Voyager itself claims the first two slots
// for TOGGLE_LAYER_COLOR and LED_LEVEL.
enum custom_keycodes {
  WISPR = ML_SAFE_RANGE,  // Wispr Flow push-to-talk: F13, held while the key is.
  CLAVIER,
  SELWORD,
  SELLINE,
  // Portuguese accents via macOS dead keys.
  PT_AACU,  // á
  PT_AGRV,  // à
  PT_ACIR,  // â
  PT_ATIL,  // ã
  PT_EACU,  // é
  PT_ECIR,  // ê
  PT_IACU,  // í
  PT_OACU,  // ó
  PT_OCIR,  // ô
  PT_OTIL,  // õ
  PT_UACU,  // ú
  PT_EURO,  // €
};

uint16_t SELECT_WORD_KEYCODE = SELWORD;
uint16_t SELECT_LINE_KEYCODE = SELLINE;

// Home row mods, mirrored finger for finger. The right hand rests on H-J-K-L,
// one column inward from the usual J-K-L-semicolon, so the mirror is taken
// across the fingers rather than across the physical halves:
//
//   pinky ring mid index │ index mid ring pinky
//     A    S    D    F   │   H    J    K    L
//    Cmd  Opt  Ctrl Shft │  Shft Ctrl Opt  Cmd
//
// Strongest finger carries the most-used modifier on both hands, weakest the
// least-used. Shift on the index also means an inward roll can never end on a
// held Shift, so fast rolls cannot produce stray capitals.
#define HM_A MT(MOD_LGUI, KC_A)
#define HM_S MT(MOD_LALT, KC_S)
#define HM_D MT(MOD_LCTL, KC_D)
#define HM_F MT(MOD_LSFT, KC_F)
#define HM_H MT(MOD_RSFT, KC_H)
#define HM_J MT(MOD_RCTL, KC_J)
#define HM_K MT(MOD_RALT, KC_K)
#define HM_L MT(MOD_RGUI, KC_L)

// The tapped letters sit where the old layout had them: Space on the right
// inner thumb, Enter on the left inner, Tab on the left outer. The layers do
// NOT follow them. NAV stays on a left thumb so its arrow cluster on the right
// hand is still an opposite-hand reach, and Media stays a two-left-thumb chord.
#define LT_NAV LT(NAV, KC_ENT)
#define LT_NUM LT(NUM, KC_TAB)
#define LT_SYM LT(SYM, KC_BSPC)
#define LT_ACC LT(ACC, KC_SPC)

// Shottr captures, on the Nav layer at the digit positions the user already
// knows. They moved off Base so the top row can be plain digits for Aerospace's
// ⌥1-⌥4 workspace switching.
#define SHOTTR1 HYPR(KC_1)
#define SHOTTR2 HYPR(KC_2)
#define SHOTTR3 HYPR(KC_3)

// ç is a single macOS combination, so Shift composes Ç for free.
#define PT_CCED LALT(KC_C)

#define NAV_UND LGUI(KC_Z)
#define NAV_RDO LGUI(LSFT(KC_Z))
#define NAV_CUT LGUI(KC_X)
#define NAV_CPY LGUI(KC_C)
#define NAV_PST LGUI(KC_V)
#define NAV_ALL LGUI(KC_A)
#define NAV_BCK LGUI(KC_LBRC)
#define NAV_FWD LGUI(KC_RBRC)
#define NAV_TBP LGUI(LSFT(KC_LBRC))
#define NAV_TBN LGUI(LSFT(KC_RBRC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_voyager(
    WISPR,          KC_1,           KC_2,           KC_3,           KC_4,           KC_NO,                                      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_HYPR,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    CLAVIER,        HM_A,           HM_S,           HM_D,           HM_F,           KC_G,                                           HM_H,           HM_J,           HM_K,           HM_L,           KC_SCLN,        KC_QUOT,
    KC_ESC,         KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_NO,
                                                                    LT_NAV,         LT_NUM,                                         LT_SYM,         LT_ACC
  ),

  [NAV] = LAYOUT_voyager(
    KC_NO,          SHOTTR1,        SHOTTR2,        SHOTTR3,        KC_F18,         KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_ESC,         SELWORD,        SELLINE,        NAV_RDO,        KC_DEL,                                      NAV_TBP,        NAV_TBN,        NAV_BCK,        NAV_FWD,        KC_TRNS,        KC_NO,
    KC_NO,          KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_NO,                                          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RGHT,        KC_TRNS,        KC_NO,
    KC_NO,          NAV_UND,        NAV_CUT,        NAV_CPY,        NAV_PST,        NAV_ALL,                                        KC_HOME,        KC_PGDN,        KC_PGUP,        KC_END,         KC_TRNS,        KC_NO,
                                                                    KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS
  ),

  [NUM] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_PLUS,        KC_MINS,        KC_ASTR,        KC_SLSH,        KC_EQL,                                         KC_7,           KC_8,           KC_9,           KC_EQL,         KC_TRNS,        KC_NO,
    KC_NO,          KC_LGUI,        KC_LALT,        KC_LCTL,        KC_LSFT,        KC_TRNS,                                        KC_4,           KC_5,           KC_6,           KC_ENT,         KC_TRNS,        KC_NO,
    KC_NO,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                        KC_1,           KC_2,           KC_3,           KC_DOT,         KC_TRNS,        KC_NO,
                                                                    KC_TRNS,        KC_TRNS,                                        KC_BSPC,        KC_0
  ),

  // After Getreuer's first symbol layer. The right hand is one rule: middle
  // finger opens a bracket, ring finger closes it, three pairs stacked. The
  // left hand is operators, laid out so the common bigrams roll inward toward
  // the index (!= += *= <= ->), and so the symbols that get typed twice in a
  // row (== ++ -- // **) never land on a pinky.
  [SYM] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_GRV,         KC_LABK,        KC_RABK,        KC_NO,          KC_NO,                                          KC_AMPR,        KC_NO,          KC_LBRC,        KC_RBRC,        KC_PERC,        KC_NO,
    KC_NO,          KC_EXLM,        KC_MINS,        KC_PLUS,        KC_EQL,         KC_HASH,                                        KC_PIPE,        KC_COLN,        KC_LPRN,        KC_RPRN,        KC_QUES,        KC_NO,
    KC_NO,          KC_CIRC,        KC_SLSH,        KC_ASTR,        KC_UNDS,        PT_EURO,                                        KC_TILD,        KC_DLR,         KC_LCBR,        KC_RCBR,        KC_AT,          KC_NO,
                                                                    KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS
  ),

  [ACC] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          PT_ACIR,        KC_TRNS,        PT_EACU,        KC_TRNS,        KC_TRNS,                                        KC_TRNS,        PT_UACU,        PT_IACU,        PT_OACU,        KC_TRNS,        KC_NO,
    KC_NO,          PT_AACU,        PT_ATIL,        PT_ECIR,        KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS,        PT_OCIR,        PT_OTIL,        KC_TRNS,        KC_NO,
    KC_NO,          PT_AGRV,        KC_TRNS,        PT_CCED,        KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_NO,
                                                                    KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS
  ),

  [MEDIA] = LAYOUT_voyager(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          RGB_TOG,        RGB_VAI,        RGB_MODE_FORWARD,RGB_HUI,        TOGGLE_LAYER_COLOR,                            KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE, KC_AUDIO_VOL_UP,KC_NO,          KC_NO,          KC_NO,
                                                                    KC_TRNS,        KC_TRNS,                                        KC_NO,          KC_NO
  ),

  // The pre-redesign mouse layer, restored from commit 53880a7. Plain mouse
  // keycodes, not Orbital Mouse: the left hand steers in 8 directions and the
  // left thumbs click. NOTHING ACTIVATES THIS LAYER YET - it is unreachable
  // until an activation key is chosen.
  //
  // Two keys from the original are dropped: QK_LLCK (layer lock, disabled in
  // rules.mk) and TD(DANCE_8) (tap dance, likewise).
  [MOUSE] = LAYOUT_voyager(
    KC_NO,          KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_MS_WH_DOWN,  KC_MS_UP,       KC_MS_WH_UP,    KC_TRNS,        KC_TRNS,                                        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRNS,        KC_TRNS,                                        KC_RIGHT_CTRL,  KC_RIGHT_SHIFT, KC_LEFT_ALT,    KC_RIGHT_GUI,   KC_TRNS,        KC_TRNS,
    KC_TRNS,        KC_MS_WH_LEFT,  KC_MS_BTN3,     KC_MS_WH_RIGHT, KC_TRNS,        KC_TRNS,                                        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_NO,
                                                                    KC_MS_BTN1,     KC_MS_BTN2,                                     KC_TRNS,        KC_TRNS
  ),
};

// Accents are typed as a macOS dead key followed by the letter. Mods are
// stripped for the dead key (⌥⇧E is not the acute dead key) and restored for
// the letter, so holding Shift yields the capital form.

// The outer pinky can brush this key while rolling off Cmd. Emit F17 only on
// release after 60 ms so that accidental brush does not open hint mode.
static uint16_t clavier_press_time;

static void tap_accent(uint16_t dead_key, uint16_t letter) {
  const uint8_t mods = get_mods();
  clear_mods();
  clear_weak_mods();
  send_keyboard_report();

  tap_code16(LALT(dead_key));

  set_mods(mods);
  send_keyboard_report();
  tap_code16(letter);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }
  if (!process_select_word(keycode, record)) { return false; }

  switch (keycode) {
    case WISPR:
      // Held, not tapped: the key must stay down while the user speaks.
      if (record->event.pressed) {
        register_code(KC_F13);
      } else {
        unregister_code(KC_F13);
      }
      return false;

    case CLAVIER:
      if (record->event.pressed) {
        clavier_press_time = timer_read();
      } else if (timer_elapsed(clavier_press_time) >= 60) {
        tap_code(KC_F17);
      }
      return false;

    case PT_AACU: if (record->event.pressed) { tap_accent(KC_E, KC_A); } return false;
    case PT_EACU: if (record->event.pressed) { tap_accent(KC_E, KC_E); } return false;
    case PT_IACU: if (record->event.pressed) { tap_accent(KC_E, KC_I); } return false;
    case PT_OACU: if (record->event.pressed) { tap_accent(KC_E, KC_O); } return false;
    case PT_UACU: if (record->event.pressed) { tap_accent(KC_E, KC_U); } return false;
    case PT_ACIR: if (record->event.pressed) { tap_accent(KC_I, KC_A); } return false;
    case PT_ECIR: if (record->event.pressed) { tap_accent(KC_I, KC_E); } return false;
    case PT_OCIR: if (record->event.pressed) { tap_accent(KC_I, KC_O); } return false;
    case PT_ATIL: if (record->event.pressed) { tap_accent(KC_N, KC_A); } return false;
    case PT_OTIL: if (record->event.pressed) { tap_accent(KC_N, KC_O); } return false;
    case PT_AGRV: if (record->event.pressed) { tap_accent(KC_GRV, KC_A); } return false;

    case PT_EURO:
      if (record->event.pressed) { tap_code16(LALT(LSFT(KC_2))); }
      return false;
  }

  return true;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  // Holding Delete cannot repeat, because a hold is how the Symbol layer is
  // reached. Tap it and press again within this window and the second press
  // repeats the delete instead, so tap-then-hold chews through text the way a
  // plain Backspace key does. A cold hold still gives Symbols.
  if (keycode == LT_SYM) { return 120; }

  // Same treatment for H, for the same reason: in vim you tap h to move left and
  // then hold it to keep moving. Without a window here that hold would be Shift.
  // A cold hold still gives Shift.
  if (keycode == HM_H) { return 120; }

  // Everything else keeps QUICK_TAP_TERM 0: tap and immediately hold still
  // reaches the hold function, with no repeated letter in the way.
  return 0;
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  // Layers bypass Achordion completely. Achordion exists to protect home row
  // mods from same-hand rolls; the layers are all on thumbs, which have no such
  // problem. Left in, its timeout is the delay before a layer appears when you
  // hold a thumb to look at the layer rather than to type a chord.
  if (IS_QK_LAYER_TAP(tap_hold_keycode)) { return 0; }

  // Below the 1000 ms default so a held mod with no key after it — Cmd+click,
  // for instance — does not sit waiting. The chord check on the next key press
  // is what does the real work, and it is unaffected by this.
  return 500;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                     uint16_t other_keycode, keyrecord_t *other_record) {
  // Every chord is allowed, same hand included. The opposite-hands rule cannot
  // work on this board: Cmd is on the left pinky, and Cmd+T, W, R, Q, S, D, F,
  // A, Z, X, C, V are all left-hand chords. Under that rule every one of them
  // resolved as two letters unless you waited out the timeout.
  //
  // ACHORDION_STREAK is what prevents accidental mods instead, and it draws a
  // better line: mods are suppressed inside a fast run of letters, which is
  // where misfires actually come from, and allowed when you pause to reach for
  // a chord deliberately.
  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}

void housekeeping_task_user(void) {
  select_word_task();
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, NAV, NUM, MEDIA);
}

// Per-layer lighting. Rather than a hand-maintained 52-entry table per layer,
// the live keys are read back out of the keymap itself, so the lighting can
// never disagree with the firmware about which keys a layer defines.
static void light_layer(uint8_t layer, uint8_t h, uint8_t s, uint8_t v) {
  const HSV hsv = {h, s, v};
  const RGB rgb = hsv_to_rgb(hsv);
  const float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;

  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
      const uint8_t led = g_led_config.matrix_co[row][col];
      if (led >= RGB_MATRIX_LED_COUNT) { continue; }

      const keypos_t pos = {.col = col, .row = row};
      const uint16_t kc = keymap_key_to_keycode(layer, pos);
      if (kc == KC_NO || kc == KC_TRANSPARENT) {
        rgb_matrix_set_color(led, 0, 0, 0);
      } else {
        rgb_matrix_set_color(led, f * rgb.r, f * rgb.g, f * rgb.b);
      }
    }
  }
}


// Layer hues stay in the base lavender's family: same value, and a saturation
// well below full, so a layer reads as a tint of the board rather than a
// different board. The hues are spread far enough apart to name at a glance.
#define LAYER_SAT 150
#define LAYER_VAL 231

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) { return false; }
  // TOGGLE_LAYER_COLOR: hand the LEDs back to the RGB effect, which is the only
  // way to see PaletteFx, since the code below repaints every LED each frame.
  if (keyboard_config.disable_layer_led) { return false; }
  // RGB_TOG parks the board at LED_FLAG_NONE. Repainting here would defeat it.
  if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
    rgb_matrix_set_color_all(0, 0, 0);
    return true;
  }

  switch (get_highest_layer(layer_state)) {
    case BASE:  light_layer(BASE,  191,          70, 231);     break;
    case NAV:   light_layer(NAV,   128, LAYER_SAT, LAYER_VAL); break;
    case NUM:   light_layer(NUM,    21, LAYER_SAT, LAYER_VAL); break;
    case SYM:   light_layer(SYM,    85, LAYER_SAT, LAYER_VAL); break;
    case ACC:   light_layer(ACC,   230, LAYER_SAT, LAYER_VAL); break;
    case MEDIA: light_layer(MEDIA, 170, LAYER_SAT, LAYER_VAL); break;
    case MOUSE: light_layer(MOUSE,   0, LAYER_SAT, LAYER_VAL); break;
  }

  return true;
}
