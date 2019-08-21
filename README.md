# My dz60 keymap
This is a QMK keymap for my custom dz60 keyboard, featuring split spacebar, arrow keys, and "flippable" number row.

## Features
+ ANSI layout
+ ISO Enter
+ SpaceFN (`FN` when held down, `Space` when tapped)
+ Split Space
+ Flipped numbers mode
+ CtrlEsc (`Ctrl` when held down, `Esc` when tapped)
+ Active layer indicated by backlight color

## How-To
This guide assumes that you have already cloned the source code for QMK firmware, if not you can find it [here](https://github.com/qmk/qmk_firmware/).

Put my `keymap.c` file in `$qmk-firmware$/keyboards/dz60/keymaps/dz60_keymap_lars/`. Then from the `$qmk-firmware$` folder run `make dz60:dz60_keymap_lars:dfu` to compile the firmware and flash it to the keyboard.

## Layout


### Base layer
```
  ,-----------------------------------------------------------------------------------------.
  | `~  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
  |-----------------------------------------------------------------------------------------+
  | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |        |
  |--------------------------------------------------------------------------------+. Enter |
  | Caps    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |  \  |       |
  |-----------------------------------------------------------------------------------------+
  | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |Shift| Up  | Win |
  |-----------------------------------------------------------------------------------------+
  | Ctrl | Win | Alt  |    SpaceFN    |SpaceFN|    SpaceFN    | Alt |Ctrl |Left |Down |Right|
  `-----------------------------------------------------------------------------------------'
 ```
The base layer is pretty straight forward, except for the `SpaceFN` keys, which doubles as `Space` key when tapped and `FN` when held down, and the `Ctrl` keys which double as `Escape` when tapped.


### FN layer
```
  ,-----------------------------------------------------------------------------------------.
  |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |   RESET   |
  |-----------------------------------------------------------------------------------------+
  |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
  |--------------------------------------------------------------------------------+.       |
  |         |     |     |     |     |     |     |     |     |     |     |     |     |       |
  |-----------------------------------------------------------------------------------------+
  |           |     |     |     |     |     |     |     |     |     |     |     |PgUp |     |
  |-----------------------------------------------------------------------------------------+
  |      |     |      |   Flipnums    |Flipnum|   Flipnums    |     |     |Home |PgDn | End |
  `-----------------------------------------------------------------------------------------'
 ```
The FN layer contains `F1`-`F12`, `Page Up`/`Page Down`, `Home`/`End`, and the `Flipnums` key which toggles flipped number row mode.

In addition to the layers, there is also the flipped number row mode, Flipnums mode. In Flipnums mode the numbers and symbols are swapped, so that you don't need to hold shift to type symbols.
