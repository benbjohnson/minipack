#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/float"

#define mu_assert_fread_float(FILENAME, VALUE, SZ, POS) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    float value = minipack_fread_float(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %f", value); \
    mu_assert_with_msg(pos+POS == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_float(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_float(file, VALUE, &sz); \
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

int test_is_float() {
    mu_assert(minipack_is_float("\xCA\x00\x00\x00\x00") == true);
    mu_assert(minipack_is_float("\x00\x00\x00\x00\x00") == false);
    return 0;
}

int test_unpack_float() {
    size_t sz;

    mu_assert(minipack_unpack_float("\xCA\x00\x00\x00\x00", &sz) == 0);
    mu_assert_msgpack_float(0, 5, "\xCA\x00\x00\x00\x00");
    mu_assert(sz == 5);

    mu_assert(minipack_unpack_float("\xCA\x42\xC8\x00\x00", &sz) == 100);
    mu_assert_msgpack_float(100, 5, "\xCA\x42\xC8\x00\x00");
    mu_assert(sz == 5);

    mu_assert(minipack_unpack_float("\xCA\xC2\xC8\x00\x00", &sz) == -100);
    mu_assert_msgpack_float(-100, 5, "\xCA\xC2\xC8\x00\x00");
    mu_assert(sz == 5);

    float value = minipack_unpack_float("\xCA\x42\xC8\x66\x66", &sz);      //= 100.2
    mu_assert_mem(&value, 4, "\x66\x66\xC8\x42");
    mu_assert_msgpack_float(100.2, 5, "\xCA\x42\xC8\x66\x66");
    mu_assert(sz == 5);

    return 0;
}

int test_pack_float() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_float(data, 0, &sz);
    mu_assert_mem(data, 5, "\xCA\x00\x00\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_float(data, 100, &sz);
    mu_assert_mem(data, 5, "\xCA\x42\xC8\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_float(data, -100, &sz);
    mu_assert_mem(data, 5, "\xCA\xC2\xC8\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_float(data, 100.2, &sz);
    mu_assert_mem(data, 5, "\xCA\x42\xC8\x66\x66");
    mu_assert(sz == 5);

    return 0;
}

int test_fread_float() {
    mu_assert_fread_float("tests/fixtures/float/0", 0, 5, 5);
    mu_assert_fread_float("tests/fixtures/float/100", 100, 5, 5);
    mu_assert_fread_float("tests/fixtures/float/-100", -100, 5, 5);
    mu_assert_fread_float("tests/fixtures/fixnum/127", 0, 0, 1);
    return 0;
}

int test_fwrite_float() {
    mu_assert_fwrite_float("tests/fixtures/float/0", 0, 5, 0);
    mu_assert_fwrite_float("tests/fixtures/float/100", 100, 5, 0);
    mu_assert_fwrite_float("tests/fixtures/float/-100", -100, 5, 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_float);
    mu_run_test(test_unpack_float);
    mu_run_test(test_pack_float);
    mu_run_test(test_fread_float);
    mu_run_test(test_fwrite_float);
    return 0;
}

RUN_TESTS()