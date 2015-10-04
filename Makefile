all: build

build_dir = ./build
CFLAGS = -lm -I include
CXX=gcc
STD=c11

prepare: dir_structure
build: prepare colour.c.o

colour.c.o:
	@echo " "
	@echo "Compiling Colour into object file"
	$(CXX) -DTESTBUILD -c -std=$(STD) -Wall colour.c -o $(build_dir)/colour.c.o $(CFLAGS)

arduino-lib: prepare
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
