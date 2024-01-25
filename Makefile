# Description: Makefile for the functools library
#
# @date 2024-01-20
# @author Marcio Reis Jr.
#
# This code is released under the GPLv2.1 license. Refer to the LICENSE file
# for more information.
#
help:
	@echo "    make all - build all"
	@echo "    make clean - clean build directory"
	@echo "    make test - build and run the tests"
	@echo "    make build/libfunctools.so - build library"

all: clean test clean build/libfunctools.so

clean:
	rm -rf build

build/libfunctools.so: functools.c functools.h build/str_join.o build/str_split.o build/str_set.o
	mkdir -p build && \
		gcc -O2 -c -fPIC -o build/functools.o functools.c && \
		gcc -O2 -shared -o build/libfunctools.so build/functools.o build/str_join.o build/str_split.o build/str_set.o

build/str_join.o: str_join.c str_join.h
	mkdir -p build && \
		gcc -O2 -c -o build/str_join.o str_join.c

build/str_split.o: str_split.c str_split.h
	mkdir -p build && \
		gcc -O2 -c -o build/str_split.o str_split.c

build/str_set.o: str_set.c str_set.h
	mkdir -p build && \
		gcc -O2 -c -o build/str_set.o str_set.c

test: str_join.c str_split.c functools.c functools.h str_join.h str_split.h str_set.c str_set.h
	mkdir -p build && \
		gcc -DTEST -fsanitize=address -g -O0 -o build/str_join str_join.c && \
		gcc -DTEST -fsanitize=address -g -O0 -o build/str_split str_split.c && \
		gcc -DTEST -fsanitize=address -g -O0 -o build/functools functools.c && \
		gcc -DTEST -fsanitize=address -g -O0 -o build/str_set str_set.c && \
		./build/str_join && ./build/str_split && ./build/functools && ./build/str_set
