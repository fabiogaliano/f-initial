# f.qwerty — Keymap Specification

This document specifies the keymap for the ZSA Voyager and records why each
decision was made. `keymap.c` now exists and is built, so **`keymap.c` is the
source of truth**; this document is the rationale behind it.

The keymap has 7 layers. All keys are assigned; Mouse remains deliberately unreachable.

Two things were amended when the firmware was written, both because ZSA's QMK
fork is older than this plan assumed: see the note in section 5 (Achordion in
place of Chordal Hold, vendored files in place of community modules) and in
section 4 (lighting derived from the keymap rather than a per-layer table).

Two things were amended after living with the board:

**The Mouse layer and Orbital Mouse were removed.** Orbital Mouse's heading model
did not feel intuitive in use. Layer 6, the `MOU` toggle, `MOUSEKEY_ENABLE`, the
`features/orbital_mouse.*` files and the `MS_*` compat shims are all gone; section
3's Layer 6 and the Mouse parts of sections 5, 6 and 8 are kept below as history
only. The left outer row 2 key is now dedicated to Clavier instead of Mouse.

**Then the pre-redesign mouse layer was restored** from commit `53880a7`, using plain
`KC_MS_*` keycodes: 8-direction steering on the left hand, clicks on the left thumbs,
acceleration on the top row. `QK_LLCK` and `TD(DANCE_8)` were dropped, since layer
lock and tap dance stay disabled. **Nothing activates it yet** - it is deliberately
unreachable until an activation key is chosen.

**Space and Enter went back to their pre-redesign thumbs.** The rule in section 7
about loading the left thumb moved Space to the left, but a thumb press on a light
switch is near the lowest-strain action on the board, so the benefit did not repay
the daily cost of unlearning. The tapped letters moved; the **layers did not**.
Space and Enter simply traded slots: `LT_NAV` is now `LT(NAV, KC_ENT)` on the left
inner thumb and `LT_ACC` is `LT(ACC, KC_SPC)` on the right outer. Tab and Backspace
did not move. This keeps Nav opposite its right-hand arrow cluster and keeps Media a
two-left-thumb chord. Section 3's layer table reflects the new thumbs.

---

## 1. Requirements

**Goals**

- Use layers. The current keymap has 12 layers, but the user uses almost none of them.
- Remove the number row from normal typing. The top row is bad for vim counts and motions.
- Move Shift off the outer pinky.
- Type Portuguese accents while the system stays in English.
- Keep QWERTY. Do not change to an alternative alphabet layout.

**Constraints**

- The Voyager has 52 keys. It has 4 thumb keys, 2 for each hand. Thumb keys are scarce.
- The primary operating system is macOS.
- The firmware is built from source with QMK. Community modules are available.
- The user is a heavy vim user.
- The user writes English and Portuguese.

**Medical constraint**

The user has chronic light inflammation in the RIGHT wrist. Every decision moves
load to the left hand. Four rules follow from this:

- Put the heavy thumb keys on the left thumb.
- Keep frequent keys off the top row.
- Keep the right pinky reaches short.
- Move pointer control off the right hand.

**Design principle**

Memory is the primary constraint, not speed. The user does not remember layers today.
So: use few layers, put keys where their meaning is obvious, and keep the rules
consistent. Example: `Z` `X` `C` `V` keep undo, cut, copy and paste, because those
positions are already known.

---

## 2. Notation

Each layer map shows the physical Voyager: an outer pinky column, a number row,
3 alphabet rows, and 2 thumb keys for each hand.

| Symbol | Meaning |
|---|---|
| `—` | Transparent. The key falls through to the base layer. |
| `×` | Dead. The key does nothing (`KC_NO`). |

Key positions are named after the **stock** Voyager layout. The name `T` means
the physical `T` position, not the character that the key sends.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ - │ 1 │ 2 │ 3 │ 4 │ 5 │         │ 6 │ 7 │ 8 │ 9 │ 0 │ = │  row 0
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│out│ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │out│  row 1
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│out│ A │ S │ D │ F │ G │         │ H │ J │ K │ L │ ; │out│  row 2
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│out│ Z │ X │ C │ V │ B │         │ N │ M │ , │ . │ / │out│  row 3
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │ L1│ L2│               │ R1│ R2│   thumbs
              └───┴───┘               └───┴───┘
