# @author	: on3ye (on3ye@proton.me)
# @date		: 11-07-2024 17:00
# @title	: EasyClick Makefile Setup

# Build Configuration
CC = gcc
SOURCE_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include

# Compiler Options
CFLAGS = -Iinclude `pkg-config --cflags gtk4`
LIBS = `pkg-config --libs gtk4`

all: final

final: ${SOURCE_DIR}/main.o ${SOURCE_DIR}/activate.o
	${CC} ${CFLAGS} ${SOURCE_DIR}/main.o ${SOURCE_DIR}/activate.o -o ${BUILD_DIR}/final ${LIBS}
	chmod +x ${BUILD_DIR}/final

main.o: ${SOURCE_DIR}/main.c
	${CC} ${CFLAGS} -c ${SOURCE_DIR}/main.c ${LIBS}

activate.o: ${SOURCE_DIR}/activate.c
	${CC} ${CFLAGS} -c ${SOURCE_DIR}/activate.c ${LIBS}

clean:
	rm -f ${BUILD_DIR}/*;
	rm -f ${SOURCE_DIR}/*.o;
