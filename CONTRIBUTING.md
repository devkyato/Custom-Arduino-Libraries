# Contributing

ArduinoPatterns is intended to be approachable for students and first-time
open-source contributors.

## Before you start

1. Search existing issues before opening a new one.
2. For behavior changes or new public APIs, open an issue first.
3. Keep the library non-blocking and avoid heap allocation.

## Local checks

Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/) and run:

```sh
pio test -e native
pio run -e uno
pio run -e esp32dev
pio run -e pico
python tools/build_release.py
```

Changes to timing logic need a native regression test. New features should include
an Arduino example or update an existing one. Hardware-dependent changes should
state the board and wiring used for verification.

## Pull requests

- Keep each pull request focused on one change.
- Use clear commit messages and explain the user-visible result.
- Update `CHANGELOG.md` for user-facing changes.
- Do not commit `.pio`, editor state, or generated `dist` files.

By participating, you agree to follow the [Code of Conduct](CODE_OF_CONDUCT.md).