```

---

## 3. Layers

| # | Layer | Access |
|---|---|---|
| 0 | Base | — |
| 1 | Nav | Hold left inner thumb (`Enter`) |
| 2 | Numbers | Hold left outer thumb (`Tab`) |
| 3 | Symbols | Hold right inner thumb (`Backspace`) |
| 4 | Accents | Hold right outer thumb (`Space`) |
| 5 | Media | Hold both left thumbs (`Enter` + `Tab`) |
| 6 | Mouse | Unreachable |

The layer headings further down still name the pre-swap tap letters. Read them by
thumb position: Nav and Numbers are the left thumbs, Symbols and Accents the right.

Each layer is held by the hand opposite to its content. The holding thumb does not
fight the typing hand.

### Layer 0 — Base

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│WSP│ 1 │ 2 │ 3 │ 4 │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│HYP│ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │ \ │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│CLV│ A │ S │ D │ F │ G │         │ H │ J │ K │ L │ ; │ ' │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ESC│ Z │ X │ C │ V │ B │         │ N │ M │ , │ . │ / │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │SPC│TAB│               │BSP│ENT│
              └───┴───┘               └───┴───┘
   hold: Nav ─┘   └─ Num        Sym ─┘   └─ Accents
              └── both = Media ──┘
```

**Home row mods**

The user rests on `A`-`S`-`D`-`F` and `H`-`J`-`K`-`L`. The right hand therefore
sits one column inward from the usual `J`-`K`-`L`-`;`, and every placement below
follows from that. Note that this document elsewhere labels the right home row
with standard fingering, where `L` is the ring finger; under this rest position
`L` is the pinky.

| Finger | Left | Mod | Right | Mod |
|---|---|---|---|---|
| pinky | `A` | Cmd ⌘ | `L` | Cmd ⌘ |
| ring | `S` | Option ⌥ | `K` | Option ⌥ |
| middle | `D` | Ctrl | `J` | Ctrl |
| index | `F` | **Shift** | `H` | **Shift** |

A finger-for-finger mirror. Read straight across the board it is a palindrome:
Cmd Opt Ctrl Shift │ Shift Ctrl Opt Cmd. One rule covers both hands.

The mirror is taken across the *fingers*, not across the two halves. A physical
mirror would pair `A` with `;` and `F` with `J`, which is wrong here because the
right hand is shifted inward — `;` sits outside the rest position entirely and
stays a plain key.

Shift is on the index because it is the most-used modifier and the index is the
strongest finger. It also means an inward roll can never end on a held Shift, so
fast rolls cannot produce stray capitals. Cmd, the most-used modifier after Shift
on macOS, is on the pinky to keep the existing left-hand habit; the weak middle
and ring fingers get Ctrl and Option, which are held only briefly.

`H` carries Shift despite being the most frequent letter on that hand and the
left arrow on the Nav layer. Tapped it is still `h`, and `get_quick_tap_term`
returns 120 ms for it so that tap-then-hold autorepeats `h` for vim motion
instead of firing Shift. A cold hold is still Shift.

**Superseded.** `H` was previously plain, with Shift on `L` and no right-hand
Cmd at all. That left every `Cmd`+left-letter chord on one hand — `Cmd+A` was
not typeable at all, since Cmd lived on `A` — which is why the Nav layer carries
`NAV_UND`/`CUT`/`CPY`/`PST`/`ALL`. Those are now a convenience rather than the
only way to reach those shortcuts.

**Top row**

The digits are gone. They live on the Numbers layer.

**Amended: the digits are back on Base, and Shottr moved to Nav.** Aerospace
switches workspace on `⌥1`-`⌥4` and Option is the home row `S`, so the digit row
has to be plain digits for that habit to survive. Positions `1`-`4` are now
`KC_1`-`KC_4`. The three Shottr captures moved to the **same positions on the Nav
layer**, still `Hyper+1`-`Hyper+3`, so the physical key stays the number the user
knows. `Hyper+5` (scrolling capture) is still unmapped.

This replaced an earlier attempt where the Base keys checked `MOD_MASK_ALT` at
runtime and sent either a digit or a Shottr chord. Moving Shottr to a layer does
the same job with no code at all.

