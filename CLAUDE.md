# CLAUDE.md

## Git

Commit straight to `main`. Do not create a branch for keymap changes — this is a
single-user config repo and a branch adds a merge step for no review benefit.

## Build

```bash
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH"
cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager
make voyager:f.qwerty           # compile
make voyager:f.qwerty:flash     # compile + flash
```

- `arm-none-eabi-gcc` is keg-only — PATH export required before every build
- Needs `isl`, `libmpc` (GCC 8 runtime deps) and `dfu-util` from Homebrew
- `FIRMWARE_VERSION` must exist in config.h (Oryx doesn't include it, ZSA's fork requires it)
- `lib/chibios-contrib` submodule warning is harmless — Voyager doesn't use it
- Flash: press reset button on bottom of LEFT half with a paperclip when prompted
- The tree builds with `-Werror`, so any new warning fails the build

## Keymap: f.qwerty

7 layers, but Mouse has no activation key. `REDESIGN.md` is the design document and the reason behind every
placement; read it before moving keys. Its §7 design rules and §9 rejected list
apply to any change.

### Key patterns
- Home row mods: left `A`/`S`/`D`/`F` = Cmd/Opt/Ctrl/Shift, right `J`/`K`/`L` =
  Ctrl/Opt/Shift. `H` is deliberately plain.
- Every layer is a momentary thumb hold; Media is a tri-layer of the two left
  thumbs. There are no toggles.
- The thumb layers stay on fixed hands, but their tapped letters were swapped back
  to the pre-redesign positions: `LT(NAV, KC_ENT)`, `LT(NUM, KC_TAB)`,
  `LT(SYM, KC_BSPC)`, `LT(ACC, KC_SPC)`. Moving a layer to the other hand would
  break Nav's opposite-hand arrows and the two-left-thumb Media chord.
- Accents are macOS dead-key macros (`tap_accent`), not Unicode input.
- Per-layer RGB is derived from the keymap at runtime, not a hand-written
  table — a key lights only if it is neither `KC_NO` nor `KC_TRNS` on that
  layer, so lighting cannot drift out of sync with the layout.

### Fork constraints
This ZSA fork is QMK from June 2024 (firmware23). It has **no** Chordal Hold and
**no** community-module support, so Getreuer's features are vendored in
`features/` and pulled in with `SRC +=` in `rules.mk`. `config.h` carries small
compat shims for names QMK introduced later (`hsv_t`/`rgb_t`,
`MODIFIER_KEYCODE_RANGE`). If the fork is ever updated, delete those shims and
switch to core Chordal Hold.

`features/select_word.c` carries one local patch: a `SELECT_LINE_KEYCODE` for a
dedicated line-selection key. Re-apply it if the file is refreshed upstream.

### Probe HUD
`scripts/sync-probe.sh` pushes `keymap.c` and `probe-labels.json` into
`~/Library/Application Support/Probe/`. Probe parses the keymap source and cannot
expand `#define`s, so **every alias this keymap adds needs an entry in
`probe-labels.json`** or it renders as a raw C token. The parser also requires
exactly 52 keys per layer, and fails silently to a blank board if that breaks.

### LED index map (Voyager)
Left side (0-25): Row 0 [0-5], Row 1 [6-11], Row 2 [12-17], Row 3 [18-23], Thumb [24-25]
Right side (26-51): Row 0 [26-31], Row 1 [32-37], Row 2 [38-43], Row 3 [44-49], Thumb [50-51]

Note this differs from `LAYOUT_voyager` argument order, which interleaves the
halves row by row.
