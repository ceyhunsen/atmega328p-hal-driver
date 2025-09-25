# ATmega328P HAL Drivers

Unofficial (not affiliated with Microchip in any way) hardware abstraction layer
drivers for ATmega328P microcontroller. This driver provides an easy to use
interface for device peripherals while staying fast and small as possible.

> [!WARNING]
>
> This software is in it's early development. Use it with caution!

## Requirements

AVR toolchain, including `avr-gcc` and `avr-libc` is needed to compile and test
this project.

```sh
# For Ubuntu
sudo apt install avr-libc avr-gcc

# For Fedora
sudo dnf install avr*
```

## Usage

You can choose add this repo as a submodule to your project as a whole and link
with your project using provided `CMakeLists.txt` file:

```cmake
# Add ATmega328P HAL driver as a subdirectory.
add_subdirectory("${PROJECT_SOURCE_DIR}/ATmega328P-HAL-Driver" atmega328p_hal_build)
target_link_libraries(my_project PRIVATE ATmega328P_HAL_Driver)
```

Or, you can add specific `src/module.c` files to your build toolchain and add
[`include/`](include/) directory as one of the include dirs for the compiler,
manually.

## Documentation

Documentation can be generated locally. In order to generate documentation, your
system should have Doxygen installed.

```sh
cd docs/
doxygen Doxyfile
```

Generated documents will be placed in `docs/build` directory.

## Testing

There are local unit and integration tests that can test this driver without the
actual hardware. These tests utilizes [Unity](https://www.throwtheswitch.org/unity)
as the testing framework. You need to clone [Unity repository](https://github.com/ThrowTheSwitch/Unity)
as a submodule for testing. If you didn't also clone recursively while cloning
this repo, run:

```sh
git submodule update --init
```

Tests can be run using:

```sh
cd tests
make
```

## License

This project is licensed under [MIT license](LICENSE).
