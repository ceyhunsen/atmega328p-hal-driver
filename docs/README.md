# ATMega328P HAL Driver Documentation

This directory doesn't include any meaningful documentation to the end users. It
is only here to generate nicely formatted code documentation with Doxygen. You
can either generate them yourself or visit
[atmega328p-hal-driver.readthedocs.io](https://atmega328p-hal-driver.readthedocs.io)

Before generating documentation, ensure you have [Doxygen](https://www.doxygen.nl/)
installed and the git submodule for the theme is cloned:

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
