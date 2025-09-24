# ATmega328P HAL Drivers

Unofficial (not affiliated with Microchip in any way) hardware abstraction layer
drivers for ATmega328P microcontroller. This driver provides easy to use
interface for device peripherals while staying fast and small as possible.

## Requirements

AVR libc is needed to compile this project.

```sh
# For Ubuntu
sudo apt install avr-libc avr-gcc
```

## Documentation

Documentation can be generated locally. In order to generate documentation, your
system should have Doxygen installed.

```sh
cd docs/
doxygen Doxyfile
```

Generated documents will be placed in `docs/build` directory.

## Testing

Local unit and integration tests uses Unity for the framework. You need to clone
that submodule for testing. If you didn't also clone submodules while cloning
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
