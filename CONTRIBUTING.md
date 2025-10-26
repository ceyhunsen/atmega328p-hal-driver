# Contributing to ATmega328P HAL Driver Repository

Please follow the [MIT license](LICENSE)'s rules to use, edit and distribute
this software.

## Opening PRs and Issues

Regarding to issues, you can open one to report a bug, suggest a new feature or
discuss another topic. You are welcome to open a PR fixing that issue but it
isn't a necessity.

Or, you can directly open a PR without a matching issue to suggest changes.
Opening an issue beforehand might decrease review time but it is not necessary,
as said above.

## Formatting

This repository uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
to format it's code. You can run `make format` to format your code before
committing. Your PR will be checked against the default formatter by CI.

## Naming Conventions

* Module names should follow ATmega328P data-sheet conventions. Although, longer
  names might be shortened.
* All of the namings should be in `snake_case`, except for the constants.
  Constants should be in `SCREAMING_SNAKE_CASE`.
* All file names, functions, structs, enums and enum members should include
  `hal_` prefix (e.g.: `hal_usart.c` or `hal_usart_transmit()`).
* All functions, structs, enums and enum members should also include it's module
  name as prefix after the `hal_` prefix (e.g.: `hal_usart_transmit()` or
  `struct hal_usart_t`).

## Module Hierarchy

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions have `_irq` suffix. E.g.:
   `hal_usart_irq.c`.
3. Extra module with non-standard functions (like support for `printf()` over
   USART) have `_extra` suffix. E.g.: `hal_usart_extra.c`.
