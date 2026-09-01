#define FIRMWARE_VERSION u8"EoBdY/RjqGg5"
#define SERIAL_NUMBER "EoBdY/RjqGg5"

#undef RGB_MATRIX_TIMEOUT
#define RGB_MATRIX_TIMEOUT 300000
#define RGB_MATRIX_STARTUP_SPD 60

#define USB_SUSPEND_WAKEUP_DELAY 0

// One term for everything, mods and thumb layers alike. This is what the old
// Oryx keymap ran at and what felt right, so the per-key overrides that made
// the thumbs resolve faster are gone.
//
// HOLD_ON_OTHER_KEY_PRESS is deliberately absent. It resolves a tap-hold as a
// hold the instant any other key goes down, whatever the press length, which on
// a thumb turns overlapping typing into a layer and eats the tap.
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0

// Tap-then-hold repeats the tap instead of reaching the hold. Only Delete wants
// this; see get_quick_tap_term() in keymap.c.
#define QUICK_TAP_TERM_PER_KEY

// Mouse Keys sends the first pointer or wheel report immediately; each delay
// only gates held repetition. Keep taps discrete, start wheel reports at one
// step, and ramp slowly enough that held scrolling stays controllable. In this QMK
// fork TIME_TO_MAX is a repeat count, so the wheel reaches its normal maximum
// after roughly 60 * 50 ms rather than after 60 ms.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 60
#define MOUSEKEY_MOVE_DELTA 4
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 10
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 24

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 100
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 50
#undef MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED 6
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 60

// Suppress home row mods inside a typing streak. This replaces Achordion's
// opposite-hands rule, which is unusable here because Cmd sits on the left
// pinky and most macOS Cmd shortcuts are left-hand letters.
#define ACHORDION_STREAK

// Select Word targets macOS word/line hotkeys.
#define SELECT_WORD_OS_MAC

// PaletteFx is for looks only (DESIGN.md, Lighting). Its sources use the hsv_t/rgb_t
// type names QMK adopted after this fork.
#define PALETTEFX_ENABLE_ALL_EFFECTS
#define PALETTEFX_ENABLE_ALL_PALETTES
// PaletteFx selects its palette from the hue setting. A step of 16 makes the
// hue wheel land on each of the 16 palettes exactly once, so the Media layer's
// RGB_HUI key is a clean "next palette".
#define RGB_MATRIX_HUE_STEP 16
#define hsv_t HSV
#define rgb_t RGB

// Select Word switches on this case range, added to QMK after this fork.
#define MODIFIER_KEYCODE_RANGE KC_LCTL ... KC_RGUI

