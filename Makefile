# Basic comands for the atmega328p-hal-driver project

C_FILES := $(shell find $(./) -name '*.c' -not -path "./tests/Unity/*")
H_FILES := $(shell find $(./) -name '*.h' -not -path "./tests/Unity/*")

format:
	clang-format $(C_FILES) -i
	clang-format $(H_FILES) -i
