# CLAUDE.md

## Build

```bash
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH"
cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager
make voyager:f.qwerty           # compile
make voyager:f.qwerty:flash     # compile + flash
```

- `arm-none-eabi-gcc` is keg-only — PATH export required before every build
- `FIRMWARE_VERSION` must exist in config.h (Oryx doesn't include it, ZSA's fork requires it)
- `lib/chibios-contrib` submodule warning is harmless — Voyager doesn't use it
- Flash: press reset button on bottom of LEFT half with a paperclip when prompted

## Keymap: f.qwerty

12 layers (0-11). See README.md for layer table.

### Key Patterns
- Home row mods on base layer (GACS order)
- Tap dance actions: DANCE_0 (bottom-right, double-tap → layer 7), DANCE_1-4 (bracket pairs), DANCE_5 (double-tap → layer 0)
- Custom keycodes: CHAT_ENTER/CHAT_SEND/CHAT_CANCEL for LoL chat flow
- DUAL_FUNC_0-3: layer-tap keys with custom tap/hold via process_record_user
- Per-layer RGB defined in ledmap[][] array (52 LEDs, indexed by physical key position)

### LED Index Map (Voyager)
Left side (0-25): Row 0 [0-5], Row 1 [6-11], Row 2 [12-17], Row 3 [18-23], Thumb [24-25]
Right side (26-51): Row 0 [26-31], Row 1 [32-37], Row 2 [38-43], Row 3 [44-49], Thumb [50-51]

### Guidelines
- Maintain RGB color consistency when moving keys
- Preserve tap dance behaviors unless specifically changing them
- Test on physical keyboard after flashing
