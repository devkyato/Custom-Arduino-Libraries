# ArduinoPatterns

[![CI](https://github.com/devkyato/Custom-Arduino-Libraries/actions/workflows/ci.yml/badge.svg)](https://github.com/devkyato/Custom-Arduino-Libraries/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

ArduinoPatterns is a small teaching library for coordinating LEDs and other digital
outputs without `delay()`. It turns the original laboratory sketches in this
repository into reusable components that can run alongside buttons, sensors,
displays, networking, and serial communication.

## Features

- `LedBank`: treat up to 32 output pins as a bit mask.
- `LedAnimator`: play timed mask sequences using rollover-safe `millis()` logic.
- `PeriodicOutput`: blink independent outputs at different rates.
- No heap allocation, third-party dependencies, interrupts, or board-specific API.
- Arduino IDE and PlatformIO examples for traffic lights, scanning, counting,
  alternating patterns, and independent blinkers.

## Install

Download the latest release ZIP and choose **Sketch > Include Library > Add .ZIP
Library** in Arduino IDE. In PlatformIO:

```ini
lib_deps =
  https://github.com/devkyato/Custom-Arduino-Libraries.git#v1.0.1
```

## Quick example

```cpp
#include <ArduinoPatterns.h>

const uint8_t pins[] = {6, 7, 8};
const PatternStep traffic[] = {
    {0b001, 5000},  // green
    {0b010, 2000},  // yellow
    {0b100, 5000},  // red
};

LedBank lights(pins, 3);
LedAnimator animation(lights, traffic, 3);

void setup() {
  lights.begin();
  animation.start(millis());
}

void loop() {
  animation.update(millis());
  // Other application work can run here.
}
```

Open **File > Examples > ArduinoPatterns** for complete sketches. The examples map
the original student work into reusable patterns; the original commits remain in
the repository history.

See the [API reference](docs/API.md) for lifecycle, ownership, rollover, and
active-low behavior.

## Compatibility

The public API uses only `pinMode`, `digitalWrite`, and unsigned millisecond
arithmetic. CI compiles for Arduino AVR Uno, ESP32, and RP2040. Other Arduino
architectures are expected to work but should be reported as verified only after an
actual compile or hardware test.

## Citation

If you use this software in research or teaching, please cite the Zenodo archive / this repository:

```text
devkyato. (2026). ArduinoPatterns: non-blocking LED and digital-output patterns for Arduino (Version 1.0.1).
```

See [CITATION.cff](CITATION.cff) for machine-readable metadata.

## Applications

- Non-blocking LED and traffic-light demonstrations.
- Arduino timing and state-machine lessons.
- Responsive ESP32 and RP2040 digital-output sketches.
- Reusable output patterns alongside sensors and serial communication.

## Contributing

Student-friendly issues are labeled `good first issue`. Changes should remain
non-blocking, avoid dynamic allocation, include native tests for timing logic, and
compile at least the Uno example. See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

[MIT](LICENSE)
