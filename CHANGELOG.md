# Changelog

All notable changes to ArduinoPatterns are documented here. The project follows
[Semantic Versioning](https://semver.org/).

## [Unreleased]

## [1.0.3] - 2026-08-12

### Added

- Add a `ButtonPause` example showing non-blocking pause/resume with `stop()` and `start()`.

### Fixed

- Update the bug-report template placeholder to 1.0.2.

## [1.0.2] - 2026-08-09

### Changed

- Overhaul the README and Zenodo presentation with installation, real code,
  applications, limitations, documentation, companion-course links, and an
  example-to-concept gallery.
- Expand Citation File Format metadata and align release metadata and attribution
  on `@dev.mako (devkyato)`.
- Package API, citation, release-note, and governance documents in the Arduino
  IDE ZIP.
- Compile every example across Uno, ESP32, and RP2040 CI targets and validate
  release metadata without additional dependencies.

### Fixed

- Update the bug-report template's stale example version.

## [1.0.1] - 2026-08-09

### Changed

- Add Zenodo and Citation File Format metadata for archival citation.
- Refresh published Arduino library metadata for the 1.0.1 release.

## [1.0.0] - 2026-07-29

### Added

- `LedBank` for controlling up to 32 active-high or active-low outputs as a mask.
- `LedAnimator` for rollover-safe, non-blocking timed sequences.
- `PeriodicOutput` for independent periodic digital outputs.
- Six Arduino IDE examples adapted from the repository's original exercises.
- Native timing tests and compile checks for Uno, ESP32, and Raspberry Pi Pico.
- Arduino IDE ZIP and PlatformIO installation metadata.

[1.0.0]: https://github.com/devkyato/Custom-Arduino-Libraries/releases/tag/v1.0.0
[1.0.1]: https://github.com/devkyato/Custom-Arduino-Libraries/compare/v1.0.0...v1.0.1
[1.0.3]: https://github.com/devkyato/Custom-Arduino-Libraries/compare/v1.0.2...v1.0.3
[1.0.2]: https://github.com/devkyato/Custom-Arduino-Libraries/compare/v1.0.1...v1.0.2
