#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/array"

#define mu_assert_fread_array(FILENAME, VALUE, SZ) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    uint32_t value = minipack_fread_array(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %d", value); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_array(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_array(file, VALUE, &sz); \
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

int test_is_array() {
    mu_assert(minipack_is_array("\x90") == true);
    mu_assert(minipack_is_array("\x9F") == true);
    mu_assert(minipack_is_array("\xDC\x00\x00") == true);
    mu_assert(minipack_is_array("\xDD\x00\x00\x00\x00") == true);

    mu_assert(minipack_is_array("\x00") == false);
    mu_assert(minipack_is_array("\xF0") == false);
    return 0;
}

int test_unpack_array() {
    size_t sz;
    
    // Fixarray
    mu_assert(minipack_unpack_array("\x90", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_array("\x9F", &sz) == 15);
    mu_assert(sz == 1);

    // array16
    mu_assert(minipack_unpack_array("\xDC\x00\x10", &sz) == 16);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_array("\xDC\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // array32
    mu_assert(minipack_unpack_array("\xDD\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_array("\xDD\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    return 0;
}

int test_pack_array() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Fixarray
    minipack_pack_array(data, 0, &sz);
    printf("sz %ld\n", sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x90");
    minipack_pack_array(data, 15, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x9F");

    // array16
    minipack_pack_array(data, 16, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDC\x00\x10");
    minipack_pack_array(data, 65535, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDC\xFF\xFF");

    // array32
    minipack_pack_array(data, 65536, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDD\x00\x01\x00\x00");
    minipack_pack_array(data, 4294967295, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDD\xFF\xFF\xFF\xFF");

    return 0;
}

int test_fread_array() {
    // fixarray
    mu_assert_fread_array("tests/fixtures/array/0", 0, 1);
    mu_assert_fread_array("tests/fixtures/array/15", 15, 1);

    // array16
    mu_assert_fread_array("tests/fixtures/array/16", 16, 3);
    mu_assert_fread_array("tests/fixtures/array/65535", 65535, 3);

    // array32
    mu_assert_fread_array("tests/fixtures/array/65536", 65536, 5);
    mu_assert_fread_array("tests/fixtures/array/4294967295", 4294967295, 5);

    // ERR
    mu_assert_fread_array("tests/fixtures/fixnum/-1", 0, 0);
    mu_assert_fread_array("tests/fixtures/fixnum/-32", 0, 0);
    mu_assert_fread_array("tests/fixtures/int/127", 0, 0);
    mu_assert_fread_array("tests/fixtures/int/-128", 0, 0);

    return 0;
}

int test_fwrite_array() {
    // fixarray
    mu_assert_fwrite_array("tests/fixtures/array/0", 0, 1, 0);
    mu_assert_fwrite_array("tests/fixtures/array/15", 15, 1, 0);

    // array16
    mu_assert_fwrite_array("tests/fixtures/array/16", 16, 3, 0);
    mu_assert_fwrite_array("tests/fixtures/array/65535", 65535, 3, 0);

    // array32
    mu_assert_fwrite_array("tests/fixtures/array/65536", 65536, 5, 0);
    mu_assert_fwrite_array("tests/fixtures/array/4294967295", 4294967295, 5, 0);

    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_array);
    mu_run_test(test_unpack_array);
    mu_run_test(test_pack_array);
    mu_run_test(test_fread_array);
    mu_run_test(test_fwrite_array);
    return 0;
}

RUN_TESTS()