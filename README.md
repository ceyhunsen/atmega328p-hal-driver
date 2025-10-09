# ATmega328P HAL Driver

Unofficial hardware abstraction layer driver for the ATmega328P microcontroller.
This driver aims to be suited for general use instead of a specific project or
use while staying fast and small as possible.

Please beware that this work is **not affiliated** with Microchip (or AVR) in
any way.

> [!WARNING]
>
> This library is in it's early development and can change drastically before
> v1.0. Use it with caution!

## Requirements

AVR toolchain, including [avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) and
[avr-libc](https://www.nongnu.org/avr-libc/) are needed to compile and test this
project.

```sh
# For Ubuntu
sudo apt install avr-libc avr-gcc

# For Fedora
sudo dnf install avr*
```

## Usage

You can choose to add this repo as a submodule to your project as a whole and
link to your project using the provided `CMakeLists.txt` file:

```cmake
# Add ATmega328P HAL driver as a subdirectory.
add_subdirectory("${PROJECT_SOURCE_DIR}/atmega328p-hal-driver" atmega328p_hal_build)
target_link_libraries(my_project PRIVATE atmega328p_hal_driver)
```

Or, you can add specific `src/module.c` files to your build toolchain and add
[`include/`](include/) directory as one of the include dirs for the compiler,
manually.

To compile built-in examples:

```sh
mkdir -p build && cd build
cmake -D CMAKE_C_COMPILER=avr-gcc -D BUILD_EXAMPLES=1 ..
cmake --build .
```

After compilation, example files will be in `build/examples/module_name/module_name`
and ready to be flashed to MCU.

## Documentation

Code documentation is available online at [atmega328p-hal-driver.readthedocs.io](https://atmega328p-hal-driver.readthedocs.io).
It can also be generated with `Doxygen`. Please see [docs/README.md](docs/README.md)
for more information about this.

## Testing

There are local unit and integration tests that can test this driver without the
actual hardware. These tests utilizes [Unity](https://www.throwtheswitch.org/unity)
as the testing framework. [Unity repository](https://github.com/ThrowTheSwitch/Unity)
already added as a submodule to this repo. If you didn't clone this repo
recursively, run:

```sh
git submodule update --init
```

Tests can be run using:

```sh
mkdir -p build && cd build
cmake -D BUILD_TESTING=1 ..
cmake --build .
make test
```

## License

This project is licensed under the [MIT license](LICENSE).
