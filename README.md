# ArduinoPatterns

[![CI](https://github.com/devkyato/Custom-Arduino-Libraries/actions/workflows/ci.yml/badge.svg)](https://github.com/devkyato/Custom-Arduino-Libraries/actions/workflows/ci.yml)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.21853284.svg)](https://doi.org/10.5281/zenodo.21853284)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

ArduinoPatterns 1.0.3 is a focused Arduino library for coordinating LEDs and
other digital outputs without blocking `loop()`. It packages common teaching
patterns into reusable components that can run alongside buttons, sensors,
serial communication, displays, or networking.

## Why ArduinoPatterns

- `LedBank`: treat up to 32 output pins as a bit mask.
- `LedAnimator`: play timed mask sequences using rollover-safe `millis()` logic.
- `PeriodicOutput`: blink independent outputs at different rates.
- No heap allocation, third-party dependencies, interrupts, or board-specific API.
- Seven compile-checked examples spanning traffic lights, scanners, counters,
  alternating masks, independent blinkers, and button pause/resume.

## Installation

Download the latest release ZIP and choose **Sketch > Include Library > Add .ZIP
Library** in Arduino IDE. In PlatformIO:

```ini
lib_deps =
  https://github.com/devkyato/Custom-Arduino-Libraries.git#v1.0.3
```

To work from source, clone the repository into the Arduino `libraries` folder or
add its root as a local PlatformIO library.

## Quick start

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

`update()` never waits for a phase to finish, so other application work remains
responsive.

## Examples gallery

| Example | Demonstrates | Companion-course connection |
| --- | --- | --- |
| [TrafficLight](examples/TrafficLight/TrafficLight.ino) | timed phases and a three-output mask | elapsed-time scheduling foundation |
| [ScanningLight](examples/ScanningLight/ScanningLight.ino) | forward/reverse animation | [Exercise B](https://github.com/devkyato/Arduino-Programs-Guide/blob/main/docs/lessons/exercise-b.md) and Exercise E |
| [AlternatingPatterns](examples/AlternatingPatterns/AlternatingPatterns.ino) | reusable multi-step mask sequences | Exercise B pattern design |
| [BinaryCounter](examples/BinaryCounter/BinaryCounter.ino) | direct `LedBank` masks and rollover-safe timing | arrays, bit masks, and output mapping |
| [CountUpDown](examples/CountUpDown/CountUpDown.ino) | longer repeating animation tables | progression toward state-machine lessons |
| [IndependentBlink](examples/IndependentBlink/IndependentBlink.ino) | two concurrent periodic outputs | cooperative scheduling used throughout Exercises C–F |
| [ButtonPause](examples/ButtonPause/ButtonPause.ino) | pause and resume with `stop()` / `start()` | interactive control without blocking `loop()` |

These examples are maintained adaptations of concepts present in the repository's
earlier laboratory sketches; they are not claimed as unchanged originals. Git
history preserves provenance. The companion
[Arduino Programs Guide](https://github.com/devkyato/Arduino-Programs-Guide)
provides a structured course progression and introduces the library as an
optional abstraction from Exercise B onward.

## Applications

- Non-blocking traffic lights, scanners, counters, and status indicators.
- Arduino timing, bit-mask, and cooperative state-machine instruction.
- Responsive output patterns alongside sensors, serial, or network activity.
- Active-low LED or relay modules through logical output inversion.

## Compatibility, safety, and limitations

The public API uses only `pinMode`, `digitalWrite`, and unsigned millisecond
arithmetic. CI compiles every example for Arduino AVR Uno, ESP32, and RP2040;
this is source compatibility evidence, not hardware validation. Other Arduino
architectures may work but are unverified.

- Respect each board's GPIO voltage and current ratings; use a series resistor
  for every LED and a suitable driver for relays, motors, or other loads.
- `LedBank` supports 1–32 outputs. The caller must keep pin and pattern arrays
  alive for the lifetime of the objects that reference them.
- `millis()` scheduling is rollover-safe, but updates only occur when `update()`
  is called; long blocking work elsewhere still delays transitions.
- A zero `PeriodicOutput` interval disables automatic toggling.

## Documentation index

- [API reference](docs/API.md) — ownership, lifecycle, active-low behavior, and
  rollover semantics.
- [Examples gallery](#examples-gallery) — working sketches mapped to concepts.
- [Contributing guide](CONTRIBUTING.md) — development and test expectations.
- [Security policy](SECURITY.md) — supported release and reporting process.
- [Changelog](CHANGELOG.md) and [1.0.3 release notes](RELEASE_NOTES.md).

## Citation

If you use this software in research or teaching, cite the archived release when
available, or use:

```text
@dev.mako (devkyato). (2026). ArduinoPatterns: non-blocking LED and digital-output patterns for Arduino (Version 1.0.3). Zenodo. https://doi.org/10.5281/zenodo.21853284
```

See [CITATION.cff](CITATION.cff) for machine-readable metadata.

## Contributing

Student-friendly issues are labeled `good first issue`. Changes should remain
non-blocking, avoid dynamic allocation, include native tests for timing logic, and
compile at least the Uno example. See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

[MIT](LICENSE)
