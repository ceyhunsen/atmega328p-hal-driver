# Changelog

All notable changes to this project will be documented in this file and will
also be mirrored to the Github releases page.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Callback function to mock sleep instruction.
- Power module extra: `hal_power_change_module_powers`.
- `hal_result_power` return type for the power module functions.

### Changed

- Naming conventions for module members like functions.
- C standard to C99.

### Fixed

- Reserved and illegal value usage checks in power module.

## [0.4.0] - 2025-10-15

### Added

- Default formatter.
- CI/CD jobs for:
  - Check formatting.
  - Compile for AVR architecture
  - Test
- Support for CMake.
- SPDX identifiers for each source file.
- Clock module.
- Threaded register and interrupt watcher for tests.

### Changed

- Updated README:
  - Added project requirements.
  - How to run tests.
  - How to compile examples.
- Tests and examples are built with CMake.
- Tests run with CTest.
- Online docs are re-enabled and cleaned from Sphinx boilerplate (now is vanilla
  Doxygen).
- Module documentations are moved into header files.

### Fixed

- Read the docs build.

## [0.3] - 2023-12-1

### Changed

- Renamed `GPIO` module to `IO`.

## [0.2] - 2023-11-19

### Added

- `system` module.

## [0.1] - 2023-11-12

There was an older implementation before versioning. That's why v0.1 is not
only about added changes. Older implementation is in
[`old_design`](https://github.com/ceyhunsen/ATmega328P-HAL-Driver/tree/old_design)
branch.

### Added

- Multiple new modules:
  - GPIO
  - Power
  - USART

### Changed

- Renamed file and function prefixes from `atmega328p_hal` to `hal`.

### Removed

- Unfinished modules' code and documentation:
  - SPI
  - Timer
  - TWI
  - ADC

[unreleased]: https://github.com/ceyhunsen/ATmega328P-HAL-Driver/compare/v0.4.0...HEAD
[0.4.0]: https://github.com/ceyhunsen/ATmega328P-HAL-Driver/compare/v0.3...v0.4.0
[0.3]: https://github.com/ceyhunsen/ATmega328P-HAL-Driver/compare/v0.2...v0.3
[0.2]: https://github.com/ceyhunsen/ATmega328P-HAL-Driver/compare/v0.1...v0.2
[0.1]: https://github.com/ceyhunsen/ATmega328P-HAL-Driver/compare/old_design...v0.1
