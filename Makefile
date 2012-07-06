################################################################################
# Variables
################################################################################

VERSION=0.3.0

CFLAGS=-g -Wall -Wextra -std=c99 -D_FILE_OFFSET_BITS=64 -lmsgpack

SOURCES=src/minipack.c
OBJECTS=bin/minipack.o
TEST_SOURCES=$(wildcard tests/*_tests.c)
TEST_OBJECTS=$(patsubst %.c,%,${TEST_SOURCES})

PACKAGE=pkg/minipack-${VERSION}.tar.gz

################################################################################
# Default Target
################################################################################

all: ${OBJECTS} test


################################################################################
# Sources
################################################################################

bin:
	mkdir -p bin

${OBJECTS}: bin ${SOURCES}
	$(CC) $(CFLAGS) -c -o ${OBJECTS} ${SOURCES}

################################################################################
# Tests
################################################################################

.PHONY: test
test: $(TEST_OBJECTS) tmp
	@sh ./tests/runtests.sh

build/tests:
	mkdir -p build/tests
	mkdir -p build/tests/eql

$(TEST_OBJECTS): %: %.c ${OBJECTS}
	$(CC) $(CFLAGS) -Isrc -o $@ $< ${OBJECTS}


################################################################################
# Package
################################################################################

package:
	rm -rf pkg
	mkdir -p pkg/tmp/minipack
	echo "// minipack v${VERSION}\n" > pkg/header
	cat pkg/header src/minipack.h > pkg/tmp/minipack/minipack.h
	cat pkg/header src/minipack.c > pkg/tmp/minipack/minipack.c
	tar czvf ${PACKAGE} -C pkg/tmp .
	rm -rf pkg/header pkg/tmp


################################################################################
# Misc
################################################################################

tmp:
	mkdir -p tmp

################################################################################
# Clean up
################################################################################

clean:
	rm -rf bin ${TEST_OBJECTS}
	rm -rf tests/*.dSYM
	rm -rf tmp
