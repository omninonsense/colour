all: build

build_dir = ./build
CFLAGS = -lm -I../include
CXX=avr-gcc
STD=c11

prepare: dir_structure colour.c.o

build: prepare build_msg $(patsubst %.c, %.out, $(wildcard *.c))
run: $(patsubst %.out, %.test, $(wildcard $(build_dir)/bin/*.out))

%.out: %.c Makefile
	$(CXX) -std=$(STD) -Wall $(CPPFLAGS) $(build_dir)/colour.c.o $< -o $(build_dir)/bin/$@ $(CFLAGS)

%.test: %.out
	@./$<

dir_structure:
	mkdir -p $(build_dir)/bin

colour.c.o:
	@echo " "
	@echo "Compiling Colour into object file"
	$(CXX) -DTESTBUILD -c -std=$(STD) -Wall ../colour.c -o $(build_dir)/colour.c.o $(CFLAGS)

clean:
	rm -rf $(build_dir)/

build_msg:
	@echo " "
	@echo "Compiling tests"
