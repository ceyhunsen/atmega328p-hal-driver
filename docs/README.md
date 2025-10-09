# ATMega328P HAL Driver Documentation

This directory doesn't include any meaningful documentation to the end users. It
is here to generate nicely formatted code documentation. You can either generate
them yourself or visit it online at:
[atmega328p-hal-driver.readthedocs.io](https://atmega328p-hal-driver.readthedocs.io/en/latest/)

Before generating documentation, ensure you have the git submodule for the
theme:

```sh
git submodule update --init
```

To generate documentation:

```sh
cd docs/ # If not already in this directory
doxygen Doxyfile
```

Either open `build/html/index.html` in your browser or generate PDF with latex:

```sh
cd build/latex
make
```

Generated PDF file (`refman.pdf`) will be in `build/latex` directory.
