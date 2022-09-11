CC := gcc
LIB := ./lib
SRC := ./src
CFLAGS := -g
BUILDDIR := ./build

run: all
	./build/app

all: app

app: app.o termgl.o
	cd ./build && gcc $^ -o $@ ${CFLAGS} && cd ..

app.o: app.c
	gcc -c $< -o ${BUILDDIR}/$@ -I${SRC}

termgl.o: ${SRC}/termgl.c
	gcc -c $< -o ${BUILDDIR}/$@ -I${SRC}


clean:
	rm ${BUILDDIR}/*

