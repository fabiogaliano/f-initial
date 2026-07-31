# f.qwerty — ZSA Voyager Keymap

Custom QMK keymap for the ZSA Voyager split keyboard.
The design and its rationale live in `REDESIGN.md`.

## Build & Flash

```bash
# Set toolchain (keg-only, must be on PATH)
export PATH="/opt/homebrew/opt/arm-none-eabi-gcc@8/bin:/opt/homebrew/opt/arm-none-eabi-binutils/bin:$PATH"

cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager

make voyager:f.qwerty           # compile only
make voyager:f.qwerty:flash     # compile + flash (press reset on left half with paperclip)
```

Or use the wrapper, which sets the toolchain PATH for you and syncs the Probe HUD
after a flash:

```bash
scripts/build.sh                # compile only
scripts/build.sh flash          # compile, flash, sync Probe
```

Toolchain dependencies: `arm-none-eabi-gcc@8`, `arm-none-eabi-binutils`, `isl`,
`libmpc`, `dfu-util`.

## Probe HUD

[Probe](https://github.com/bogo/probe) is a floating macOS HUD that shows the live
layer and pressed keys. It works off Raw HID telemetry, which needs
`ORYX_ENABLE = yes` in `rules.mk` — already set.

Probe labels keys from an **imported copy** of `keymap.c`, not from the live
keyboard, so a reflash alone leaves the HUD showing the old layout:

```bash
scripts/sync-probe.sh           # copy keymap + merge labels + restart Probe
```

`probe-labels.json` names everything Probe cannot resolve from source — our
`#define` aliases and custom keycodes. Add a key to the
keymap, add it there too. Close ZSA Keymapp first; it claims the same Raw HID
interface.

## Layers

| # | Layer | Access |
|---|---|---|
| 0 | Base | — |
| 1 | Nav | hold left inner thumb (`Enter`) |
| 2 | Numbers | hold left outer thumb (`Tab`) |
| 3 | Symbols | hold right inner thumb (`Backspace`) |
| 4 | Accents | hold right outer thumb (`Space`) |
| 5 | Media | hold both left thumbs (tri-layer) |
| 6 | Mouse | hold left outer row 3 (`Escape`) |

Mouse wheel taps send one native HID step immediately. Holding a wheel key
repeats after 100 ms, ramps over roughly three seconds, and gets one bounded
second-stage boost after a six-second hold. `Slwr` and `Fstr` on the Mouse layer
adjust a bounded persistent speed level, while `Norm` restores
the firmware default. Pointer movement reaches full speed in roughly half a
second; the faster levels favor pointer speed so scrolling changes less.

## Files

- `keymap.c` — layers, custom keycodes, per-layer lighting
- `config.h` — tapping config, PaletteFx settings, keycode compat shims
- `rules.mk` — build features and the vendored feature sources
- `features/` — Getreuer's Achordion, Select Word, PaletteFx
- `rgb_matrix_user.inc` — registers the PaletteFx effects
- `autocorrect_dict.txt` / `autocorrect_data.h` — autocorrect dictionary
- `probe-labels.json` — Probe HUD labels for our macros and `#define` aliases
- `archive/league.md` — the removed League of Legends layers

## Regenerating autocorrect data

```bash
cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager
qmk generate-autocorrect-data -kb voyager -km f.qwerty \
  /Users/f/Core/dev/keyboard/f.qwerty/autocorrect_dict.txt
```
