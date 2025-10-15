# Basic commands for the atmega328p-hal-driver project

C_FILES := $(shell find $(./) -name '*.c' -not -path "./tests/Unity/*")
H_FILES := $(shell find $(./) -name '*.h' -not -path "./tests/Unity/*")

format:
	clang-format $(C_FILES) -i
	clang-format $(H_FILES) -i

test:
	mkdir -p build
	cd build && cmake -D BUILD_TESTING=1 ..
	cd build && cmake --build .
	cd build && make test
