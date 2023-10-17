CC=gcc
BUILD_FOLDER=./build/

all: ${BUILD_FOLDER} aoc1 aoc2 aoc3 aoc4 aoc5 aoc6 aoc7 aoc8

${BUILD_FOLDER}:
	@mkdir -p ${BUILD_FOLDER}

aoc1: aoc1.c
	${CC} -o ${BUILD_FOLDER}aoc1 aoc1.c

aoc2: aoc2.c
	${CC} -o ${BUILD_FOLDER}aoc2 aoc2.c

aoc3: aoc3.c
	${CC} -o ${BUILD_FOLDER}aoc3 aoc3.c

aoc4: aoc4.c
	${CC} -o ${BUILD_FOLDER}aoc4 aoc4.c

aoc5: aoc5.c
	${CC} -o ${BUILD_FOLDER}aoc5 aoc5.c

aoc6: aoc6.c
	${CC} -o ${BUILD_FOLDER}aoc6 aoc6.c

aoc7: aoc7.c
	${CC} -o ${BUILD_FOLDER}aoc7 aoc7.c

aoc8: aoc8.c
	${CC} -o ${BUILD_FOLDER}aoc8 aoc8.c

clean:
	rm ${BUILD_FOLDER}aoc1 ${BUILD_FOLDER}aoc2 ${BUILD_FOLDER}aoc3  \
	${BUILD_FOLDER}aoc4 ${BUILD_FOLDER}aoc5 ${BUILD_FOLDER}aoc6 \
	${BUILD_FOLDER}aoc7 ${BUILD_FOLDER}aoc8
