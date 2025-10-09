# Contributing to ATmega328P HAL Driver Repository

## Opening PRs and Issues

You can either open an issue to report a bug, suggest a new feature or discuss
another topic. Or, you can directly open a PR without a matching issue to
suggest changes. Opening an issue beforehand might decrease review time but it
is not necessary. Also, issues without PRs are also welcome.

## Formatting

This repository uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
to format it's code. You can run `make format` to format your code before
committing. Your PR will be checked against the default formatter by CI.

## Naming Conventions

* Module names follows ATmega328P data-sheet conventions. Although, longer names
might be shortened.
* All of the namings are in `snake_case`, except for the constants: they are in
`SCREAMING_SNAKE_CASE`.
* All file names includes `hal_` prefix (e.g.: `hal_usart.c`).
* All functions, structs, enums and enum members includes it's module name
prefix (e.g.: `usart_transmit()` or `struct usart_t`).

## Module Hierarchy

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions have `_irq` suffix. E.g.:
`hal_usart_irq.c`.
3. Extra module with non-standard functions (like support for `printf()` over
USART) have `_extra` suffix. E.g.: `hal_usart_extra.c`.
