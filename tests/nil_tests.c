#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/nil"

#define mu_assert_fread_nil(FILENAME, SZ) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    minipack_fread_nil(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_nil(FILENAME, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_nil(file, &sz); \
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

int test_is_nil() {
    uint8_t data[] = {0x00, 0xC0};
    mu_assert(minipack_is_nil(data+0) == false);
    mu_assert(minipack_is_nil(data+1) == true);
    return 0;
}

int test_unpack_nil() {
    size_t sz;
    uint8_t data[] = {0xC0, 0x00};

    minipack_unpack_nil(data+0, &sz);
    mu_assert(sz == 1);

    minipack_unpack_nil(data+1, &sz);
    mu_assert(sz == 0);

    return 0;
}

int test_pack_nil() {
    size_t sz;
    uint8_t data[] = {0x00};
    minipack_pack_nil(data, &sz);
    mu_assert_mem(data, 1, "\xC0");
    mu_assert_msgpack_nil(1, "\xC0");
    mu_assert(sz == 1);
    return 0;
}

int test_fread_nil() {
    mu_assert_fread_nil("tests/fixtures/nil/nil", 1);
    mu_assert_fread_nil("tests/fixtures/fixnum/127", 0);
    return 0;
}

int test_fwrite_nil() {
    mu_assert_fwrite_nil("tests/fixtures/nil/nil", 1, 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_nil);
    mu_run_test(test_unpack_nil);
    mu_run_test(test_pack_nil);
    mu_run_test(test_fread_nil);
    mu_run_test(test_fwrite_nil);
    return 0;
}

RUN_TESTS()