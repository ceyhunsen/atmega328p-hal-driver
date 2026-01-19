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
add_subdirectory("${PROJECT_SOURCE_DIR}/path/to/atmega328p-hal-driver")
target_link_libraries(my_project PRIVATE atmega328p_hal_driver)
```

Or if you are not using Cmake, you can add specific modules in `src/` directory
to your build toolchain. And finally add [`include/`](include/) directory as one
of the include dirs of the compiler, manually.

You can try provided examples on your MCU. To compile built-in examples:

```sh
mkdir -p build && cd build
cmake -D CMAKE_C_COMPILER=avr-gcc -D BUILD_EXAMPLES=1 ..
cmake --build .
```

After compilation, example files will be in `build/examples/module_name/module_name`.
They will be ready to be flashed to the MCU.

## Documentation

Documentation can be generated either locally or can be found online at
[atmega328p-hal-driver.readthedocs.io](https://atmega328p-hal-driver.readthedocs.io).

To generate documentation locally:

```sh
cd docs/
doxygen Doxyfile
```

Open `build/html/index.html` in your preferred browser for the webpage. Or
proceed to generate PDF file version with latex:

```sh
cd build/latex
make
```

Generated PDF file (`refman.pdf`) will be in `build/latex` directory.

## Testing

There are unit and integration tests that can be used to test this driver
without the actual hardware. These tests utilizes
[Unity](https://www.throwtheswitch.org/unity) as the testing framework.
[Unity repository](https://github.com/ThrowTheSwitch/Unity) already added as a
submodule to this repo. If you didn't clone this repo recursively, run:

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

Or, you can call `make test` in the root directory for an easier experience.

## Contributing and License

You are welcome to contribute to this project. But please read
[CONTRIBUTING.md](CONTRIBUTING.md) beforehand.

This project is licensed under the [MIT license](LICENSE).
