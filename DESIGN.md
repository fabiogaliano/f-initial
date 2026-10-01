# f.qwerty — Design Decisions

`keymap.c` is the source of truth for what every key does. This document records
**why**, and it deliberately contains no key-position diagrams: a hand-drawn
picture of the layout can only ever drift from the firmware. Generate one from
the firmware instead — see [Rendering](#rendering).

Read [Design rules](#design-rules) and [Rejected](#rejected) before moving any key.

---

## Requirements

**Goals**

- Use layers. The old keymap had 12 and the user used almost none of them.
- Remove the number row from normal typing. The top row is bad for vim counts and motions.
- Move Shift off the outer pinky.
- Type Portuguese accents while the system stays in English.
- Keep QWERTY. Do not change to an alternative alphabet layout.

**Constraints**

- The Voyager has 52 keys and 4 thumb keys, 2 per hand. Thumb keys are scarce.
- The primary operating system is macOS.
- The firmware is built from source with QMK.
- The user is a heavy vim user.
- The user writes English and Portuguese.

**Medical constraint**

The user has chronic light inflammation in the RIGHT wrist. Every decision moves
load to the left hand. Four rules follow:

- Put the heavy thumb keys on the left thumb.
- Keep frequent keys off the top row.
- Keep the right pinky reaches short.
- Move pointer control off the right hand.

**Design principle**

Memory is the primary constraint, not speed. So: few layers, keys where their
meaning is obvious, consistent rules. `Z` `X` `C` `V` keep undo, cut, copy and
paste because those positions are already known.

---

## Layer rationale

The layer list and how each is reached live in `README.md`. This section is only
the reasoning.

### Base

**Home row mods.** The user rests on `A`-`S`-`D`-`F` and `H`-`J`-`K`-`L`, so the
right hand sits one column inward from the usual `J`-`K`-`L`-`;`. Every placement
follows from that. The mirror is taken across the *fingers*, not across the two
halves: a physical mirror would pair `A` with `;`, which is wrong here because `;`
sits outside the rest position entirely and stays a plain key.

Cmd is on the pinky (`A`/`L`), Option on the ring, Shift on the middle, Ctrl on
the index.

*Amended.* Ctrl and Shift were originally reversed — Shift on the index, Ctrl on
the middle — because the index is the strongest finger and an inward roll could
then never end on a held Shift. Swapped by preference; that guarantee against
stray capitals no longer holds. Cmd, the most-used modifier on macOS, stays on
the pinky to keep the existing left-hand habit, and the weak ring finger gets
Option, which is held only briefly.

`H` carries Ctrl despite being the most frequent letter on that hand and the left
arrow on Nav. Tapped it is still `h`, and `get_quick_tap_term()` returns 120 ms so
tap-then-hold autorepeats `h` for vim motion instead of firing the modifier. A
cold hold still gives Ctrl.

*Superseded.* `H` was previously plain, with Shift on `L` and no right-hand Cmd at
all. That left every Cmd+left-letter chord on one hand — `Cmd+A` was not typeable,
since Cmd lived on `A` — which is why Nav originally carried dedicated
`NAV_UND`/`CUT`/`CPY`/`PST`/`ALL` keys.

*Amended.* Right-hand Cmd on `L` made those redundant except for `ALL`. Achordion
allows same-hand chords, so `Cmd+Z`/`X`/`C`/`V` are reachable by holding the `A`
home-row mod and tapping the letter. `Cmd+A` is the exception — `A` is itself the
Cmd key, so it cannot be its own chord target — so it kept a slot and moved to
`X`. The other four were deleted; `Z`, `C` and `V` fall through to Base.

**Top row.** The digits were originally gone entirely, moved to the Numbers layer.

*Amended: `1`-`4` are back on Base, and Shottr moved to Nav.* Aerospace switches
workspace on `⌥1`-`⌥4`, and Option is the home row `S`, so those positions have to
be plain digits for the habit to survive. The three Shottr captures moved to the
**same positions on the Nav layer**, still `Hyper+1`-`Hyper+3`, so the physical key
stays the number the user knows. This replaced an earlier attempt where the Base
keys checked `MOD_MASK_ALT` at runtime and sent either a digit or a Shottr chord —
moving Shottr to a layer does the same job with no code at all.

`5`-`0` remain on Numbers. `-` and `=` are off Base entirely; both have a home on
Symbols.

**Left outer column.** Row 2 is the best key in the column, because the pinky
slides sideways with no up or down stretch — it opens Clavier hint mode with
`F17`. A brush under 60 ms sends nothing, preventing an outward pinky roll off Cmd
from opening it. The function key is emitted on release, which is fine because
Clavier starts on key-down. Wispr is on row 0; the distance does not matter
because the key is held — reach once, speak, release. Escape stays on row 3: the
habit is strong, and habit beats the usual vim convention of moving it to Caps.

**Right outer column.** The rule "move load off the right hand" applies to keys
**pressed often**. A rare key on the right costs the wrist nothing, so `\` and `'`
stay.

### Nav

The right hand moves the cursor, the left hand edits. The left home row mods stay
live, so Shift, Option and Cmd with an arrow give select, word jump and line jump
without extra keys.

The right hand has 3 tiers: the bottom row holds the extreme of the arrow above it
(`Home` under `←`, `Page Down` under `↓`, `Page Up` under `↑`, `End` under `→`).
The top row holds the three Shottr captures and `F18` for Clavier scroll mode. The
middle row navigates the application — previous tab, next tab, back, forward —
which removes mouse work.

The left keys use the letter as the memory aid: `W` = select **W**ord, `E` = select
lin**E**. `SEL` is the Select Word module; `SLN` extends it to a full line. Only
`X` (`ALL`) still carries a dedicated chord.

The index-finger inward reach held `HRD`, the Herdr prefix, until the Clavier key
absorbed it. The Nav copy had a trap the Clavier key does not: the prefix is
followed by a key from the base layer, so the thumb had to release first or the
follow-up came off Nav instead.

### Numbers

The right hand is a calculator numpad, the left hand the operators.

`0` is on the right OUTER thumb, in the `Enter` position, which keeps `Backspace`
live on the inner thumb — that matters most when typing digits — and reads like a
real numpad, where `0` is the wide key below the digits.

The `L` position (pinky home) is dead. `Enter` was removed from it: the left inner
thumb already taps `Enter` on Base, so a second copy added memory load for no
reach benefit.

Two `=` keys are intentional. `T` groups it with the operators, `O` puts it in the
calculator position. The left key would otherwise be empty, and the pair lets you
type `4+5=` without crossing hands.

The left home row keeps the modifiers, so `Cmd+1` to `Cmd+9` still switch tabs and
desktops.

Nothing else goes here. Hex letters, parentheses and a thousands separator were
considered and rejected: memory load for a rare gain.

### Symbols

Rebuilt after [Getreuer's symbol layer](https://getreuer.info/posts/keyboards/symbol-layer/).
Four rules, in the order they matter:

1. **The right hand is brackets, and only brackets.** Middle finger opens, ring
   finger closes, three pairs stacked: `[]`, `()`, `{}`. One motion learned once
   covers all three. This replaced an older mirrored scheme where closing a
   bracket meant finding its mirror position on the other hand.
2. **The left hand is operators, rolling inward.** The common bigrams run from a
   weak finger toward the index: `!=` pinky to index, `+=` and `*=` middle to
   index, `<=` ring to index, `->` ring to middle.
3. **Nothing doubled sits on a pinky.** `==`, `++`, `--`, `//`, `**` are typed
   twice in a row, so they live on ring, middle and index. Pinkies take symbols
   that are never doubled: `` ` ``, `!`, `^`, `&`, `|`, `~`.
4. **The sore hand never reaches past its own home row.** The bracket pairs moved
   inward from `K`/`L` to `J`/`K`, and `%`/`?`/`@` folded in from the stretch `;`
   column onto the freed `L`. `:` and `$` moved off the right hand onto the left
   hand's otherwise-dead `F`/`G`: both are frequent in TypeScript, and the left
   hand is the one that is not sore.

This layer has no Shift key, so `+`, `~` and `_` **must** live here — `Shift+=`
and ``Shift+` `` are impossible while it is held.

### Accents

The mental model is "Shift, but for accents": hold the right thumb, tap the vowel,
release. To type `café`: tap `c` `a` `f`, then hold the thumb and tap `e`.

Hold is correct here, not one-shot. A true one-shot needs its own tap, which
cannot share the thumb without losing its tapped letter. The cost of the hold is
low because the most frequent accents (`á é ç ã`) are on the LEFT hand, opposite
the holding thumb; only the rarer `í ó ú` are on the same hand. The circumflex and
tilde variants (`ô`, `õ`) are on the home row so the sore hand does not stretch up.

Acute `´` sits on the vowel itself: `á é í ó ú` on `A` `E` `I` `O` `U`.

**Output method: macOS dead keys, not Unicode.** The firmware sends the built-in
macOS combinations, which needs zero macOS configuration and works on the default
layout. Unicode Hex Input was rejected: it takes over the Option key, which would
break the Option+arrow word jumps on Nav. Dead keys use Option only for a fraction
of a second.

Capitals are free — hold Shift and tap the accent key, and macOS composes `Á`.
Known limit: two-step dead keys do not work in Terminal. Acceptable, because the
user writes Portuguese in applications. `ç` is a direct combination, so it works in
Terminal too.

| Char | Send | Char | Send | Char | Send |
|---|---|---|---|---|---|
| `á` | ⌥e a | `ê` | ⌥i e | `ó` | ⌥e o |
| `à` | ⌥\` a | `í` | ⌥e i | `ô` | ⌥i o |
| `â` | ⌥i a | `ú` | ⌥e u | `õ` | ⌥n o |
| `ã` | ⌥n a | `é` | ⌥e e | `ç` | ⌥c |

### Media

One idea per finger, in a stack: index does previous track and volume down, middle
does play/pause and mute, ring does next track and volume up, pinky does stop.
Transport sits directly above volume, on the home row, so the sore hand travels the
shortest distance.

The stop key is almost useless on macOS, where most applications treat it as
play/pause. It stays because the user asked for it. Remove it first if the slot is
needed.

The trigger is a chord of both left thumbs, which costs no key. The thumbs are the
strongest fingers, they already rest there, and the reach is zero. It reads
logically: left inner alone is Nav, left outer alone is Numbers, both together are
the third layer.

The left hand holds the lighting controls. The top row is reserved for a launcher
row — see [Open items](#open-items).

### Mouse

The right half is empty: the right hand takes no part in pointer control.

*Superseded.* This layer was originally built on Getreuer's Orbital Mouse, whose
heading model — the pointer steers like a car — did not feel intuitive in use. The
module, the `MOU` toggle and the `MS_*` compat shims were all removed. The layer
was then restored from commit `53880a7` using plain `KC_MS_*` keycodes:
8-direction steering on the left hand, clicks on the left thumbs, acceleration on
the top row. `README.md` documents the current wheel and speed behaviour.

The keys are literal `WASD`, not a shifted variant, because the user already has
`WASD` in their hands from games and from the old keymap. With a gaming grip the
ring finger is on `A`, the middle on `W`/`S`, the index on `D`, and the pinky
floats over the outer column — so the outer column takes the keys you want when the
pointer misbehaves.

Drag, double click, middle click and horizontal scroll are deliberately absent.
All are rare, all would double the size of the layer, and the trackball is still
available. Add them once the basic keys become a habit.

---

## Lighting

**Base layer.** All keys use `HSV 191, 70, 231`, a soft lavender-purple. This is
the signature colour of the keymap.

**All other layers.** Light only the live keys, one hue per layer, so the colour
alone identifies the layer. This makes the board its own reference card: hold the
Nav thumb and only the Nav keys glow. It is the single most useful feature in the
build for the memory problem, which is goal number one.

This is not a module. No Getreuer feature provides it; it is a hand-written
`rgb_matrix_indicators_user()`.

*Amended at implementation time.* The plan was a per-layer `ledmap` array. The
firmware instead reads the live keys back out of `keymaps[]` at draw time: a key
lights if its keycode on the active layer is neither `KC_NO` nor `KC_TRNS`. Same
result in fewer lines, and it removes the failure mode where a key moves but its
colour does not. Each layer needs one hue, not a 52-entry table.

**The two cannot show at once.** Per-layer lighting repaints every LED every frame,
so it covers whatever RGB effect is running. ZSA's `TOGGLE_LAYER_COLOR` switches
between them and sits on the Media layer. Layer colours on is the teaching mode and
the default; off reveals PaletteFx. The setting does not survive a reboot, because
ZSA's handler never writes it to EEPROM.

**PaletteFx** is adopted for appearance only. The user said: "looks cool af, it's
not about the functional side." It is global and not layer-aware, so it does not
teach layers. Do not later "correct" this into a functional decision.

---

## Firmware and fork constraints

| Feature | Form | Use |
|---|---|---|
| Achordion | Getreuer, vendored | Prevents home row mod misfires. |
| Permissive Hold | QMK core | Used with Achordion. |
| Select Word | Getreuer, vendored | Nav layer `W` and `E`. |
| Mouse keys | QMK core | Mouse layer, plain `KC_MS_*`. |
| Autocorrect | QMK core | `qmk generate-autocorrect-data`. |
| PaletteFx | Getreuer, vendored | Appearance only. |
| Per-layer lighting | Hand-written | See [Lighting](#lighting). |

*Amended at implementation time.* The plan called for core Chordal Hold and the QMK
Community Modules form. Neither is available: `qmk/qmk_zsa_voyager` is ZSA's
`firmware23` branch, a fork of QMK from June 2024, which predates Chordal Hold
(QMK 0.28.0) and module support. So Getreuer's `achordion.c` is used instead, and
every feature is vendored under `features/` with `SRC +=` lines in `rules.mk`.
`config.h` also carries compat shims for names QMK introduced after the fork: the
`hsv_t` / `rgb_t` colour types and `MODIFIER_KEYCODE_RANGE`.

Revisit all of this if ZSA rebases the fork — Achordion and Chordal Hold solve the
same problem the same way.

**Achordion is configured to allow every chord**, same hand included. The default
opposite-hands rule cannot work on this board: Cmd is on the left pinky, so
`Cmd+T`/`W`/`R`/`Q`/`S`/`D`/`F`/`A`/`Z`/`X`/`C`/`V` are all left-hand chords and
every one resolved as two letters. `ACHORDION_STREAK` draws the better line
instead — mods are suppressed inside a fast run of letters, where misfires actually
come from, and allowed when you pause to reach for a chord deliberately.

Two exemptions have been carved out of the streak rule, both because a *lost* mod
costs more than a stray one:

- **Cmd and Ctrl, for the chords used mid-flow.** `Cmd+V` typed mid-sentence was
  resolving as the letters `av`. Only `Cmd+Z`/`X`/`C`/`V`/`S`/`A` and
  `Ctrl+A`/`E`/`K`/`W` are exempt.

  *Amended.* The exemption originally covered every Cmd and Ctrl chord. That let
  pinky lingers in ordinary words fire app shortcuts: `an` (the most frequent
  bigram after `a` in the user's own typing) gave `Cmd+N`, and `at`, `ar`, `a `
  gave `Cmd+T`, `Cmd+R` and `Cmd+Space`. Any other chord now needs only a brief
  pause after the last letter.
- **Shift in front of `/` `;` `'` `\`.** The streak rule exists to stop a stray
  capital mid-word, and punctuation cannot produce one. `why?` typed at speed came
  out `whyd/`. Comma and dot stay protected: `d,` and `d.` are frequent enough that
  exempting them would trade a rare lost `?` for a regular stray `<` or `>`.

`features/select_word.c` carries one local patch, a `SELECT_LINE_KEYCODE`, so `SLN`
can be its own key rather than Shift plus `SEL`. Upstream only reaches line
selection through Shift, and the state that makes repeat presses extend the
selection is file-private. Re-apply it if the file is refreshed upstream.

**Autocorrect and Portuguese.** The risk is low. Autocorrect is a whitelist of
typo-to-correction pairs that you supply, not a live English spellchecker, and it
cannot correct a word it was never taught. Its scope is a–z plus the apostrophe, so
accented Portuguese words pass through untouched. Use the `:word:` boundary markers
to prevent false matches inside longer words. Any held modifier except Shift clears
the buffer, so it does not interfere with vim normal mode.

---

## Design rules

Apply these to any future change.

1. **One key, one home.** A key that can move has one place. This killed `-` and `=`
   on the base top row.
   - Exception: a shifted character that the base layer produces for free is not a
     duplicate. `Shift+/` gives `?` the moment `/` lives on the base layer, and you
     cannot remove it without removing the letter. The Symbols copy is cheaper to
     press, so it earns its slot.
   - `+` and `~` **must** stay on the Symbols layer. That layer has no Shift key, so
     `Shift+=` and ``Shift+` `` are impossible there. `_` is on the layer for the
     same reason.
2. **Hold a layer with the hand opposite to its content.**
3. **Keep frequent keys off the top row.**
4. **Reduce the load on the right hand.** This applies to keys pressed often. Rare
   keys on the right side are free.
5. **Prefer an obvious position over a fast one.** Memory is the constraint.
6. **Release the thumb to return to Base.** Every daily layer is momentary, so `MO`
   and `LT` already do this. A `TO(0)` key is unnecessary.
7. **Chords are acceptable.** Do not treat "the user cannot remember chords" as a
   constraint. It was never their position.
8. **Existing muscle memory beats theory.** Keep `WASD`, Escape on the bottom outer
   key, and Cmd on `A`.

---

## Open items

- **Application-shortcut audit.** Inventory the hotkeys of every main application,
  resolve the conflicts, and mirror the important ones into the keymap as single
  keys. Applications: Shottr (done), Herdr (done), Wispr Flow, the browser, Raycast,
  the window manager, Karabiner, macOS itself, clavier.app. The free base top-row
  slots and the 2 free right outer keys are reserved for this. Herdr resolved
  without spending a base slot: its prefix is `Ctrl+;`, which no TUI can claim
  because it is not encodable as a legacy control code, and both its prefix and its
  palette reuse the Clavier key through a Karabiner branch on the frontmost
  application.
- **Launcher row.** The top row of the Media layer sends `F13` to `F20` to Raycast,
  which then runs scripts. A keyboard can only send keystrokes; it cannot run a
  script by itself. `F13` to `F20` are safe, because no physical Mac keyboard has
  them.
- **Single-key macros for modifier plus symbol.** Combinations such as `Cmd+[` and
  `Cmd+/` are painful when the symbol lives on a held layer. Make each frequent one
  a single key on the relevant layer. Nav already does this for back and forward.
  Collect the real list from the user.
- **Cmd chords.** `Cmd+C`, `Cmd+V`, `Cmd+X` and `Cmd+Z` are same-hand chords,
  because Cmd is on the left pinky. A later option is Cmd on a thumb, or a combo.
- **Shottr `Hyper+5`** (scrolling capture) is not mapped.
- **Accent layer extras.** `« »`, `º ª`, `– —` and `" "` are all Option
  combinations. Add them to the layer if the user wants them.
- **Alternative alphabet layout.** A hand-balanced layout such as Colemak-DH is more
  justified than before, because of the wrist. Revisit only if the wrist stays sore
  after this foundation.

**Expected to change by feel:**

- The tapping term.
- `-` on the Symbols layer. It is frequent (hyphens, kebab-case, `--flags`) and it
  costs a right thumb hold on the sore hand. The key itself is on the left index, so
  the hold is light, but confirm with real typing.
- The accent positions.
- The Symbols positions.
- **Layer Lock.** Dropped for version 1, because this design already avoids the pain
  it solves: the holding thumb never fights the typing hand. Add it if the user
  thinks "I have held Tab for a long time" during long runs of digits. It must go on
  the RIGHT hand, because the left thumb is busy.
- **Repeat Key.** Repeats the last keypress; Alternate Repeat does the opposite
  action. It would reduce right-hand load if it sits on the left hand, but it is
  blocked on placement — the left hand has no free comfortable key. Revisit if the
  shortcut audit frees a good slot.

---

## Rejected

Do not propose these again without a new reason.

| Item | Reason |
|---|---|
| Caps Word | The user rarely writes SCREAMING_CASE, so it would never fire. |
| Sentence Case | Portuguese abbreviations (`Sr.`, `Dr.`, `Av.`) trigger it falsely. It needs a hand-maintained exception list. |
| Custom Shift Keys | Each entry is one more exception to remember, and there is no specific annoyance to fix. |
| F1–F12 | The user barely uses them. They would fill a free row tidily but not usefully. |
| A "back to Base" key | Releasing the thumb already returns to Base. |
| Leader Key | It needs sequence memorization, which is wrong when memory is the problem. Use Raycast or Espanso for text expansion. |
| Dynamic Macros | They do not survive a reboot. |
| Callum-style one-shot mods | Redundant with home row mods. |
| Orbital Mouse | The heading model did not feel intuitive in use. Replaced by plain `KC_MS_*` keys. |
| SOCD Cleaner | For games only. |
| Mouse Turbo Click | Not worth a slot. |
| EurKey | It would cut keystrokes for English plus Portuguese, but it needs a change of the system input source. The accent layer deliberately needs zero macOS configuration. |
| romak Ç-extension | `ç` becomes a one-shot that gives `ã`, `õ` and the `-ão` / `-ões` word macros. High effort and very specific. Revisit only on request. |
| Flow Tap | Reduces mod-tap misfires during fast rolls. Only add it if accidental mods appear that `ACHORDION_STREAK` does not catch. |

Tap Dance was also rejected on the grounds that "what does N taps do" is the exact
problem this redesign removes. One isolated exception now exists: the LoL toggle on
the otherwise-empty bottom-right key. It is acceptable because it sits alone, on a
key with no tap function to compete with, and it guards a layer stack that is not
part of the daily layout.

**Keyboard Maestro cleanup.** The "Select a word" and "Select a line" macros are
replaced by the firmware Select Word module. Delete them after the firmware works.
The `;` browser leader key is a separate ccstone multi-press template and is
unrelated to Portuguese. Keep or disable it freely.

---

## Rendering

There are deliberately no layout diagrams above. Generate them from the firmware,
so they cannot drift:

```bash
cd /Users/f/Core/dev/keyboard/qmk/qmk_zsa_voyager
qmk c2json -kb voyager -km f.qwerty keymap.c > keymap.json
```

Then feed `keymap.json` to [keymap-drawer](https://caksoylar.github.io/keymap-drawer)
for an SVG. It handles the Voyager physical layout, hold-tap keys and combos.

For a live view while typing, the Probe HUD reads the layer state off Raw HID —
see `README.md`.