The digits are otherwise gone from Base; `5`-`0` live on the Numbers layer.

`-` and `=` are removed from the base layer. Both have a home on the Symbols layer.

**Left outer column**

| Row | Key | Function |
|---|---|---|
| 0 | `WSP` | Wispr Flow push-to-talk. Sends `F13`, held. |
| 1 | `HYP` | Hyper (`KC_HYPR`). Used for Shottr and global hotkeys. |
| 2 | `CLV` | Clavier. Sends `F17` on release after a 60 ms press. |
| 3 | `ESC` | Escape. Plain key, no hold function. |

Row 2 is the best key in the column, because the pinky slides sideways with no
up or down stretch. It opens Clavier hint mode with `F17`. A short brush under
60 ms sends nothing, preventing an outward pinky roll off Cmd from opening it.
The function key is emitted on release, which is acceptable because Clavier
starts when macOS receives its key-down event.

Wispr is on row 0. The distance does not matter, because the key is held: the user
reaches once, keeps the finger there, speaks, and releases.

Escape stays on row 3. The habit is strong, and habit is more valuable than the
usual vim convention of moving Escape to the Caps position.

**Right outer column**

| Row | Key | Note |
|---|---|---|
| 0 | `×` | Reserved. |
| 1 | `\` | Rare, but already habitual. |
| 2 | `'` | Frequent in English contractions. Easy sideways position. |
| 3 | `×` | Reserved. |

The rule "move load off the right hand" applies to keys that are **pressed often**.
A rare key on the right side costs the wrist nothing. So `\` and `'` stay.

### Layer 1 — Nav (hold left `Space`)

The right hand moves the cursor. The left hand edits. The left home row mods stay
live, so `Shift`, `Option` and `Cmd` with an arrow give select, word jump and line
jump. No extra keys are needed for those.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │S1 │S2 │S3 │SCR│ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ESC│SEL│SLN│RDO│ — │         │TB←│TB→│BCK│FWD│ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │CMD│OPT│CTL│SFT│FND│         │ ← │ ↓ │ ↑ │ → │ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │UND│CUT│CPY│PST│ALL│         │HOM│PGD│PGU│END│ — │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
```

The right hand has 3 tiers. The bottom row holds the extreme of the arrow above it:
`Home` under `←`, `Page Down` under `↓`, `Page Up` under `↑`, `End` under `→`.

The top row holds the three Shottr captures and `F18` for Clavier scroll mode;
the next row navigates the application: previous tab, next tab, back, forward.
This removes mouse work.

The left keys use the letter as the memory aid: `W` = select **W**ord,
`E` = select lin**E**, `G` = find (**G**rep), and `Z` `X` `C` `V` `B` keep the
standard macOS edit positions.

`SEL` is the Select Word module. `SLN` extends the same module to a full line.

### Layer 2 — Numbers (hold left `Tab`)

The right hand holds a calculator numpad. The left hand holds the operators.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ + │ − │ * │ / │ = │         │ 7 │ 8 │ 9 │ = │ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │CMD│OPT│CTL│SFT│ — │         │ 4 │ 5 │ 6 │ENT│ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ — │ — │ — │ — │ — │         │ 1 │ 2 │ 3 │ . │ — │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │ — │hold               │BSP│ 0 │
              └───┴───┘               └───┴───┘
```

`0` is on the right OUTER thumb, in the `Enter` position. `Enter` is already on this
layer at `L`, in the calculator position, so the thumb copy is not needed. This keeps
`Backspace` live on the inner thumb, which matters most when you type digits.
The position also reads like a real numpad, where `0` is the wide key below the digits.

Two `=` keys are intentional. `T` groups it with the operators. `O` puts it in the
calculator position. The left key would otherwise be empty, and the pair lets you
type `4+5=` without a hand crossing over.

The left home row keeps the modifiers, so `Cmd+1` to `Cmd+9` still switch tabs
and desktops.

Nothing else goes on this layer. Hex letters, parentheses and a thousands separator
were considered and rejected: they add memory load for a rare gain.

### Layer 3 — Symbols (hold right inner thumb)

