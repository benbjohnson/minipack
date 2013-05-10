################################################################################
# Variables
################################################################################

VERSION=0.5.2

CFLAGS=-g -O4 -Wall -Wextra -std=c99 -D_FILE_OFFSET_BITS=64 -lmsgpack

SOURCES=src/minipack.c
OBJECTS=bin/minipack.o
TEST_SOURCES=$(wildcard tests/*_tests.c)
TEST_OBJECTS=$(patsubst %.c,%,${TEST_SOURCES})

PACKAGE=pkg/minipack-${VERSION}.tar.gz
PKGTMPDIR=pkg/tmp/minipack-${VERSION}

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
test: .prepared-msgpack $(TEST_OBJECTS) tmp
	@sh ./tests/runtests.sh

build/tests:
	mkdir -p build/tests
	mkdir -p build/tests/eql

$(TEST_OBJECTS): %: %.c ${OBJECTS}
	$(CC) $(CFLAGS) -Wno-unused-result -Isrc -Imsgpack-c/src -Lmsgpack-c/src/.libs -o $@ $< ${OBJECTS}

.prepared-ruby:
	if [ ! -f /usr/bin/ruby ]; then                                  \
		[ -f /usr/bin/sudo ] && { sudo apt-get install ruby; };      \
		[ ! -f /usr/bin/sudo ] && { su -c "apt-get install ruby"; }; \
	fi;                                                              \
	if [ -f /usr/bin/ruby ]; then touch .prepared-ruby ; fi

.prepared-msgpack: .prepared-ruby
	if [ ! -f msgpack-c/bootstrap ]; then git clone https://github.com/msgpack/msgpack-c.git ; fi
	if [ ! -f msgpack-c/Makefile ]; then cd msgpack-c; sh bootstrap; fi
	if [ ! -f msgpack-c/src/libmsgpack.la ]; then cd msgpack-c; sh configure; make; fi
	if [ -f msgpack-c/src/libmsgpack.la ]; then touch .prepared-msgpack ; fi

################################################################################
# Package
################################################################################

package:
	rm -rf pkg
	mkdir -p ${PKGTMPDIR}
	echo "// minipack v${VERSION}\n" > pkg/header
	cat pkg/header src/minipack.h > ${PKGTMPDIR}/minipack.h
	cat pkg/header src/minipack.c > ${PKGTMPDIR}/minipack.c
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
	rm -rf tmp pkg msgpack-c .prepared-ruby .prepared-msgpack
