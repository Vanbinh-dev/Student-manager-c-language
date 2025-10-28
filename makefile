CC = gcc
CFLAGS = 

TARGET = ./bin/app.exe
SRC_DIR = src
INCLUDE_DIR = include

HEADER_DIR = ${INCLUDE_DIR} \
	${INCLUDE_DIR}/helper \
	${INCLUDE_DIR}/service \
	${INCLUDE_DIR}/model \
	${INCLUDE_DIR}/file 

DEPS = ${addprefix -I,${HEADER_DIR}}


SRC_FILE = $(wildcard ${SRC_DIR}/*.c) \
	$(wildcard ${SRC_DIR}/helper/*.c) \
	$(wildcard ${SRC_DIR}/model/*.c) \
	$(wildcard ${SRC_DIR}/file/*.c) \
	$(wildcard ${SRC_DIR}/service/*.c) 

.PHONY :clean build run rebuild all

build:
	${CC} ${CFLAGS} ${SRC_FILE} -I./${INCLUDE_DIR} -o ${TARGET}

run:
	${TARGET}

rebuild: build run

clean:
	rm -f *.exe *.o