#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/map"

#define mu_assert_fread_map(FILENAME, VALUE, SZ) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    uint32_t value = minipack_fread_map(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %d", value); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_map(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_map(file, VALUE, &sz); \
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

int test_is_map() {
    mu_assert(minipack_is_map("\x80") == true);
    mu_assert(minipack_is_map("\x8F") == true);
    mu_assert(minipack_is_map("\xDE\x00\x00") == true);
    mu_assert(minipack_is_map("\xDF\x00\x00\x00\x00") == true);

    mu_assert(minipack_is_map("\x00") == false);
    mu_assert(minipack_is_map("\xF0") == false);
    return 0;
}

int test_unpack_map() {
    size_t sz;
    
    // Fixmap
    mu_assert(minipack_unpack_map("\x80", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_map("\x8F", &sz) == 15);
    mu_assert(sz == 1);

    // map16
    mu_assert(minipack_unpack_map("\xDE\x00\x10", &sz) == 16);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_map("\xDE\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // map32
    mu_assert(minipack_unpack_map("\xDF\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_map("\xDF\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    return 0;
}

int test_pack_map() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Fixmap
    minipack_pack_map(data, 0, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x80");
    minipack_pack_map(data, 15, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x8F");

    // map16
    minipack_pack_map(data, 16, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDE\x00\x10");
    minipack_pack_map(data, 65535, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDE\xFF\xFF");

    // map32
    minipack_pack_map(data, 65536, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDF\x00\x01\x00\x00");
    minipack_pack_map(data, 4294967295, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDF\xFF\xFF\xFF\xFF");

    return 0;
}

int test_fread_map() {
    // fixmap
    mu_assert_fread_map("tests/fixtures/map/0", 0, 1);
    mu_assert_fread_map("tests/fixtures/map/15", 15, 1);

    // map16
    mu_assert_fread_map("tests/fixtures/map/16", 16, 3);
    mu_assert_fread_map("tests/fixtures/map/65535", 65535, 3);

    // map32
    mu_assert_fread_map("tests/fixtures/map/65536", 65536, 5);
    mu_assert_fread_map("tests/fixtures/map/4294967295", 4294967295, 5);

    // ERR
    mu_assert_fread_map("tests/fixtures/fixnum/-1", 0, 0);
    mu_assert_fread_map("tests/fixtures/fixnum/-32", 0, 0);
    mu_assert_fread_map("tests/fixtures/int/127", 0, 0);
    mu_assert_fread_map("tests/fixtures/int/-128", 0, 0);

    return 0;
}

int test_fwrite_map() {
    // fixmap
    mu_assert_fwrite_map("tests/fixtures/map/0", 0, 1, 0);
    mu_assert_fwrite_map("tests/fixtures/map/15", 15, 1, 0);

    // map16
    mu_assert_fwrite_map("tests/fixtures/map/16", 16, 3, 0);
    mu_assert_fwrite_map("tests/fixtures/map/65535", 65535, 3, 0);

    // map32
    mu_assert_fwrite_map("tests/fixtures/map/65536", 65536, 5, 0);
    mu_assert_fwrite_map("tests/fixtures/map/4294967295", 4294967295, 5, 0);

    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_map);
    mu_run_test(test_unpack_map);
    mu_run_test(test_pack_map);
    mu_run_test(test_fread_map);
    mu_run_test(test_fwrite_map);
    return 0;
}

RUN_TESTS()