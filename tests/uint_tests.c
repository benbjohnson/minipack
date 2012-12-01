#include "minunit.h"
#include <minipack.h>

#include "memdump.h"


//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/uint"

#define mu_assert_fread_uint(FILENAME, VALUE, SZ) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    uint64_t value = minipack_fread_uint(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %" PRIu64, value); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_uint(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_uint(file, VALUE, &sz); \
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

int test_unpack_uint() {
    size_t sz;

    // Fixnum
    mu_assert(minipack_unpack_uint("\x00", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_uint("\x7f", &sz) == 127);
    mu_assert(sz == 1);

    // 8-bit
    mu_assert(minipack_unpack_uint("\xCC\x80", &sz) == 128);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_uint("\xCC\xFF", &sz) == 255);
    mu_assert(sz == 2);

    // 16-bit
    mu_assert(minipack_unpack_uint("\xCD\x01\x00", &sz) == 256);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_uint("\xCD\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // 32-bit
    mu_assert(minipack_unpack_uint("\xCE\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_uint("\xCE\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    // 64-bit
    mu_assert(minipack_unpack_uint("\xCF\x00\x00\x00\x01\x00\x00\x00\x00", &sz) == 4294967296);
    mu_assert(sz == 9);

    return 0;
}

int test_pack_uint() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Fixnum
    minipack_pack_uint(data, 0, &sz);
    mu_assert_mem(data, 1, "\x00");
    mu_assert(sz == 1);
    minipack_pack_uint(data, 127, &sz);
    mu_assert_mem(data, 1, "\x7F");
    mu_assert(sz == 1);

    // 8-bit
    minipack_pack_uint(data, 128, &sz);
    mu_assert_mem(data, 2, "\xCC\x80");
    mu_assert(sz == 2);
    minipack_pack_uint(data, 255, &sz);
    mu_assert_mem(data, 2, "\xCC\xFF");
    mu_assert(sz == 2);

    // 16-bit
    minipack_pack_uint(data, 256, &sz);
    mu_assert_mem(data, 3, "\xCD\x01\x00");
    mu_assert(sz == 3);
    minipack_pack_uint(data, 65535, &sz);
    mu_assert_mem(data, 3, "\xCD\xFF\xFF");
    mu_assert(sz == 3);

    // 32-bit
    minipack_pack_uint(data, 65536, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\x01\x00\x00");
    mu_assert(sz == 5);
    minipack_pack_uint(data, 4294967295, &sz);
    mu_assert_mem(data, 5, "\xCE\xFF\xFF\xFF\xFF");
    mu_assert(sz == 5);

    // 64-bit
    minipack_pack_uint(data, 4294967296, &sz);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x01\x00\x00\x00\x00");
    mu_assert(sz == 9);

    return 0;
}

int test_fread_uint() {
    // Fixnum
    mu_assert_fread_uint("tests/fixtures/fixnum/0", 0, 1);
    mu_assert_fread_uint("tests/fixtures/fixnum/127", 127, 1);

    // 8-bit
    mu_assert_fread_uint("tests/fixtures/uint/128", 128, 2);
    mu_assert_fread_uint("tests/fixtures/uint/255", 255, 2);

    // 16-bit
    mu_assert_fread_uint("tests/fixtures/uint/256", 256, 3);
    mu_assert_fread_uint("tests/fixtures/uint/65535", 65535, 3);

    // 32-bit
    mu_assert_fread_uint("tests/fixtures/uint/65536", 65536, 5);
    mu_assert_fread_uint("tests/fixtures/uint/4294967295", 4294967295, 5);

    // 64-bit
    mu_assert_fread_uint("tests/fixtures/uint/4294967296", 4294967296, 9);

    // ERR: Negative fixnum
    mu_assert_fread_uint("tests/fixtures/fixnum/-1", 0, 0);

    // ERR: Signed ints
    mu_assert_fread_uint("tests/fixtures/fixnum/-1", 0, 0);
    mu_assert_fread_uint("tests/fixtures/fixnum/-32", 0, 0);
    mu_assert_fread_uint("tests/fixtures/int/127", 0, 0);
    mu_assert_fread_uint("tests/fixtures/int/-128", 0, 0);

    return 0;
}

int test_fwrite_uint() {
    // Fixnum
    mu_assert_fwrite_uint("tests/fixtures/fixnum/0", 0, 1, 0);
    mu_assert_fwrite_uint("tests/fixtures/fixnum/127", 127, 1, 0);


    // 8-bit
    mu_assert_fwrite_uint("tests/fixtures/uint/128", 128, 2, 0);
    mu_assert_fwrite_uint("tests/fixtures/uint/255", 255, 2, 0);

    // 16-bit
    mu_assert_fwrite_uint("tests/fixtures/uint/256", 256, 3, 0);
    mu_assert_fwrite_uint("tests/fixtures/uint/65535", 65535, 3, 0);

    // 32-bit
    mu_assert_fwrite_uint("tests/fixtures/uint/65536", 65536, 5, 0);
    mu_assert_fwrite_uint("tests/fixtures/uint/4294967295", 4294967295, 5, 0);

    // 64-bit
    mu_assert_fwrite_uint("tests/fixtures/uint/4294967296", 4294967296, 9, 0);

    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_uint);
    mu_run_test(test_pack_uint);
    mu_run_test(test_fread_uint);
    mu_run_test(test_fwrite_uint);
    return 0;
}

RUN_TESTS()