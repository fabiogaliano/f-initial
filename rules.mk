CONSOLE_ENABLE = no
COMMAND_ENABLE = no
ORYX_ENABLE = yes
RGB_MATRIX_CUSTOM_KB = yes
SPACE_CADET_ENABLE = no

# One isolated tap dance toggles the archived LoL layer from the empty
# bottom-right key. Layer lock remains disabled.
TAP_DANCE_ENABLE = yes
LAYER_LOCK_ENABLE = no

AUTOCORRECT_ENABLE = yes
CAPS_WORD_ENABLE = no

# Needed by the restored mouse layer's plain KC_MS_* keycodes.
MOUSEKEY_ENABLE = yes

# PaletteFx effects live in rgb_matrix_user.inc alongside ZSA's own effects.
RGB_MATRIX_CUSTOM_USER = yes

# This fork has no community-module support, so Getreuer's features are
# vendored under features/ (see REDESIGN §5).
SRC += features/achordion.c
SRC += features/select_word.c
