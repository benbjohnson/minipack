#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/double"

#define mu_assert_fread_double(FILENAME, VALUE, SZ, POS) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    double value = minipack_fread_double(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %f", value); \
    mu_assert_with_msg(pos+POS == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_double(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_double(file, VALUE, &sz); \
    mu_assert_with_msg(rc == RC, "Unexpected return value: %d", rc); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    mu_assert_file(TMPFILE, FILENAME); \
    fclose(file); \
} while(0)


//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_double() {
    mu_assert(minipack_is_double("\xCB\x00\x00\x00\x00\x00\x00\x00\x00") == true);
    mu_assert(minipack_is_double("\xCA\x00\x00\x00\x00\x00\x00\x00\x00") == false);
    return 0;
}

int test_sizeof_double() {
    mu_assert(minipack_sizeof_elem_and_data("\xCB\x00\x00\x00\x00\x00\x00\x00\x00") == 9);
    return 0;
}

int test_unpack_double() {
    size_t sz;
    mu_assert(minipack_unpack_double("\xCB\x00\x00\x00\x00\x00\x00\x00\x00", &sz) == 0);
    mu_assert_msgpack_double(0, 9, "\xCB\x00\x00\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    mu_assert(minipack_unpack_double("\xCB\x40\x59\x00\x00\x00\x00\x00\x00", &sz) == 100);
    mu_assert_msgpack_double(100, 9, "\xCB\x40\x59\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    mu_assert(minipack_unpack_double("\xCB\xC0\x59\x00\x00\x00\x00\x00\x00", &sz) == -100);
    mu_assert_msgpack_double(-100, 9, "\xCB\xC0\x59\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    double value = minipack_unpack_double("\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD", &sz);      // = 100.2
    mu_assert_mem(&value, 8, "\xCD\xCC\xCC\xCC\xCC\x0C\x59\x40");
    mu_assert_msgpack_double(100.2, 9, "\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");
    mu_assert(sz == 9);

    return 0;
}

int test_pack_double() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_double(data, 0, &sz);
    mu_assert_mem(data, 9, "\xCB\x00\x00\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    minipack_pack_double(data, 100, &sz);
    mu_assert_mem(data, 9, "\xCB\x40\x59\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    minipack_pack_double(data, -100, &sz);
    mu_assert_mem(data, 9, "\xCB\xC0\x59\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    minipack_pack_double(data, 100.2, &sz);
    mu_assert_mem(data, 9, "\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");
    mu_assert(sz == 9);

    return 0;
}

int test_fread_double() {
    mu_assert_fread_double("tests/fixtures/double/0", 0, 9, 9);
    mu_assert_fread_double("tests/fixtures/double/100", 100, 9, 9);
    mu_assert_fread_double("tests/fixtures/double/-100", -100, 9, 9);
    mu_assert_fread_double("tests/fixtures/fixnum/127", 0, 0, 1);
    return 0;
}

int test_fwrite_double() {
    mu_assert_fwrite_double("tests/fixtures/double/0", 0, 9, 0);
    mu_assert_fwrite_double("tests/fixtures/double/100", 100, 9, 0);
    mu_assert_fwrite_double("tests/fixtures/double/-100", -100, 9, 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_double);
    mu_run_test(test_sizeof_double);
    mu_run_test(test_unpack_double);
    mu_run_test(test_pack_double);
    mu_run_test(test_fread_double);
    mu_run_test(test_fwrite_double);
    return 0;
}

RUN_TESTS()