# linco95 QMK userspace

Keymaps for my Corne (crkbd rev1, Pro Micro), built as a [QMK External Userspace](https://docs.qmk.fm/newbs_external_userspace) on top of an unmodified `qmk_firmware` checkout.

Keymap: [`keyboards/crkbd/keymaps/linco95`](keyboards/crkbd/keymaps/linco95)

## Setup

```sh
qmk setup                                   # once; clones qmk_firmware to ~/qmk_firmware
qmk config user.overlay_dir="$(realpath .)"
```

## Build & flash

```sh
qmk compile -kb crkbd/rev1 -km linco95      # or: qmk userspace-compile
qmk flash   -kb crkbd/rev1 -km linco95
```

Flash each half separately: run `qmk flash`, then double-tap the reset button on the half that's plugged in (or press `QK_BOOT` on the Adjust layer). Left half is master (`MASTER_LEFT`).

Pushing to GitHub also builds the firmware via `.github/workflows/build_binaries.yaml`.

## Swedish characters

`å ä ö` are on the Lower layer and are typed with macOS **US**-layout Option sequences (`⌥A`, `⌥U a`, `⌥U o`), not Unicode Hex Input — Chromium browsers (Brave, Chrome) drop the last hex digit so `ä` became `à`. Requires the macOS input source to be *U.S.* (or *ABC*).
