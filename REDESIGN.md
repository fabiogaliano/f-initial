# f.qwerty — Keymap Redesign Plan

Living design doc. We build this bit by bit; each locked decision gets recorded here.
Status legend: 🔒 locked · 🤔 discussing · ⬜ not yet raised

## STATUS (handoff summary)
- 🔒 **Locked:** D1 home-row mods · D2 thumbs + layer set · D3 pointing/mouse strategy · D4 Nav · D5 Numbers · D6 Accents · D7 Symbols · **D8 Base + Media** · **D9 Mouse/Orbital** · **D10 consistency pass** (Wispr→`F13`; stale refs cleaned)
- ✅ **All 7 layers are designed.** Base · Nav · Numbers · Symbols · Accents · Media · Mouse.
- ✅ **D10 audit COMPLETE** — all 6 gaps resolved. ✅ **D12 modules FINAL.**
- ▶️ **NEXT: write `keymap.c`.** The spec is complete: 7 layers, all keys assigned, modules chosen, RGB defined.
- 🎨 **D11 RGB locked:** base lavender `191,70,231` · other layers light **only live keys** (the cheatsheet-in-hardware — DIY, ~50–100 lines) · PaletteFx adopted for looks · lighting controls on the Media layer.
- 🧩 **Modules so far:** IN — Chordal Hold, Permissive Hold, Select Word, Orbital Mouse, **Autocorrect** (core; safe for PT — it's an opt-in typo whitelist, not a spellchecker), **PaletteFx**. PARKED — Repeat Key (no good key). STILL TO DECIDE — Sentence Case, Custom Shift Keys.
- 📋 **Deferred to future sessions:** app-shortcut audit (Wispr/browser/Herd/etc.) · custom layer overlay build · Accent-layer extras (« » º ª – — " ") + optional Ç-extension · Symbols code-combo keys (`=>`/`->`/`${}`) if wanted later
- ▶️ **Resume at:** **write `keymap.c`.** Design phase is done — D1–D12 all locked. Nothing written to `keymap.c` yet; this doc is the complete spec. Build commands are in `f.qwerty/CLAUDE.md`. Expect to revise by feel after the first flash (several decisions are explicitly marked "revise after flashing").
- 🛠 **Layer rendering standard:** ASCII Voyager template in "Layer maps & rendering" §; final SVGs via [keymap-drawer](https://caksoylar.github.io/keymap-drawer) from `keymap.c` (`qmk c2json`).

## Goals (from user)
- Actually use layers (today: barely used).
- Stop reaching to the top number row (bad for vim counts/motions).
- Fix awkward Shift placement (currently outer-pinky, keeps getting reached for).
- Type Portuguese accents comfortably while working in English.
- Optimize without a scary rewrite — keep QWERTY, no full alt-layout switch (for now).
- Add some Getreuer "plugins" (select word, orbital mouse, sentence case, palettefx).

## Hard constraints
- ZSA Voyager: 52 keys, **4 thumb keys total (2 per hand)** — thumbs are scarce.
- macOS primary. Builds from source (QMK), so community modules are on the table.
- Heavy vim user.
- Writes English + Portuguese.

## Design philosophy (user doesn't use layers today — memorability is the #1 goal)
- User currently uses **almost no layers** (occasionally Symbols for `~ /`, and hold-Enter nav). Root problem is *remembering*, not the layout.
- So: **few layers, mnemonic placement, maximum consistency.** Prefer semantic/common-letter mappings (e.g. Z/X/C/V = undo/cut/copy/paste, W = select Word, F = Find) so a key's meaning is guessable.
- I (assistant) drive the design toward best practices; user reacts. Almost everything is up for change.
- Back it with a visual memory aid (see Deliverable 2).

## Deliverables
1. **Rebuilt keymap** (`f.qwerty/keymap.c`) per decisions below.
2. **Floating layer-cheatsheet overlay** (after keymap): always-on-top, translucent macOS overlay showing the keyboard; highlights/swaps to the active layer live so the user can *see* what each hold does. Interim solution available today: **ZSA Keymapp** already shows the active layer live — use it while learning. Custom overlay is a follow-up build project.

## Ergonomics driver (shapes every decision)
- User has **chronic light inflammation in the RIGHT wrist**. Willing to retrain for ergonomic gain.
- Bias all decisions toward **offloading the right hand/wrist**:
  - Split heavy keys off the right thumb; favor the left where balanced.
  - Keep reaches **off the top row**; favor home position.
  - Minimize right-**pinky** stretches when designing Nav/Num/Sym.
  - Get **mousing off the right hand** where possible (keyboard mouse / left-hand pointer).
- Note: this makes a hand-balanced alt layout (e.g. Colemak-DH) more justified than before — parked, revisit after foundation if wrist persists.

## Layer maps & rendering (standard format)
Every layer is documented in this ASCII **Voyager template** — physical map: outer pinky columns · number row · 3 alpha rows · 2 thumbs per hand. `—` = transparent (falls through to Base) · `·` = undecided slot.

**Reference key names** (physical positions — this is the *stock* Voyager layout, used only for naming slots like "the `T` key" or "outer row 2"):
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

**THE ACTUAL BASE LAYER (current truth):**
```
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│WSP│SH1│SH2│SH3│   │   │         │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│HYP│ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │ \ │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│MOU│ A │ S │ D │ F │ G │         │ H │ J │ K │ L │ ; │ ' │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ESC│ Z │ X │ C │ V │ B │         │ N │ M │ , │ . │ / │   │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │SPC│TAB│               │BSP│ENT│
              └───┴───┘               └───┴───┘
   hold: Nav ─┘   └─ Num        Sym ─┘   └─ Accents
              └── both = Media ──┘
```
Home-row mods (D1): `A`=Cmd `S`=Opt `D`=Ctrl `F`=Shift · `J`=Ctrl `K`=Opt `L`=Shift · `H` plain.
`WSP`=Wispr(F13) · `SH1/2/3`=Shottr Hyper+1/2/3 · `HYP`=Hyper · `MOU`=Mouse toggle. Blanks are **reserved**, not unfinished.
**Pretty renders / final artifact:** [keymap-drawer](https://github.com/caksoylar/keymap-drawer) (parses QMK json → SVG; handles Voyager physical layout, hold-taps, combos; [web app](https://caksoylar.github.io/keymap-drawer) + CLI). Workflow once `keymap.c` exists: `qmk c2json keymap.c > keymap.json` → keymap-drawer → SVG for doc/README + base for the floating overlay. Single source of truth = `keymap.c`; ASCII here is truth until then.

## Decisions

### 🔒 Decision 1 — Home row mods + Shift/Caps + freed pinky
User rests **index-on-H** (vim style; has an arrows layer on H J K L), so mods go on the keys actually rested on, and H stays plain.

- **Left home row:** `A`=Cmd ⌘ · `S`=Option ⌥ · `D`=Ctrl · `F`=**Shift**
- **Right home row:** `H`=plain · `J`=Ctrl · `K`=Option ⌥ · `L`=**Shift**
  - **Comfort-driven (user feedback):** holding middle/ring (`D`,`S`) feels weird; pinky comfortable, index fine. So **Shift** (longest-held mod) → comfortable fingers: left **index `F`**, right **pinky `L`**. Rarely-sustained **Opt/Ctrl** → the "weird" ring/middle.
  - **Cmd stays on left pinky `A`** (keep the habit user likes); Cmd only on the left.
  - `H` stays plain: most-common letter on that hand + vim/arrow key.
  - Shift is asymmetric (L-index `F` / R-pinky `L`) but both capitalize opposite-hand letters on comfortable fingers.
- **Remove** old outer-pinky Left Shift → freed for Wispr (below).
- **Keep** the top outer-left **Hyper key** (`KC_HYPR`) — used for Shottr (Hyper+1/2/3).
- ~~**Caps Word:** tap both Shifts together (`F`+`L`).~~ **SUPERSEDED by 8h — Caps Word dropped entirely.**
- ~~**Freed outer-pinky key (old Shift spot):** Wispr Flow push-to-talk.~~ **SUPERSEDED by 8d (moved to outer row 0) and 8j (trigger changed to `F13`).**
- **Anti-misfire:** enable Chordal Hold + Permissive Hold; tapping term ~200ms (tune on hardware).
- Old dead config to clean up: `get_tapping_term()` special-cases `KC_J`/`KC_K` from a previous setup.

### 🔒 Decision 2 — Thumbs + slimmed layer set (Option B, wrist-driven)
Thumb **taps** rebalanced to offload the right thumb; **holds** open layers:

| Hand | Tap | Hold → |
|---|---|---|
| Left | `Space` | Nav |
| Left | `Tab` | Numbers |
| Right | `Backspace` | Symbols |
| Right | `Enter` | **Accents (PT)** — resolved by D6 |

- ✅ **Pending revision RESOLVED:** Enter-hold went to Accents (D6). Fn/Media did *not* become a right-thumb combo — it became **both LEFT thumbs** (8g), and Mouse got its own dedicated key instead (8d).
- `Space` → left thumb: offloads inflamed right side; pairs most-used thumb with most-used layer (Nav).
- Left thumbs hold right-hand-content layers (Nav, Numbers) so opposite hands cooperate.
- ~~Active layers cut 12 → 5.~~ **Final count is 12 → 7:** `0` Base · `1` Nav (hold L-Space) · `2` Numbers (hold L-Tab) · `3` Symbols (hold R-Bspc) · `4` Accents (hold R-Enter) · `5` Media (hold both L thumbs) · `6` Mouse (toggle `MOU`).
- Portuguese: macOS dead keys for now (no layer).
- **Archive** League (old 9/10/11) + layer-switcher (old 7) → `f.qwerty/archive/league.md` (restorable).
- Old per-key tapping-term hacks for `KC_J`/`KC_K` to be cleaned up.
- **Mouse: still open** — leaning keep + upgrade to Orbital Mouse specifically to get mousing off the right wrist.

### 🔒 Decision 3 — Pointing / mouse strategy (wrist-driven)
Goal: cut right-hand mousing hard.
- **Keyboard mouse:** replace clunky hold-`Esc`+`ASDW` with **Orbital Mouse** (Getreuer module) on its own small Mouse layer. ~~Access via both-left-thumbs tri-layer or a Nav-layer key.~~ **SUPERSEDED by 8d/D9 — access is a dedicated `MOU` toggle key** on the left outer column, row 2.
- **Select Word** (Getreuer module) → **Nav layer**. Replaces the KM "Select a word" (Hyper+W: `Opt→, ⇧Opt←, Opt→, ⇧Opt←`) and "Select a line" (`Cmd←, Cmd⇧→`) macros. One keycode, all apps, tap-to-extend.
- **clavier.app** (keyboard clicking, Homerow/Shortcat-style) stays — pairs with the above.
- **SlimBlade Pro:** it's a *stationary* trackball → placement problem. Move it **between the spread keyboard halves** or adjacent; strongly consider **left-hand** operation to spare the right wrist.

### KM cleanup notes (from reading Macros.plist)
- `;` "hack" = ccstone Multi-Press Template making `;` a **browser leader key** (single/double/triple press) + a `Cmd+Shift+;` macro to enable/disable that group. NOT Portuguese-related. Keep or disable freely.
- KM "Select a word / line" macros → **superseded** by firmware Select Word (delete after firmware works).
- Other minor hacks seen: `Opt+W`→`@`, Hyper+G=Search, Hyper+Y=KM trigger palette.

### 🔒 Decision 4 — Nav layer (hold left `Space`)
Principle: **right hand = MOVE, left hand = EDIT** (edit keys on the real Cmd-shortcut positions). Left home-row mods stay live → `Shift/Opt/Cmd + arrow` give select / word-jump / line-jump **for free** (no dedicated keys).

Right hand (3 spatial tiers):
- home `H J K L` = `← ↓ ↑ →`
- bottom `N M , .` = `Home · PgDn · PgUp · End` (extremes, matched under each arrow)
- top `Y U I O` = `prev-tab · next-tab · back · forward` (GUI app nav = mouse reduction)

Left hand (edit, mnemonic):
- top `Q W E R` = `Esc · Select Word · Select Line · Redo`; `G` = Find
- home `A S D F` = normal modifiers (for mod+arrow combos)
- bottom `Z X C V B` = `Undo · Cut · Copy · Paste · Select-All`

`W` Select Word = firmware Select Word module (replaces KM Hyper+W). Note: Keymapp is flaky for this user (code, not Oryx) → strengthens case for custom overlay.

### 🔒 Decision 5 — Numbers layer (hold left `Tab`)
Calculator numpad under the **right hand** (fixes top-row reach + vim counts). Aligned to index-on-`H` rest.

Right hand:
- top `Y U I` = `7 8 9`, `O` = `=`
- home `H J K` = `4 5 6`, `L` = `Enter`
- bottom `N M ,` = `1 2 3`, `.` = `.` (decimal)
- **🔒 `0` = the right OUTER thumb (the `Enter` key's position)** — updated, resolves D10 gap #4. (The old note said "right thumb, `Space` position," which went stale when D2 moved `Space` to the left thumb.) Chosen over the inner thumb because: Enter is already on this layer at `L` (calculator position), so the thumb copy is redundant — and this **keeps `Backspace` live on the inner right thumb**, which matters most exactly when typing digits. Also reads like a real numpad: `0` is the big key under the digits.
- **🔒 Two `=` keys on this layer is intentional**, not a slip (resolves D10 gap #3). `T` (with the operators) and `O` (calculator position). The left key would otherwise be empty, so the duplicate is free, and it lets you type `4+5=` without the hands crossing.
- **🔒 Nothing else added.** Layer covers digits, all math operators, Enter, decimal, and live modifiers (so `Cmd+1…9` still works). Considered and rejected: hex letters, parens, thousands separator — all would add memory load for rare gains.

Left hand:
- top `Q W E R T` = `+ − * / =` (math operators)
- home `A S D F` = normal modifiers → **`Cmd+1…9`** for tab/desktop switching (bonus)

Depends on: base top row must **stop emitting digits** (remove the fallback) — handled in the Base-layer decision.

### 🔒 Decision 6 — Portuguese Accent layer (core locked; variant layout + output method still open)
Studied romak's "Alpha 2" sticky layer + Ç-extension (`layout-research/romak/`) and ran web research on macOS accent input. Two things locked:

- **Placement = mnemonic-literal.** Each accent sits on its own QWERTY letter key so there is nothing to memorize: `á`→A, `é`→E, `í`→I, `ó`→O, `ú`→U, `ç`→C. Diacritic **variants** (`à â ã · ê · ô õ`) go on **nearby** keys (positions TBD — next task).
  - Accepted tension: this puts `é í ó ú` on the **top row** (QWERTY vowels aren't home-row). OK here because the layer is held/occasional, not hammered like the number row. Only `á` (A) and `ç` (C) are non-top.
- **Trigger = HOLD the right thumb (the Enter thumb).** `LT(ACCENT, KC_ENT)`: tap = Enter (unchanged), hold = accent layer momentarily. Mental model: "**Shift, but for accents**" — hold, tap the vowel, release. `café` = `c a f` + hold-thumb-`e`.
  - **Why hold, not one-shot** (reversed a brief interim lean): (1) a true tap-once one-shot needs its *own* dedicated tap, which can't share the Enter thumb without losing Enter; (2) the wrist cost of holding is low because the **highest-frequency accents (á é ç ã) are all LEFT-hand**, typed opposite the right thumb-hold — only the rarer `í ó ú` are same-hand. A one-shot key can be added later on a spare key if wanted.
- **Consequence:** Fn/Media loses the Enter hold. ~~Demotes to a two-*right*-thumb combo.~~ **SUPERSEDED by 8g — it became both LEFT thumbs**, keeping the trigger off the inflamed hand.

**🔒 Full vowel map (locked; user will revise by feel after flashing).** Reduces to **3 rules by accent shape** + one A-corner exception:
```
   Q  W  E  R  T        Y  U  I  O  P
   â  ·  é  ·  ·        ·  ú  í  ó  ·

   A  S  D  F  G        H  J  K  L  ;
   á  ã  ê  ·  ·        ·  ·  ô  õ  ·

   Z  X  C  V  B        N  M  ,  .  /
   à  ·  ç  ·  ·        ·  ·  ·  ·  ·
```
- **Rule 1 — Acute ´ = on the vowel itself:** `á é í ó ú` on A E I O U. Nothing to learn.
- **Rule 2 — Circumflex ^ = middle-finger home key:** `ê`→D, `ô`→K (mirror pair).
- **Rule 3 — Tilde ~ = ring-finger home key:** `ã`→S, `õ`→L (mirror pair).
- **`ç`→C** (its own letter).
- **A-corner exception:** grave `à`→Z (below A) and circumflex `â`→Q (above A). A lives on the weak pinky with no middle-home key of its own, so its two extras tuck around A instead of joining the mirror. `à` gets the easier down-key (more frequent than `â`); `â`'s `^` "points up" → Q.
- Wrist bonus: the two right-hand variants (`ô õ`) sit on the **home row** (K/L) — no top-row stretch on the inflamed hand.

**🔒 Output method = macOS dead keys (default layout), NOT Unicode.** Firmware fires the built-in Mac accent combos per tap — `á`=⌥e·a, `à`=⌥\`·a, `â`=⌥i·a, `ã`=⌥n·a, `é`=⌥e·e, `ê`=⌥i·e, `í`=⌥e·i, `ó`=⌥e·o, `ô`=⌥i·o, `õ`=⌥n·o, `ú`=⌥e·u, `ç`=⌥c. Chosen over Unicode because:
- **Zero macOS config** — works on the default keyboard; no "Unicode Hex Input" source to enable.
- **Breaks nothing** — Unicode Hex Input hijacks Option and would kill **Nav-layer ⌥+arrow word-jumps (D4)**. Dead keys only flash Option for a split-second per accent. (The old "would also kill Wispr ⌥." argument is now moot — Wispr moved to `F13`, see 8j — but the Nav argument alone still holds.)
- **Capitals free** — hold Shift + accent key → `Á É` (OS composes).
- **Accepted tradeoff:** two-step dead keys don't fire in **Terminal** — fine, user writes PT in apps (already noted). `ç` (direct ⌥c) works even in Terminal.
- Implementation: each accent key = a small macro (e.g. `SS_LOPT("e") "a"`). Same mechanism will host the extras below.

**Remaining (minor, revisit anytime — NOT blocking):**
- **Extras:** `« »`, `€`, `º ª`, `– —`, `" "` (all also ⌥-combos) — add to this layer later if wanted.
- **Optional advanced:** romak Ç-extension (`ç`→one-shot giving `ã`/`õ` + `-ão`/`-ões` word macros). Bespoke/high-investment — revisit only if wanted.

### 🔒 Decision 7 — Symbols layer (locked; revise by feel after flashing)
Symbols = **hold right Backspace**. Researched real layouts (Getreuer, Callum, Miryoku, Seniply, Sunaku, justinmklam) — chose **mirrored brackets** (Callum-style: most *memorable*, one rule for all pairs) over clustered/roll-optimized (faster but more to learn). Volume biased to the **left hand** (right thumb holds the layer + right wrist is the sore one).

```
SYMBOLS · hold BSP        (— = transparent → Base)

┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│ — │ — │ — │ — │ — │ — │         │ — │ — │ — │ — │ — │ — │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ — │ ? │ ! │ & │ - │ + │         │ ` │ : │ — │ — │ — │ — │  ← operators
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ — │ < │ [ │ { │ ( │ = │         │ | │ ) │ } │ ] │ > │ — │  ← CONTAINERS (mirror)
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│ — │ — │ @ │ # │ $ │ € │         │ ~ │ ^ │ % │ * │ — │ — │  ← meta/€ (L) · rares (R)
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
                                        (, . / stay = Base)
```
**Four shelves (the whole layer):**
1. **Home = containers, fully symmetric:** `< [ { ( = │ | ) } ] >`. Brackets **nest** and mirror to the same finger per pair — `(`↔`)` index, `{`↔`}` middle, `[`↔`]` ring; `< >` on the outer pinkies **pointing outward**; `=`/`|` anchor the center (inner index).
2. **Operators (top):** `? ! &` + math `- +`; `` ` `` (template literal) and `:` on the right.
3. **Meta/currency (bottom-left):** `@ # $ €` on strong fingers (Swift/JS + PT).
4. **Rares (bottom-right):** `~ ^ % *` grouped in one fixed, findable home (user's call — "I know the tilde lives bottom-right"). Rare → negligible right-hand load.

- **Base pass-through:** `, . / ' ;` and quotes `" '` stay on Base (no slot needed here). Number row stays clean.
- **Deliberately sparse right hand** = fewer things to remember (user's #1 goal) + rests the inflamed wrist. Rejected: number-order `!@#$%^&*` top row (would burn prime keys on rare symbols — Getreuer's frequency data) and code-combo keys (`=>`/`->`/`${}` — user chose clean; can add later).
- Output: shifted-number symbols have **no Base home** once digits move to a layer, so this layer is their only home. `€` = ⌥⇧2 macro (like the accents).

### 🔒 Decision 8 — Base layer + Media layer (COMPLETE)

**🔒 8a — Freed top row (partial lock).** Digits are gone (they live on Numbers, D5). Researched what others do with a freed top row (Getreuer, Miryoku-derived, Seniply, Moonlander/Voyager builds): the practiced convention is *not* to blank it but to banish the least-valuable keys there, most commonly F1–F12. **Rejected for this user — barely uses F-keys**, so filling the row with them wastes it tidily instead of usefully.

Locked instead:
```
BASE · top row
┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│   │SH1│SH2│SH3│   │   │         │   │   │   │   │   │   │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
     full area OCR                  reserved: special shortcuts
```
- **Shottr captures on the physical `1` `2` `3` keys** — firmware fires `Hyper+1/2/3` internally. Zero new memory: the number already in muscle memory *is* the key. **Supersedes** the earlier `F`/`A`/`O`/`S` mnemonic plan (that was a second naming system on top of one the user already knows). `Hyper+5` (scrolling capture) not mapped for now.
- **Remaining 9 slots deliberately empty**, reserved for future "special shortcuts" — to be filled from the app-shortcut audit, not invented now.
- **🔒 8b — `-` and `=` REMOVED from Base** (resolves the doc's "fate of `=`" open item, and takes `-` with it). Both already have a home on Symbols: `-`→`R`, `=`→`T`. Rationale: one key, one home — duplicates are what make a layout unmemorable.
  - ⚠️ **Watch after flashing:** `-` is high-frequency (PT/EN hyphenation, kebab-case, `--flags`) and now costs a **right-thumb hold** (Symbols) on the inflamed hand. Key itself is left-index, so the hold is light — but re-evaluate with real typing.
- **Consequence:** F1–F12 need a home → **resolved by 8i: not mapped at all** (user declined).
- **Consequence:** with F-keys and Shottr off it, the Fn/Media layer's remaining job is media only → **resolved by 8g: kept as a Media layer**, retriggered from both left thumbs.

**🔒 8c — "Back to Base" key: NOT needed, dropped.** Research (QMK docs + community practice) is clear that with every layer momentary/thumb-held, *releasing the thumb is the return to Base* — that's what `MO`/`LT` do. A dedicated `TO(0)` is an anti-pattern in a held-layer design; it only earns its keep as an escape from a **locked** layer, and tapping Layer Lock again already unlocks. One key, not two. Resolves the doc's "consistent back-to-Base key" open item.

**🔒 8d — LEFT outer column (the 4 left-pinky keys).**
```
row 0   WISPR   ← hold-to-talk (Wispr Flow push-to-talk)
row 1   HYPER   ← unchanged (Shottr + global hotkey namespace)
row 2   MOUSE   ← toggle Mouse layer on/off
row 3   ESC     ← unchanged (user kept the habit)
```
- **Esc stays put (user's call).** Overrode the research convention (vim users usually move Esc off the bottom-outer to the Caps position) because the habit is already in the fingers and habit is worth a lot when memorability is the goal. It also *improves* without moving: it loses its old second job (`LT(5, KC_ESCAPE)` — hold opened a layer), so it becomes a plain, misfire-proof Esc.
- **Wispr → row 0.** Fine on a far key because it's a *hold*: reach once, park the finger, talk, release. The reach doesn't repeat. (Was going to be row 2 per D1 — moved.)
- **Row 2 = the best key in the column** (pinky slides straight sideways, no up/down stretch), so it got the highest-value job: **Mouse layer toggle.**
  - **Why:** D3's entire purpose is getting the right hand off the trackball, and a dedicated key makes the most valuable feature the easiest to reach. Row 2 was free and needed a job; Mouse was the highest-value candidate for it.
  - (Its old access was "hold both left thumbs." That chord is now the **Media** trigger — see 8g. Note the doc briefly justified this swap by claiming chords are bad for this user; that was the assistant's inference, not the user's position, and is retracted.)
  - **Toggle, not hold** (`TG(MOUSE)`): mousing lasts seconds-to-minutes; holding a pinky that long is its own strain.
  - Mouse keys sit under the **left** fingers → the whole pointing operation happens on the good side, right wrist never involved.
  - **Supersedes** D3's "hold both left thumbs tri-layer" access and frees that chord.
- Rejected for row 2: a second Shift (that's the placement D1 is escaping) and Layer Lock (wrong hand — see 8e).

**🔒 8e — Layer Lock: DROPPED for v1.** Considered and rejected, not forgotten.
- Layer Lock solves the pain of holding a thumb down for a long time — but **this design already avoids that pain**: every layer is held by the hand *opposite* its content (left thumb holds Nav/Numbers, right hand does the typing). The holding thumb isn't fighting the typing hand, it's just resting. That's the situation where people reach for Layer Lock, and it doesn't apply here.
- User also reports never having used layer-lock on the old 12-layer map. Adding it = one more thing to forget, which is the exact failure mode this redesign exists to fix.
- **Revisit trigger:** if after flashing the user thinks "I've been holding Tab forever" during long digit runs. One-line change to add.
- If it ever is added: it must go on the **right hand** (left thumb is busy holding the layer; right hand is idle), using the Getreuer/QMK pattern of `QK_LAYER_LOCK` on Base + `KC_TRNS` on every other layer so one fixed spot locks whichever layer is active. Note research shows real keymaps put it on a **thumb** — unavailable here, all 4 thumbs are spoken for.

**🔒 8f — RIGHT outer column (the 4 right-pinky keys).**
```
row 0   (empty)   ← reserved (was `=`; top row = the row we're escaping)
row 1   \         ← unchanged (rare, already habitual, nothing better competing)
row 2   '         ← unchanged (frequent in EN contractions; sits in the easy sideways slot)
row 3   (empty)   ← reserved (old dead TD key)
```
- **Principle correction recorded:** "offload the right hand" does **not** mean emptying this column. A key you rarely press costs the wrist nothing — strain comes from keys you *hit*. So the rule is only: nothing *frequent* lands here. `\` and `'` both stay.
- Both free slots stay **empty and reserved** for the app-shortcut audit, same treatment as the base top row. Deliberately not filled with invented content.

**Freed-key inventory update:** old bottom-right `TD(DANCE_0)` is **fully dead** — it was single-tap `Option+E` (acute dead key), double-tap → layer 7. Accents are superseded by D6; layer 7 was archived by D2. Slot is free.

**🔒 8g — Media layer KEPT (layer count stays 5), triggered by a dedicated key.**
Rejected putting media on the Nav top row ("too much on top"). User asked for a dedicated media layer preserving the media keys they already know, rest blank.
```
MEDIA · hold base top-row `5` position          (blank = KC_NO, does nothing)

┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │         │   │   │   │   │   │   │  ← free: future launcher row
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │         │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │         │ ⏮ │ ⏯ │ ⏭ │ ■ │   │   │  ← H J K L
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│   │   │   │   │   │   │         │ 🔉│ 🔇│ 🔊│   │   │   │  ← N M ,
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
```
- **Improved on the old positions (user's idea).** Old layer 7 had transport on `I O P \` (top alpha row) and volume on `N M ,`. User moved transport to sit **directly above** the volume keys → transport lands on the **home row** `H J K`, minimal travel on the inflamed hand. One idea per finger, stacked: **index** prev/vol-down · **middle** play-pause/mute · **ring** next/vol-up · **pinky** stop (least used, off to the side).
- `■` stop is near-useless on macOS (most apps treat it as play/pause) — kept because the user asked; first thing to drop if the key is ever wanted back.
- **🔒 Trigger = hold BOTH LEFT THUMBS** (`Space` + `Tab` together).
  - An interim proposal put it on a dedicated base top-row key (above `T`); **user rejected the position**, and the left hand has no other free comfortable key (outer column full: Wispr/Hyper/Mouse/Esc · alphas are letters · both thumbs already assigned).
  - On the merits the chord is the better key anyway: **zero reach**, thumbs are the strongest fingers, both are already resting there, and it's still **opposite-hand** from the right-hand media keys.
  - Reads logically: `Space` alone = Nav · `Tab` alone = Numbers · **both = the third thing**. Standard ergo-keyboard tri-layer pattern, and it costs **no key** — the two free top-row slots stay reserved.
  - ⚠️ **Correction to an earlier draft of this doc:** it claimed the chord was rejected because "the user forgets chords / a key you can point at beats a gesture." **The user never said that** — it was the assistant's inference from "I can't remember layers" and the user corrected it. Do not treat "chords are bad for this user" as an established constraint.
- **Consequence:** the old D2/D6 "Fn/Media = hold both right thumbs" chord is **dead** — replaced by both-*left*-thumbs, which also moves the trigger off the inflamed hand.

**📚 Reference — what a key can actually do** (asked by user; governs how the reserved slots get filled later)
A USB keyboard can **only send keystrokes** — it cannot run a script, call an API, or invoke a skill. Everything else is a chain: *keyboard sends a keystroke nobody else uses → a Mac-side app hears it → that app does the real work.* (This is exactly why the Hyper namespace exists: Ctrl+Alt+Shift+Cmd collides with nothing.) Three levels:
1. **Send an existing shortcut** — zero setup if the app has one (e.g. Shottr `Hyper+1`); otherwise assign it in the app first, then point a key at it.
2. **Type text (QMK macro)** — zero setup, no Mac app involved. A key can type an entire prompt preamble straight into Claude Code. Limits: goes to whatever is focused; long strings eat firmware space.
3. **Trigger a script/skill** — needs one Mac-side listener (**Raycast** — user already has it — or Keyboard Maestro / Hammerspoon). **Pro trick: send `F13`–`F20`.** No physical Mac keyboard has those keys, so they can never collide; Raycast catches them and runs anything.
- **Planned use:** the Media layer's empty top row becomes a **launcher row** (F13, F14, F15… → Raycast scripts). Details deferred to the app-shortcut audit.

**🔒 8h — Caps Word: DROPPED.** D1 planned it on a tap-both-Shifts (`F`+`L`) combo with no dedicated key. User rarely writes SCREAMING_CASE constants, so it would never fire. **Supersedes D1's Caps Word line.** Also removes it from the "modules In" list. Trivial to add back later (combo + `CAPS_WORD_ENABLE`) if constant-heavy code shows up.

**🔒 8i — F1–F12: NOT MAPPED.** Proposed on the Numbers layer's empty top row (straight F1–F12 left-to-right, laptop-style, zero to memorize, zero cost since the row is empty). **User declined for now** — barely uses them, doesn't want the row filled. Numbers-layer top row stays empty and reserved. One-line change to add if an app ever demands one.

**✅ D8 COMPLETE.** Base layer + Media layer fully specified.

**⚠️ Flagged for the D7 final pass (user's catch):** `?` would have **two homes** — Shift+`/` on Base *and* `Q` on the Symbols layer. Same duplication argument that killed `-`/`=` from the top row. Audit Symbols for other shifted-character duplicates (`!` = Shift+`1`… but digits are gone, so check case by case).

### 🔒 Decision 9 — Mouse layer (Orbital Mouse)

Implements D3's wrist goal literally: **the right half of this layer is entirely blank.** The right hand does not participate in pointing at all.

**Access:** toggle on/off with the `MOU` key (left outer column, row 2 — see 8d). Not a hold: mousing lasts seconds-to-minutes.

**The model (Orbital Mouse, Getreuer).** Not classic mouse keys. The pointer works like **driving a car** — it always has a heading. `FWD`/`BCK` drive along the heading; the left/right keys **steer** (rotate the heading) rather than moving the pointer sideways. Benefit: travel at *any* angle with one key held, instead of 8 fixed directions needing two keys. Confirmed as the user's choice (D3 already locked it).

```
MOUSE · toggled on/off with MOU              (blank = KC_NO, does nothing)

┌───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┐
│   │   │   │   │   │   │         │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│   │ ⇑ │FWD│ ⇓ │   │   │         │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│OFF│ ↰ │BCK│ ↱ │   │   │         │   │   │   │   │   │   │
├───┼───┼───┼───┼───┼───┤         ├───┼───┼───┼───┼───┼───┤
│SLO│   │   │   │   │   │         │   │   │   │   │   │   │
└───┴───┴───┴───┴───┴───┘         └───┴───┴───┴───┴───┴───┘
              ┌───┬───┐               ┌───┬───┐
              │L-C│R-C│               │   │   │
              └───┴───┘               └───┴───┘
```
| Key | Keycode | Job |
|---|---|---|
| `W` / `S` | `OM_U` / `OM_D` | drive forward / reverse |
| `A` / `D` | `OM_L` / `OM_R` | steer left / steer right (rotate heading) |
| `Q` / `E` | `OM_W_U` / `OM_W_D` | scroll up / scroll down |
| outer row 3 (`Esc` position) | `OM_SLOW` | **hold** for slow, precise movement + turning |
| outer row 2 | `TG(MOUSE)` | `OFF` — same key that turned it on |
| left thumb 1 (`Space`) | `OM_BTN1` | left click |
| left thumb 2 (`Tab`) | `OM_BTN2` | right click |

**Why this shape (design history — two corrections the user made):**
1. Assistant first proposed **ESDF** (WASD shifted one finger right) to keep the pinky out and put the index on the `F` home bump. **User preferred literal WASD** — it's already in their hands from the old keymap and from gaming. Existing muscle memory beats ergonomic tidying; memorability is goal #1.
2. Assistant put `SLOW` on `Q` and scroll on the index column. **User moved scroll to `Q`/`E`** (the classic "extra buttons" flanking WASD) **and `SLOW` to the `Esc` position** — because with a **gaming grip** (ring on `A`, middle on `W`/`S`, index on `D`) the **pinky floats free over the outer column**. This reveals the finger assignment the assistant had wrong; the layout now matches how the hand actually sits.
- Scroll direction assigned by **frequency, not geometry**: scroll-down is far more common (reading), so it gets `E` (stronger finger) and scroll-up gets `Q`.
- `OFF` and `SLO` end up stacked in the outer column → the pinky owns both "slow down" and "get out," the two things wanted when the pointer misbehaves.
- No same-finger conflicts under the gaming grip: `SLOW` (pinky, outer) can be held while ring/middle/index drive and steer.

**Deliberately NOT in v1:** drag (`OM_HLDS`/`OM_RELS`), double-click (`OM_DBLS`), middle click, button-selection keys (`OM_SEL*`), horizontal scroll. All rare, all would double the layer's size, and the trackball still exists for edge cases. Trivial to add once the basics are habitual.

**Implementation notes (from `layout-research/getreuer-qmk-keymap/features/orbital_mouse.h`):**
- `SRC += features/orbital_mouse.c` and `MOUSE_ENABLE = yes` in `rules.mk`.
- Call `process_orbital_mouse()` from `process_record_user()` and `orbital_mouse_task()` from `housekeeping_task_user()`.
- Orbital repurposes the stock Mouse Keys keycodes (`MS_UP`, `MS_BTN1`, …) — so `OM_U` *is* `MS_UP`, just with orbital semantics. Also repurposes `UC(0x41)`–`UC(0x4a)` for its own keycodes.
- Full docs: <https://getreuer.info/posts/keyboards/orbital-mouse>

### 🔒 Decision 10 — Consistency pass (pre-build audit)

**🔒 10a / "8j" — Wispr push-to-talk trigger = `F13`, not `Option+.`**
User will reconfigure Wispr Flow to listen on `F13` and free up `Option+.` for other use. Firmware sends a plain `F13` **held** for the duration of the key press (`register_code`/`unregister_code`, not `tap_code` — see the implementation note below). Why `F13`: no physical Mac keyboard has it, so it can never collide with an app shortcut or with the Option-based dead-key accent macros (D6). Placement unchanged — left outer column, row 0 (8d).
- ⚠️ **Implementation gotcha (from research):** a hold-to-talk key must `register_code()` on press and `unregister_code()` on release. Forgetting the release leaves the key stuck down. Also verify it doesn't collide with the home-row-mod / Chordal Hold chording window.

**Stale references cleaned up in this pass:** D1 Caps Word + Wispr lines · D2 thumb table + "12→5" layer count · D3 mouse access method · D6 Fn-demotion line + the Wispr rationale for rejecting Unicode · 8a's two "not yet locked" consequences · the Working Skeleton block · the Open-questions parking lot (resolved items folded in, incl. the dead `F`/`A`/`O`/`S` Shottr plan).

**🔴 REAL GAPS FOUND — need decisions before `keymap.c` (not yet resolved):**

1. **`_` (underscore) has NO home anywhere.** The Symbols layer (D7) replaces the entire home row with containers, so **there is no Shift key on the Symbols layer** — meaning `Shift`+`-` is impossible there, and `-` only exists there. Underscore is common in JS/TS and file names. **Needs a slot on Symbols.**
2. **Duplicate homes** — the same "one key, one home" rule that killed `-`/`=` from the Base top row (8b) is violated by several Symbols keys, because Base still supplies their unshifted partner:
   - `?` = Shift+`/` on Base **and** `Q` on Symbols *(user spotted this one)*
   - `:` = Shift+`;` on Base **and** the right-hand `:` on Symbols
   - `<` `>` = Shift+`,` / Shift+`.` on Base **and** the outer pinkies on Symbols
   - `+` = Shift+`=` **and** its own key on Symbols (`=` is also on Symbols, so both live on the same layer)
   - `~` = Shift+`` ` `` **and** its own key on Symbols (same layer again)
   - **✅ RESOLVED — keep all of them; no change.** The `-`/`=` precedent does **not** apply. Those were *unshifted* duplicates on a bad-reach row. These are different:
     - Shift+`/`→`?`, Shift+`;`→`:`, Shift+`,`→`<` etc. are **unavoidable** — they exist for free the moment `/ ; , .` live on Base. You can't "remove" them without removing the letters.
     - The Symbols copies are **cheaper** (one key vs. Shift+key), so they earn their slot rather than duplicating it.
     - `<` `>` are **load-bearing**: they complete the mirrored container row `< [ { ( = │ | ) } ] >`, which is the entire mnemonic of D7. Removing them to save a duplicate would break the one rule that makes the layer memorable.
     - `+` and `~` **must** stay on Symbols: there is no Shift key on that layer, so `Shift`+`=` and ``Shift+` `` are impossible there. (Same root cause as the `_` gap.)
3. **✅ RESOLVED — `=` twice on Numbers is intentional.** Not a slip; the left key would otherwise be empty and the duplicate lets you type `4+5=` one-handed. See D5.
4. **✅ RESOLVED — `0` goes on the right OUTER thumb** (`Enter` position), keeping `Backspace` live on the inner thumb. See D5.
5. **🔒 RESOLVED — outer columns are `KC_NO` (dead) on Nav, Numbers, Symbols and Accents.**
   The problem: those layers left the outer columns transparent, so while holding a layer the four left-pinky keys were still **Wispr / Hyper / Mouse / Esc**. Brushing Wispr, Hyper or Esc is harmless — but **`MOU` is a toggle**, so a stray hit silently switches the board into mouse mode with no obvious cause and no auto-recovery. The Accents layer is the worst case: `à`→Z, `â`→Q and `á`→A all sit right next to that column.
   - **Dead on:** Nav · Numbers · Symbols · Accents. Nothing is lost — there is no reason to fire Wispr or toggle the mouse mid-symbol or mid-accent.
   - **Still live on:** Base (obviously) and Mouse (where the column holds `OFF` and `SLO` deliberately).
   - Also worth applying the same thinking to the **Base top row** on held layers, so Shottr can't fire mid-symbol.
6. **🔒 RESOLVED — `Esc`'s two homes are fine, keep both.** Dedicated Base key (8d) plus Nav-layer `Q` (D4). Not a duplicate in the harmful sense: the Base one is the reflex, the Nav one is free real estate on a key that would otherwise be empty. Costs nothing.

**✅ D10 COMPLETE — all six gaps resolved.**

### 🔒 Decision 11 — RGB / lighting

**🔒 11a — Base layer = the user's signature colour, unchanged.** `HSV 191, 70, 231` (soft lavender-purple) — read from the old `ledmap[0]`. All keys lit, as today.

**🔒 11b — Every other layer: only LIVE keys are lit; inactive keys are OFF (`0,0,0`).**
This is the **layer-cheatsheet-in-hardware** pattern and it's the single highest-leverage memorability feature in the whole build — the board becomes the reference card, so there's no chart or overlay to consult. Hold `Space` → only the Nav keys glow. Hold `Tab` → only the numpad glows.
- Precedent: the user's **own** old `ledmap[5]` and `ledmap[6]` already do exactly this (dead keys set to `{0,0,0}`) — the instinct is already in their keymap.
- Give each layer a distinct hue so the colour alone identifies the layer.
- ⚠️ **Research correction:** this is **NOT** something PaletteFx or any Getreuer module provides. It's a hand-rolled `rgb_matrix_indicators_user()` (or per-layer `ledmap` as the old keymap does), ~50–100 lines. Standard QMK RGB Matrix pattern; DIY but well-trodden.

**🔒 11c — PaletteFx: ADOPTED, for looks only.** User: *"looks cool af, it's not about the functional side."* Recorded explicitly so nobody later "corrects" this into a functional decision — it is an aesthetic choice, made with full knowledge that it does **not** do layer teaching (6 animated effects × 16 palettes, global, not layer-aware; Getreuer himself uses only a single binary status LED). Coexists fine with 11b.

**🔒 11d — Lighting controls live on the MEDIA layer.** User's idea. The Media layer's empty left hand / top row hosts RGB toggle, brightness, effect-cycle and palette-cycle keys. Exact placement TBD when we write `keymap.c` — the space is reserved.

**Repeat Key — PARKED (not rejected).** One key that repeats the last keypress; **Alternate Repeat** does the complementary action (Page Down → Page Up). Genuinely a right-hand-load reducer *if* placed on the left hand. **Blocked on placement:** the left hand has no free comfortable key (outer column full, alphas are letters, both thumbs assigned) and a repeat key you have to reach for won't get used. Revisit if the app-shortcut audit frees a good slot. Use QMK **core** Repeat Key, not the legacy `features/` copy; call it after Chordal Hold in `process_record_user()`.

**🔒 Underscore resolved (D10 gap #1) — assistant's call, user deferred ("idk"), trivially reversible.**
`_` takes the `E` slot on the Symbols top row (where `&` was); `&` moves to the bottom-right rare cluster alongside `~ ^ % *`. Rationale: identifiers and filenames beat `&&` in volume, and the rares cluster is exactly the "one findable home for things I rarely need" shelf D7 already established.
```
SYMBOLS · revised rows
│ — │ ? │ ! │ _ │ - │ + │      ← operators (was `&` on E)
│ — │ — │ @ │ # │ $ │ € │         │ ~ │ ^ │ % │ * │ & │ — │   ← `&` joins the rares
```

## Pending tasks (FUTURE sessions — not this one)
- **Portuguese / Accent layer — DONE, see Decision 6.** (Superseded this pending note: full vowel map + hold-Enter trigger + macOS dead-key output all locked.) Remaining optional extras (`« »`, `º ª`, `– —`, `" "`) + Ç-extension tracked under D6.
- **App-shortcut audit + consolidation.** Inventory hotkeys across all main apps, resolve conflicts, mirror the important ones into the keymap as single mnemonic keys, and record the full map here (this file = registry). Apps to cover: Shottr (done), **Wispr Flow** (dictation; currently `Option+,`/`Option+.` push-to-talk — confirm exact trigger), **browser** (Arc/Chrome/Dia?), **Herd**, Raycast/Alfred, window manager, Karabiner (if any), macOS system shortcuts, clavier.app. Strategy: Hyper namespace for global hotkeys + firmware single-key mirrors + overlay as live view.
- **Layer-cheatsheet overlay** (Deliverable 2) — build after keymap; Keymapp is flaky here (code, not Oryx).

## Working skeleton (CURRENT — 7 layers)
```
0 Base
1 Nav      = hold LEFT Space
2 Numbers  = hold LEFT Tab
3 Symbols  = hold RIGHT Backspace
4 Accents  = hold RIGHT Enter
5 Media    = hold BOTH LEFT thumbs (Space + Tab)
6 Mouse    = toggle, MOU key (left outer column, row 2) → Orbital Mouse
```

## Open questions / parking lot
**✅ Resolved (kept for history):** home-row mod order → D1 · layer set + thumb scheme → D2/D8 · number layer geometry → D5 · Nav layer → D4 · Symbol layer → D7 · Portuguese method → D6 · fate of `=`/`+` → 8b (removed from Base) · base top-row design → 8a · freed-key inventory → 8a/8d/8f · Layer Lock + back-to-Base → 8c/8e (both dropped) · Shottr placement → 8a (**supersedes** the old `F`/`A`/`O`/`S`-on-Fn-layer plan; it's now Hyper+1/2/3 on the physical `1`/`2`/`3` keys).

**Still open:**
- **App-shortcut conflicts / global control:** make the keyboard the single source of truth for app shortcuts so per-app shortcuts stop colliding. Own topic, after foundation.
- **Principle — modifier+symbol shortcuts:** combos like `Cmd+[`, `Cmd+/`, `Ctrl+[` are painful when the symbol lives on a *held* layer. Bake each frequent one as a **single-key macro** on the relevant layer (Nav already does this: back/fwd = `Cmd+[`/`]`). Collect the user's actual list.
- macOS Cmd+C/V/X/Z are same-hand chords (Cmd on left pinky `A`). Possible later tweak: Cmd on a thumb or a combo.
- Getreuer/community modules to adopt + ordering — **in progress, see the modules section**.
- **Shottr `Hyper+5`** (scrolling capture) still unmapped — 8a mapped only 1/2/3.

## 🔒 Decision 12 — Modules (FINAL)

**IN:**
| Module | Form | Note |
|---|---|---|
| Chordal Hold | QMK **core** | anti-misfire for home-row mods. Use core, **not** Getreuer's older `achordion.c` (superseded, QMK 0.28.0) |
| Permissive Hold | QMK **core** | with the above |
| Select Word | Getreuer module | Nav layer `W` (D4) |
| Orbital Mouse | Getreuer `features/` | Mouse layer (D9) |
| **Autocorrect** | QMK **core** | user wants it. `qmk generate-autocorrect-data` |
| **PaletteFx** | Getreuer module | **aesthetic only** — see 11c |
| Layer-cheatsheet RGB | **DIY** | not a module; see 11b. Highest-leverage item for memorability |

**Autocorrect × Portuguese — researched, LOW RISK.** It is an **opt-in whitelist** of `typo → correction` pairs you supply, *not* a live English spellchecker. It cannot correct a word it was never taught. It's also scoped to a–z + apostrophes, so accented PT words are simply out of scope and pass through untouched. Start from the small (~71-entry) example dictionary, not the 400-entry one, and use `:word:` boundary markers to avoid substring false-positives. Any held modifier other than Shift resets the buffer, so it won't fight vim normal mode.

**OUT (all user decisions):**
- **Caps Word** — dropped in 8h (rarely writes SCREAMING_CASE).
- **Layer Lock** — dropped in 8e (the design already avoids the pain it solves).
- **Sentence Case** — user declined. (It auto-caps after `. `; the failure mode is Portuguese abbreviations — `Sr.` `Dr.` `Av.` — falsely triggering, needing a hand-maintained exception list.)
- **Custom Shift Keys** — user declined. Every entry is another exception to remember; only worth it for a specific known annoyance, and there isn't one.
- **Repeat Key** — PARKED, not rejected. See D11: good feature, no good key.

**Also evaluated and skipped for this user** (research): Leader Key (sequence memorization — wrong for a memorability-first noob; use Raycast/Espanso snippets for text expansion instead) · Dynamic Macros (no persistence across reboot) · Callum-style one-shot mods (redundant with home-row mods + Chordal Hold) · Tap Dance (the "what does N taps do" problem the redesign exists to escape) · SOCD Cleaner (gaming only) · Mouse Turbo Click (superseded by Orbital Mouse).

**Backlog / notable:**
- **Flow Tap** (QMK core; was Getreuer's "Tap Flow") — reduces mod-tap misfires during fast typing rolls. Only reach for it if accidental-mods show up after flashing.
- **QMK Community Modules** (core, since 0.28.0, Feb 2025) — the `git submodule` mechanism that makes Getreuer's modules near-zero-glue via `keymap.json`. Prefer the `modules/` form over hand-copying `features/*.c` so upstream fixes come free.
- Other module collections exist (tzarc, drashna, elpekenin, silvinor) — nothing in them beat the list above for this profile.
- **EurKey** — Getreuer's own recommendation for EN+PT on macOS, and it would cut keystrokes vs. dead keys. **Not adopted:** D6 deliberately chose dead keys for *zero macOS config*, and EurKey requires changing the system input source. Parked as a genuine alternative if the dead-key approach chafes.
