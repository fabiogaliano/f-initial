# My Voyager Keymap

Custom keymap for ZSA Voyager keyboard, initially generated from Oryx configurator.

## Building

From the QMK root directory:

```bash
make voyager:f-initial
```

## Flashing

```bash
make voyager:f-initial:flash
```

## Features

- Custom layout based on initial Oryx configuration
- Tap dance functionality
- Custom macros
- RGB lighting configuration

## Files

- `keymap.c` - Main keymap layout and custom functions
- `config.h` - Keyboard-specific configuration
- `rules.mk` - Build options and feature flags
- `i18n.h` - Internationalization support