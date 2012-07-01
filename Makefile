################################################################################
# Variables
################################################################################

CFLAGS=-g -Wall -Wextra -std=c99 -D_FILE_OFFSET_BITS=64

SOURCES=src/minipack.c
OBJECTS=bin/minipack.o
TEST_SOURCES=$(wildcard tests/*_tests.c)
TEST_OBJECTS=$(patsubst %.c,%,${TEST_SOURCES})


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
test: $(TEST_OBJECTS)
	@sh ./tests/runtests.sh

build/tests:
	mkdir -p build/tests
	mkdir -p build/tests/eql

$(TEST_OBJECTS): %: %.c ${OBJECTS}
	$(CC) $(CFLAGS) -Isrc -o $@ $< ${OBJECTS}


################################################################################
# Clean up
################################################################################

clean:
	rm -rf bin ${TEST_OBJECTS}
	rm -rf tests/*.dSYM
