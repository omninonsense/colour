BUILD_DIR = ./build
CFLAGS = -Iinclude/
CC=gcc
STD=c11
SOVERSION=1

all: build
build: shared

shared: prepare
	$(CC) -shared -Wl,-soname,libcolour.so.$(SOVERSION) -o $(BUILD_DIR)/libcolour.so -std=$(STD) $(CFLAGS) -Wall -fPIC colour.c
	@rm -f $(BUILD_DIR)/libcolour.so.$(SOVERSION)
	@ln -s libcolour.so $(BUILD_DIR)/libcolour.so.$(SOVERSION)

# @TODO: Fix this.
arduino: prepare
	@echo " "
	@echo "Preparing Arduino-compatible library inside "$(BUILD_DIR)"/arduino"
	mkdir -p $(BUILD_DIR)/arduino/libcolour
	cp include/colour.h $(BUILD_DIR)/arduino/libcolour/colour.h
	cp colour.c $(BUILD_DIR)/arduino/libcolour/colour.cpp
	cp LICENSE $(BUILD_DIR)/arduino/libcolour/LICENSE
	cp README.md $(BUILD_DIR)/arduino/libcolour/README.md

prepare:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/
