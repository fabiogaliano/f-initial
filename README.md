# f.qwerty — ZSA Voyager Keymap

Custom QMK keymap for the ZSA Voyager split keyboard.

## Build & Flash

```bash
# Set toolchain (keg-only, must be on PATH)
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH"

cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager

make voyager:f.qwerty           # compile only
make voyager:f.qwerty:flash     # compile + flash (press reset on left half with paperclip)
```

## Layers

| Layer | Purpose |
|-------|---------|
| 0 | Base QWERTY (home row mods) |
| 1 | Portuguese characters |
| 2 | Symbols |
| 3 | Numpad |
| 4 | Navigation |
| 5 | Mouse |
| 6 | F-keys |
| 7 | Layer switcher + RGB (double-tap bottom-right) |
| 8 | Window management |
| 9 | League of Legends |
| 10 | LoL alt-abilities (MO layer) |
| 11 | LoL chat mode |

## Files

- `keymap.c` — layers, tap dance, RGB, custom keycodes
- `config.h` — keyboard config (includes required `FIRMWARE_VERSION`)
- `rules.mk` — build features (tap dance, RGB matrix, layer lock)
- `i18n.h` — Portuguese character definitions
