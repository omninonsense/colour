all: build

build_dir = ./build
CFLAGS = -lm -Iinclude/
CC=gcc
STD=c11
SOVERSION=1

prepare: dir_structure
build: prepare shared

shared:
	$(CC) -shared -Wl,-soname,libcolour.so.$(SOVERSION) -o $(build_dir)/libcolour.so -std=$(STD) $(CFLAGS) -Wall -fPIC colour.c

# @TODO: Fix this.
arduino: prepare
	@echo " "
	@echo "Preparing Arduino-compatible library inside "$(build_dir)"/arduino"
	mkdir -p $(build_dir)/arduino/libcolour
	cp include/colour.h $(build_dir)/arduino/libcolour/colour.h
	cp colour.c $(build_dir)/arduino/libcolour/colour.cpp
	cp LICENSE $(build_dir)/arduino/libcolour/LICENSE
	cp README.md $(build_dir)/arduino/libcolour/README.md

dir_structure:
	mkdir -p $(build_dir)

clean:
	rm -rf $(build_dir)/