**Rebuilt after Getreuer's first symbol layer**
(<https://getreuer.info/posts/keyboards/symbol-layer/>). The original mirrored
design below it is kept as history at the end of this section.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ ` │ < │ > │ × │ × │         │ & │ × │ [ │ ] │ % │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ ! │ - │ + │ = │ # │         │ | │ : │ ( │ ) │ ? │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ ^ │ / │ * │ _ │ € │         │ ~ │ $ │ { │ } │ @ │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
   pnky ring mid  ix  inner        inner  ix  mid ring pnky
```

Three rules, in the order they matter:

1. **The right hand is brackets, and only brackets.** Middle finger opens, ring
   finger closes, three pairs stacked: `[]`, `()`, `{}`. One motion learned once
   covers all three. This replaces the old mirrored scheme, where closing a
   bracket meant finding its mirror position on the other hand.
2. **The left hand is operators, rolling inward.** The common bigrams run from a
   weak finger toward the index: `!=` pinky to index, `+=` and `*=` middle to
   index, `<=` ring to index, `->` ring to middle.
3. **Nothing doubled sits on a pinky.** `==`, `++`, `--`, `//`, `**` are all typed
   twice in a row, so they live on ring, middle and index. Pinkies take the
   symbols that are never doubled: `` ` ``, `!`, `^`, `&`, `|`, `~`.

The three dead slots held `"`, `.` and a `::` macro in Getreuer's original. The
first two are on the base layer here and the third is not wanted, so they stay
dead rather than take invented filler.

`, . / ' ; \\` stay on the base layer. They need no slot here.

A number-order top row (`!@#$%^&*`) was rejected: it spends the best keys on rare
symbols. Code combination keys (`=>`, `->`, `${}`) were also rejected. Add them later
if the user wants them.

**Superseded design.** The layer was originally a mirror, with each bracket pair on
the same finger of opposite hands (`< [ { ( =` against `| ) } ] >`). It was coherent
but made every bracket pair a two-hand alternation, and the mirror had to be recalled
rather than felt. Replaced in favour of same-hand rolls.

### Layer 4 — Accents (hold right `Enter`)

The mental model is "Shift, but for accents". Hold the right thumb, tap the vowel,
release. To type `café`: tap `c` `a` `f`, then hold the thumb and tap `e`.

Hold is correct here, not one-shot. A true one-shot needs its own tap, which cannot
share the `Enter` thumb without the loss of `Enter`. The cost of the hold is low,
because the most frequent accents (`á é ç ã`) are all on the LEFT hand, opposite the
thumb that holds. Only the rarer `í ó ú` are on the same hand.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ â │ — │ é │ — │ — │         │ — │ ú │ í │ ó │ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ á │ ã │ ê │ — │ — │         │ — │ — │ ô │ õ │ — │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ à │ — │ ç │ — │ — │         │ — │ — │ — │ — │ — │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
```

Three rules and one exception cover the whole layer:

1. **Acute ´ is on the vowel itself.** `á é í ó ú` on `A` `E` `I` `O` `U`.
2. **Circumflex ^ is on the middle-finger home key.** `ê` on `D`, `ô` on `K`.
3. **Tilde ~ is on the ring-finger home key.** `ã` on `S`, `õ` on `L`.
4. **`ç` is on `C`**, its own letter.
5. **Exception for A.** `A` is on the weak pinky and has no middle home key of its
   own. So its two extra forms go around it: `à` on `Z` (below `A`) and `â` on `Q`
   (above `A`). `à` is more frequent, so it gets the easier down key. The `^` of `â`
   points up, which matches `Q`.

`é í ó ú` are on the top row, because the QWERTY vowels are there. This is acceptable:
the layer is held and occasional, unlike the old number row. The two right-hand
variants (`ô` and `õ`) are on the home row, so the sore hand does not stretch up.

**Output method: macOS dead keys, not Unicode.**

The firmware sends the built-in macOS accent combinations. This needs zero macOS
configuration and works on the default keyboard layout.

Unicode Hex Input was rejected. It takes over the Option key, which would break the
Option+arrow word jumps on the Nav layer. Dead keys use Option only for a fraction of
a second.

Capital letters are free: hold Shift and tap the accent key, and macOS composes `Á`.

Known limit: two-step dead keys do not work in Terminal. This is acceptable, because
the user writes Portuguese in applications. `ç` is a direct combination, so it works
in Terminal too.

| Char | Send | Char | Send | Char | Send |
|---|---|---|---|---|---|
| `á` | ⌥e a | `ê` | ⌥i e | `ó` | ⌥e o |
| `à` | ⌥\` a | `í` | ⌥e i | `ô` | ⌥i o |
| `â` | ⌥i a | `ú` | ⌥e u | `õ` | ⌥n o |
| `ã` | ⌥n a | `é` | ⌥e e | `ç` | ⌥c |

### Layer 5 — Media (hold both left thumbs)

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │  reserved: launchers
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │RGB│RGB│RGB│RGB│ × │         │ × │ × │ × │ × │ × │ × │  lighting controls
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ × │ × │ × │ × │ × │         │ ⏮ │ ⏯ │ ⏭ │ ■ │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ × │ × │ × │ × │ × │         │ 🔉│ 🔇│ 🔊│ × │ × │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
```

One idea for each finger, in a stack: the index does previous track and volume down,
the middle does play/pause and mute, the ring does next track and volume up, and the
pinky does stop. Transport is directly above volume, on the home row, so the sore hand
travels the shortest distance.

The stop key is almost useless on macOS, because most applications treat it as
play/pause. It stays because the user asked for it. Remove it first if the slot
is needed.

The trigger is a chord of both left thumbs. This costs no key. The thumbs are the
strongest fingers, they already rest there, and the reach is zero. It reads logically:
`Space` alone is Nav, `Tab` alone is Numbers, and both together are the third layer.

The left hand holds the lighting controls: RGB on/off, brightness, effect cycle and
palette cycle. The exact positions are set when `keymap.c` is written.

The top row is reserved for a launcher row. See section 8.

### Layer 6 — Mouse (toggle with `MOU`)

The right half of this layer is empty. The right hand takes no part in pointer control.

The module is Orbital Mouse. It is not a classic mouse-key layer. The pointer works
like a car: it always has a heading. `FWD` and `BCK` drive along the heading. The
left and right keys turn the heading, they do not move the pointer sideways. So you
can travel at any angle with one key held, instead of 8 fixed directions that need
two keys.

```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ × │ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ × │ ⇑ │FWD│ ⇓ │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│OFF│ ↰ │BCK│ ↱ │ × │ × │         │ × │ × │ × │ × │ × │ × │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│SLO│ × │ × │ × │ × │ × │         │ × │ × │ × │ × │ × │ × │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │L-C│R-C│               │ × │ × │
              └───┴───┘               └───┴───┘
```

| Position | Keycode | Function |
|---|---|---|
| `W` / `S` | `OM_U` / `OM_D` | Drive forward / drive backward |
| `A` / `D` | `OM_L` / `OM_R` | Turn left / turn right |
| `Q` / `E` | `OM_W_U` / `OM_W_D` | Scroll up / scroll down |
| Outer row 2 | `TG(MOUSE)` | Turn the layer off |
| Outer row 3 | `OM_SLOW` | Hold for slow, precise movement |
| Left thumb 1 | `OM_BTN1` | Left click |
| Left thumb 2 | `OM_BTN2` | Right click |

The layout matches how the hand actually sits. With a gaming grip the ring finger is
on `A`, the middle finger is on `W` and `S`, and the index finger is on `D`. The pinky
floats free over the outer column, so it takes `OFF` and `SLOW`. Those are the two
things you want when the pointer misbehaves.

The keys are literal `WASD`, not a shifted variant. The user already has `WASD` in
their hands from games and from the old keymap.

Scroll down is on `E` and scroll up is on `Q`. Scroll down is far more frequent when
you read, so it gets the stronger finger.

These are **not** in version 1: drag (`OM_HLDS` / `OM_RELS`), double click (`OM_DBLS`),
middle click, button-selection keys (`OM_SEL*`) and horizontal scroll. All are rare,
all would double the size of the layer, and the trackball is still available. Add them
after the basic keys become a habit.

---

## 4. Lighting

**Base layer.** All keys use `HSV 191, 70, 231`, a soft lavender-purple. This is the
signature colour of the current keymap.

**All other layers.** Light only the live keys. Set every dead key to `0,0,0`. Give
each layer its own hue, so the colour alone identifies the layer.

This makes the board its own reference card. Hold `Space` and only the Nav keys glow.
Hold `Tab` and only the numpad glows. This is the single most useful feature in the
build for the memory problem, which is goal number 1.

This is **not** a module. No Getreuer feature provides it. It is a hand-written
`rgb_matrix_indicators_user()`.

**Amended at implementation time.** The plan was a per-layer `ledmap` array, like
the old keymap. The firmware instead reads the live keys back out of `keymaps[]`
at draw time: a key lights if its keycode on the active layer is neither `KC_NO`
nor `KC_TRNS`. This is the same result in fewer lines, and it removes the failure
mode where a key moves but its colour does not. Each layer therefore only needs
one hue, not a 52-entry table. The base layer is the exception and lights every
key in the signature lavender.

**The two cannot show at once.** Per-layer lighting repaints every LED on every
frame, so it covers whatever RGB effect is running. ZSA's `TOGGLE_LAYER_COLOR`
switches between them and sits on the Media layer at `T`. Layer colours on is the
teaching mode and the default; layer colours off reveals PaletteFx. The setting
does not survive a reboot, because ZSA's handler never writes it to EEPROM.

**PaletteFx** is adopted for appearance only. The user said: "looks cool af, it's not
about the functional side." It has 6 animated effects and 16 palettes. It is global
and it is not layer-aware, so it does not teach layers. Do not later "correct" this
into a functional decision. It works together with the per-layer lighting above.

---

## 5. Modules and firmware features

| Module | Form | Use |
|---|---|---|
| Achordion | Getreuer `features/` | Prevents home row mod misfires. |
| Permissive Hold | QMK core | Used with Achordion. |
| Select Word | Getreuer `features/` | Nav layer `W` and `E`. |
| Orbital Mouse | Getreuer `features/` | Mouse layer. |
| Autocorrect | QMK core | `qmk generate-autocorrect-data`. |
| PaletteFx | Getreuer `features/` | Appearance only. |
| Per-layer lighting | Hand-written | See section 4. |

**Amended at implementation time.** This plan called for core Chordal Hold and the
QMK Community Modules form. Neither is available: `qmk/qmk_zsa_voyager` is ZSA's
`firmware23` branch, a fork of QMK from June 2024, which predates Chordal Hold
(QMK 0.28.0) and module support. So Getreuer's `achordion.c` is used instead, and
every feature is vendored as a copy under `f.qwerty/features/` with `SRC +=` lines
in `rules.mk`.

Revisit both decisions if ZSA rebases the fork. Nothing else in this document
depends on the choice — Achordion and Chordal Hold solve the same problem the
same way.

`config.h` also carries compat shims for names QMK introduced after the fork:
the `MS_*` mouse keycodes, the `hsv_t` / `rgb_t` colour types, and
`MODIFIER_KEYCODE_RANGE`. Delete them when the fork moves forward.

Achordion is configured to allow **same-hand layer taps**. The default rule only
holds a tap-hold key when the other key is on the opposite hand, which would break
the Nav and Numbers layers: the left thumb holds both, and the left half of both
layers is full of live keys. Home row mod-taps keep the opposite-hands rule.

`features/select_word.c` has one local patch: a `SELECT_LINE_KEYCODE`, so `SLN`
can be its own key rather than Shift plus `SEL`. Upstream only reaches line
selection through Shift, and the state that makes repeat presses extend the
selection is file-private.

**Autocorrect and Portuguese.** The risk is low. Autocorrect is a whitelist of
typo-to-correction pairs that you supply. It is not a live English spellchecker, and
it cannot correct a word that it was never taught. Its scope is a–z plus the
apostrophe, so accented Portuguese words pass through untouched. Start from the small
example dictionary of about 71 entries, not the 400-entry one. Use the `:word:`
boundary markers, to prevent false matches inside longer words. Any held modifier
except Shift clears the buffer, so it does not interfere with vim normal mode.

---

## 6. Implementation notes

Build commands are in `f.qwerty/CLAUDE.md`.

**Home row mods.** Set the tapping term to about 200 ms and tune it on the hardware.
Delete the old `get_tapping_term()` special cases for `KC_J` and `KC_K`. They belong
to a previous setup.

**Media trigger.** Use the standard tri-layer pattern:
`update_tri_layer_state(state, NAV, NUM, MEDIA)` in `layer_state_set_user()`.

**Wispr key.** Use `register_code(KC_F13)` on press and `unregister_code(KC_F13)` on
release. Do not use `tap_code`: the key must stay down while the user speaks. If you
forget the release, the key stays down forever. Also confirm that the key does not
interfere with the Chordal Hold timing window.

`F13` is used because no physical Mac keyboard has that key. So it cannot collide with
an application shortcut or with the Option-based accent macros. Configure Wispr Flow
to listen on `F13`.

**Accent keys.** Each key is a small macro, for example `SS_LOPT("e") "a"`. See the
table in the Accents section. `€` uses the same mechanism: ⌥⇧2.

**Orbital Mouse.**

- Add `SRC += features/orbital_mouse.c` and `MOUSE_ENABLE = yes` to `rules.mk`.
- Call `process_orbital_mouse()` from `process_record_user()`.
- Call `orbital_mouse_task()` from `housekeeping_task_user()`.
- Orbital Mouse reuses the stock mouse keycodes. `OM_U` **is** `MS_UP`, with different
  behaviour. It also reuses `UC(0x41)` to `UC(0x4a)`.
- Documentation: <https://getreuer.info/posts/keyboards/orbital-mouse>

**Dead outer columns.** The outer columns are `KC_NO` on Nav, Numbers, Symbols and
Accents. If they stay transparent, the four left pinky keys are still Wispr, Hyper,
Mouse and Escape while you hold a layer. Wispr, Hyper and Escape are harmless, but
`MOU` is a **toggle**: one stray press puts the board into mouse mode, with no obvious
cause and no automatic recovery. The Accents layer is the worst case, because `à` (Z),
`â` (Q) and `á` (A) are all next to that column.

The outer columns stay live on Base and on Mouse, where they hold `OFF` and `SLOW`.

**Old code to delete.** The tap dance `TD(DANCE_0)` on the bottom right is dead. It
was a single tap of `Option+E` and a double tap to layer 7. The accent method replaces
the first, and layer 7 no longer exists.

---

## 7. Design rules

Apply these rules to any future change.

1. **One key, one home.** A key that can move has one place. This killed `-` and `=`
   on the base top row.
   - Exception: a shifted character that the base layer produces for free is not a
     duplicate. `Shift+/` gives `?` the moment `/` lives on the base layer, and you
     cannot remove it without the removal of the letter. The Symbols copy is cheaper
     to press, so it earns its slot.
   - `+` and `~` **must** stay on the Symbols layer. That layer has no Shift key, so
     `Shift+=` and ``Shift+` `` are impossible there. `_` is on the layer for the same
     reason.
2. **Hold a layer with the hand opposite to its content.**
3. **Keep frequent keys off the top row.**
4. **Reduce the load on the right hand.** This applies to keys that you press often.
   Rare keys on the right side are free.
5. **Prefer an obvious position over a fast one.** Memory is the constraint.
6. **Release the thumb to return to Base.** Every layer is momentary, so `MO` and `LT`
   already do this. A `TO(0)` key is unnecessary.
7. **Chords are acceptable.** Do not treat "the user cannot remember chords" as a
   constraint. It was never their position.
8. **Existing muscle memory beats theory.** Keep `WASD`, Escape on the bottom outer
   key, and Cmd on `A`.

---

## 8. Open items

- **Application-shortcut audit.** Inventory the hotkeys of every main application,
  resolve the conflicts, and mirror the important ones into the keymap as single keys.
  Record the result in this file. Applications: Shottr (done), Wispr Flow, the browser,
  Herd, Raycast, the window manager, Karabiner, macOS itself, clavier.app.
  The 9 free base top-row slots and the 2 free right outer keys are reserved for this.
- **Launcher row.** The top row of the Media layer sends `F13` to `F20` to Raycast,
  which then runs scripts. A keyboard can only send keystrokes; it cannot run a script
  by itself. `F13` to `F20` are safe, because no physical Mac keyboard has them.
- **Single-key macros for modifier plus symbol.** Combinations such as `Cmd+[` and
  `Cmd+/` are painful when the symbol lives on a held layer. Make each frequent one a
  single key on the relevant layer. The Nav layer already does this for back and
  forward. Collect the real list from the user.
- ~~**Layer-cheatsheet overlay.**~~ Solved by **Probe** (`/Users/f/Core/dev/clones/probe`),
  a native macOS HUD that reads Raw HID telemetry from the Voyager and renders the live
  layer. It needs `ORYX_ENABLE = yes`, which `rules.mk` already sets. Probe labels keys
  from an imported copy of `keymap.c`, so `scripts/sync-probe.sh` pushes both the keymap
  and `f.qwerty/probe-labels.json` after every flash. Close ZSA Keymapp before using it —
  both claim the same Raw HID interface and only one gets it.
- **Cmd chords.** `Cmd+C`, `Cmd+V`, `Cmd+X` and `Cmd+Z` are same-hand chords, because
  Cmd is on the left pinky. A later option is Cmd on a thumb or a combo.
- **Shottr `Hyper+5`** (scrolling capture) is not mapped.
- **Accent layer extras.** `« »`, `€`, `º ª`, `– —` and `" "` are all Option
  combinations. Add them to the layer if the user wants them.
- **Alternative alphabet layout.** A hand-balanced layout such as Colemak-DH is more
  justified than before, because of the wrist. Revisit only if the wrist stays sore
  after this foundation.

**Check after the first flash.** These decisions are expected to change by feel:

- The tapping term.
- `-` on the Symbols layer. It is frequent (hyphens, kebab-case, `--flags`) and it now
  costs a right thumb hold on the sore hand. The key itself is on the left index, so
  the hold is light, but confirm with real typing.
- The accent positions.
- The Symbols positions.
- **Layer Lock.** It is dropped for version 1, because this design already avoids the
  pain that it solves: the holding thumb never fights the typing hand. Add it if the
  user thinks "I have held Tab for a long time" during long runs of digits. It must go
  on the RIGHT hand, because the left thumb is busy. Use the standard pattern:
  `QK_LAYER_LOCK` on Base and `KC_TRNS` on every other layer.
- **Repeat Key.** It repeats the last keypress, and Alternate Repeat does the opposite
  action (Page Down becomes Page Up). It would reduce right-hand load if it sits on
  the left hand. It is blocked on placement: the left hand has no free comfortable key.
  Revisit if the shortcut audit frees a good slot. Use the QMK core version, not the
  older `features/` copy, and call it after Chordal Hold.

---

## 9. Rejected

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
| Callum-style one-shot mods | Redundant with home row mods and Chordal Hold. |
| Tap Dance | "What does N taps do" is the exact problem that this redesign removes. |
| SOCD Cleaner | For games only. |
| Mouse Turbo Click | Orbital Mouse replaces it. |
| EurKey | It would cut keystrokes for English plus Portuguese, but it needs a change of the system input source. The accent layer deliberately needs zero macOS configuration. |
| romak Ç-extension | `ç` becomes a one-shot that gives `ã`, `õ` and the `-ão` / `-ões` word macros. High effort and very specific. Revisit only on request. |
| Flow Tap | Reduces mod-tap misfires during fast rolls. Only add it if accidental mods appear after the flash. |

**Old layers to archive.** Done. The League of Legends layers (old 9, 10, 11), the
layer switcher (old 7) and the chat-flow keycodes are in `f.qwerty/archive/league.md`.

**Keyboard Maestro cleanup.** The "Select a word" and "Select a line" macros are
replaced by the firmware Select Word module. Delete them after the firmware works.
The `;` browser leader key is a separate ccstone multi-press template and is unrelated
to Portuguese. Keep or disable it freely.

---

## 10. Deliverables and rendering

1. ~~`f.qwerty/keymap.c`, built to this specification.~~ Done, compiles clean.
   Not yet flashed or typed on.
2. The layer-cheatsheet overlay (section 8). Still open.

`keymap.c` is now the truth. Generate the pretty renders from the firmware:

```bash
qmk c2json keymap.c > keymap.json
```

Then use [keymap-drawer](https://caksoylar.github.io/keymap-drawer) to produce an SVG.
It handles the Voyager physical layout, hold-tap keys and combos. Use the SVG in the
README and as the base for the overlay.
