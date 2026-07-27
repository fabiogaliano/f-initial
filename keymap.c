#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  CHAT_ENTER,
  CHAT_SEND,
  CHAT_CANCEL,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
  DANCE_5,
};

#define DUAL_FUNC_0 LT(6, KC_F5)
#define DUAL_FUNC_1 LT(5, KC_F16)
#define DUAL_FUNC_2 LT(2, KC_F5)
#define DUAL_FUNC_3 LT(6, KC_G)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_MINUS,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_EQUAL,       
    KC_HYPR,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           MT(MOD_RCTL, KC_Y),MT(MOD_RSFT, KC_U),MT(MOD_RALT, KC_I),MT(MOD_RGUI, KC_O),KC_P,           KC_BSLS,        
    KC_LEFT_SHIFT,  MT(MOD_LGUI, KC_A),MT(MOD_LALT, KC_S),MT(MOD_LSFT, KC_D),MT(MOD_LCTL, KC_F),KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOTE,       
    LT(5, KC_ESCAPE),KC_Z,           KC_X,           KC_C,           LT(3, KC_V),    LT(2, KC_B),                                    KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       TD(DANCE_0),    
                                                    LT(4, KC_ENTER),LT(2, KC_TAB),                                  DUAL_FUNC_0,    LT(8, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, PT_OSX_ACUT,    
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_J,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, PT_OSX_TILD,    
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    LT(4, KC_ENTER),LT(2, KC_TAB),                                  KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    QK_LLCK,        KC_GRAVE,       KC_TRANSPARENT, KC_QUOTE,       KC_SCLN,        KC_COMMA,                                       KC_DELETE,      KC_SLASH,       KC_BSLS,        KC_AMPR,        KC_ASTR,        KC_TRANSPARENT, 
    KC_AT,          KC_BSPC,        KC_LABK,        KC_RABK,        KC_DQUO,        KC_DLR,                                         KC_AMPR,        KC_LBRC,        KC_RBRC,        KC_EQUAL,       KC_UNDS,        KC_TAB,         
    KC_MINUS,       DUAL_FUNC_1,    MT(MOD_LALT, KC_MINUS),DUAL_FUNC_2,    MT(MOD_RCTL, KC_EQUAL),KC_LBRC,                                        KC_CIRC,        KC_LPRN,        KC_RPRN,        KC_QUES,        KC_EXLM,        ST_MACRO_0,     
    KC_HASH,        KC_ENTER,       KC_LPRN,        KC_RPRN,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TILD,        KC_LCBR,        KC_RCBR,        KC_AT,          KC_PIPE,        KC_TRANSPARENT, 
                                                    KC_DOT,         KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    QK_LLCK,        KC_NO,          KC_NO,          KC_NO,          KC_DELETE,      KC_NO,                                          KC_SLASH,       KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_NO,          
    KC_TRANSPARENT, KC_NO,          KC_MAC_UNDO,    LGUI(LSFT(KC_Z)),KC_BSPC,        KC_MAC_CUT,                                     KC_KP_MINUS,    KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_NO,          
    KC_MEH,         KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_SHIFT,  KC_LEFT_CTRL,   KC_MAC_COPY,                                    KC_0,           KC_1,           KC_2,           KC_3,           KC_NO,          KC_NO,          
    KC_HYPR,        KC_NO,          LGUI(KC_A),     LALT(LGUI(LCTL(LSFT(KC_W)))),KC_TRANSPARENT, KC_MAC_PASTE,                                   KC_KP_EQUAL,    TD(DANCE_1),    TD(DANCE_2),    TD(DANCE_3),    TD(DANCE_4),    KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_BSPC,                                        KC_COMMA,       KC_DOT
  ),
  [4] = LAYOUT_voyager(
    QK_LLCK,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE,      KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LSFT(KC_Z)),KC_MAC_UNDO,    KC_BSPC,        KC_MAC_CUT,                                     KC_TRANSPARENT, LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TAB,         
    KC_TRANSPARENT, KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_SHIFT,  KC_LEFT_CTRL,   KC_MAC_COPY,                                    KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, ST_MACRO_1,     
    KC_TRANSPARENT, KC_TRANSPARENT, LGUI(KC_A),     LALT(LGUI(LCTL(LSFT(KC_W)))),LALT(LSFT(KC_RIGHT)),KC_MAC_PASTE,                                   KC_HOME,        KC_PGDN,        KC_PAGE_UP,     KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_voyager(
    QK_LLCK,        KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MS_WH_DOWN,  KC_MS_UP,       KC_MS_WH_UP,    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_RIGHT_CTRL,  KC_RIGHT_SHIFT, KC_LEFT_ALT,    KC_RIGHT_GUI,   KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_BTN3,     KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_5),    
                                                    KC_MS_BTN1,     KC_MS_BTN2,                                     KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [6] = LAYOUT_voyager(
    QK_LLCK,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_NO,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F15,         
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_PSCR,        KC_F4,          KC_F5,          KC_F6,          KC_F11,         KC_BRIGHTNESS_DOWN,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_SCRL,        KC_F1,          KC_F2,          KC_F3,          KC_F12,         KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_PAUSE,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [7] = LAYOUT_voyager(
    TO(0),          TO(2),          TO(3),          TO(1),          TO(4),          TO(5),                                          TO(6),          KC_NO,          KC_NO,          KC_NO,          KC_NO,          TO(9),          
    KC_NO,          RGB_SPI,        RGB_SAI,        RGB_VAI,        RGB_HUI,        RGB_MODE_FORWARD,                                RGB_TOG,        KC_NO,          KC_MEDIA_PREV_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,
    KC_NO,          RGB_SPD,        RGB_SAD,        RGB_VAD,        RGB_HUD,        RGB_SLD,                                        TOGGLE_LAYER_COLOR,KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_AUDIO_VOL_UP,KC_NO,          KC_NO,          KC_LEFT_GUI,    
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [8] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, LGUI(LSFT(KC_DOWN)),LGUI(KC_DOWN),  LGUI(KC_UP),    LGUI(LSFT(KC_UP)),KC_TRANSPARENT,                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [9] = LAYOUT_voyager(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_NO,          KC_NO,          KC_T,           KC_NO,          KC_NO,          TO(0),
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_6,                                           KC_Y,           KC_U,           KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    MO(10),         KC_Z,           KC_NO,          CHAT_ENTER,     KC_V,           KC_B,                                           KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          TD(DANCE_0),
                                                    KC_SPACE,       KC_LEFT_CTRL,                                   KC_P,           KC_NO
  ),
  [10] = LAYOUT_voyager(
    KC_TRANSPARENT, LALT(KC_1),     LALT(KC_2),     LALT(KC_3),     LALT(KC_4),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LALT(KC_Q),     LALT(KC_W),     LALT(KC_E),     LALT(KC_R),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LALT(KC_D),     LALT(KC_F),     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_P,                                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [11] = LAYOUT_voyager(
    CHAT_CANCEL,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    CHAT_SEND,      KC_TRANSPARENT,                                 KC_BSPC,        KC_TRANSPARENT
  ),
};



uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_J:
            return TAPPING_TERM -60;
        case KC_K:
            return TAPPING_TERM -35;
        case LT(8, KC_SPACE):
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231}, {191,70,231} },

    [1] = { {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216} },

    [2] = { {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170}, {177,44,170} },

    [3] = { {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238}, {189,255,238} },

    [4] = { {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216}, {135,70,216} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {245,134,235}, {25,131,246}, {245,134,235}, {0,0,0}, {0,0,0}, {0,0,0}, {25,131,246}, {25,131,246}, {25,131,246}, {0,0,0}, {0,0,0}, {0,0,0}, {245,134,235}, {245,134,235}, {245,134,235}, {0,0,0}, {0,0,0}, {245,134,235}, {245,134,235}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {245,134,235}, {245,134,235}, {245,134,235}, {245,134,235}, {0,0,0}, {0,0,0}, {245,134,235}, {245,134,235}, {245,134,235}, {245,134,235}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {36,255,255}, {36,255,255}, {36,255,255}, {36,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {36,255,255}, {36,255,255}, {0,0,0}, {36,255,255}, {36,255,255}, {36,255,255}, {36,255,255}, {0,0,0}, {36,255,255}, {36,255,255}, {36,255,255}, {0,0,0}, {36,255,255}, {0,0,0}, {36,255,255}, {36,255,255}, {36,255,255}, {36,255,255}, {36,255,255}, {0,0,0}, {36,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {36,255,255}, {36,255,255} },

    [7] = { {0,0,0}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {33,255,255}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {33,255,255}, {33,255,255}, {33,255,255}, {0,0,0}, {0,0,0}, {33,255,255}, {0,0,0}, {0,0,0} },

    [9] = { {190,120,165}, {20,130,180}, {20,130,180}, {20,130,180}, {20,130,180}, {20,130,180}, {190,120,165}, {30,210,210}, {30,210,210}, {30,210,210}, {30,210,210}, {20,130,180}, {190,120,165}, {30,160,195}, {30,160,195}, {240,170,200}, {240,170,200}, {190,120,165}, {190,120,165}, {15,150,175}, {0,0,0}, {15,150,175}, {15,150,175}, {15,150,175}, {30,160,195}, {15,150,175}, {0,0,0}, {0,0,0}, {130,140,175}, {0,0,0}, {0,0,0}, {190,120,165}, {130,140,175}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {130,140,175}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {190,120,165}, {130,140,175}, {0,0,0} },

    [10] = { {0,0,0}, {20,130,160}, {20,130,160}, {20,130,160}, {20,130,160}, {0,0,0}, {0,0,0}, {30,190,180}, {30,190,180}, {30,190,180}, {30,190,180}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {240,150,170}, {240,150,170}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {15,130,155}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [11] = { {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170}, {175,130,170} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 7:
      set_layer_color(7);
      break;
    case 9:
      set_layer_color(9);
      break;
    case 10:
      set_layer_color(10);
      break;
    case 11:
      set_layer_color(11);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_LEFT_SHIFT)SS_DELAY(100)  SS_TAP(X_TAB));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_LEFT_SHIFT)SS_DELAY(100)  SS_TAP(X_TAB));
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_BSPC);
        } else {
          unregister_code16(KC_BSPC);
        }
      } else {
        if (record->event.pressed) {
          register_code16(LALT(KC_BSPC));
        } else {
          unregister_code16(LALT(KC_BSPC));
        }  
      }  
      return false;
    case DUAL_FUNC_1:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_EXLM);
        } else {
          unregister_code16(KC_EXLM);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_GUI);
        } else {
          unregister_code16(KC_LEFT_GUI);
        }  
      }  
      return false;
    case DUAL_FUNC_2:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_PLUS);
        } else {
          unregister_code16(KC_PLUS);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_RIGHT_SHIFT);
        } else {
          unregister_code16(KC_RIGHT_SHIFT);
        }  
      }  
      return false;
    case DUAL_FUNC_3:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_B);
        } else {
          unregister_code16(KC_B);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_P);
        } else {
          unregister_code16(KC_P);
        }  
      }  
      return false;
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
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[6];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(PT_OSX_AE);
        tap_code16(PT_OSX_AE);
        tap_code16(PT_OSX_AE);
    }
    if(state->count > 3) {
        tap_code16(PT_OSX_AE);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(PT_OSX_AE); break;
        case DOUBLE_TAP: layer_move(7); break;
        case DOUBLE_SINGLE_TAP: tap_code16(PT_OSX_AE); register_code16(PT_OSX_AE);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(PT_OSX_AE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(PT_OSX_AE); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LPRN);
        tap_code16(KC_LPRN);
        tap_code16(KC_LPRN);
    }
    if(state->count > 3) {
        tap_code16(KC_LPRN);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_LPRN); break;
        case DOUBLE_TAP: register_code16(KC_LABK); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LPRN); register_code16(KC_LPRN);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_LPRN); break;
        case DOUBLE_TAP: unregister_code16(KC_LABK); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LPRN); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LCBR);
        tap_code16(KC_LCBR);
        tap_code16(KC_LCBR);
    }
    if(state->count > 3) {
        tap_code16(KC_LCBR);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_LCBR); break;
        case DOUBLE_TAP: register_code16(KC_LBRC); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LCBR); register_code16(KC_LCBR);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_LCBR); break;
        case DOUBLE_TAP: unregister_code16(KC_LBRC); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LCBR); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RCBR);
        tap_code16(KC_RCBR);
        tap_code16(KC_RCBR);
    }
    if(state->count > 3) {
        tap_code16(KC_RCBR);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_RCBR); break;
        case DOUBLE_TAP: register_code16(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RCBR); register_code16(KC_RCBR);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_RCBR); break;
        case DOUBLE_TAP: unregister_code16(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RCBR); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RPRN);
        tap_code16(KC_RPRN);
        tap_code16(KC_RPRN);
    }
    if(state->count > 3) {
        tap_code16(KC_RPRN);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(KC_RPRN); break;
        case DOUBLE_TAP: register_code16(KC_RABK); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RPRN); register_code16(KC_RPRN);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_RPRN); break;
        case DOUBLE_TAP: unregister_code16(KC_RABK); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RPRN); break;
    }
    dance_state[4].step = 0;
}
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case DOUBLE_TAP: layer_move(0); break;
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
    }
    dance_state[5].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_finished, dance_5_reset),
};
