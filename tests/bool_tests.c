#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/bool"

#define mu_assert_fread_bool(FILENAME, VALUE, SZ, POS) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    bool value = minipack_fread_bool(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %d", value); \
    mu_assert_with_msg(pos+POS == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_bool(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_bool(file, VALUE, &sz); \
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

int test_is_bool() {
    uint8_t data[] = {0xC2, 0xC3, 0x00};

    mu_assert(minipack_is_bool(data+0) == true);
    mu_assert(minipack_is_bool(data+1) == true);
    mu_assert(minipack_is_bool(data+2) == false);

    mu_assert(minipack_is_true(data+0) == false);
    mu_assert(minipack_is_true(data+1) == true);
    mu_assert(minipack_is_true(data+2) == false);

    mu_assert(minipack_is_false(data+0) == true);
    mu_assert(minipack_is_false(data+1) == false);
    mu_assert(minipack_is_false(data+2) == false);

    return 0;
}

int test_sizeof_bool() {
    mu_assert(minipack_sizeof_elem_and_data("\xC3") == 1);
    mu_assert(minipack_sizeof_elem_and_data("\xC2") == 1);
    return 0;
}

int test_unpack_bool() {
    size_t sz;
    
    mu_assert(minipack_unpack_bool("\xC3", &sz) == true);
    mu_assert_msgpack_true(1, "\xC3");
    mu_assert(sz == 1);
    
    mu_assert(minipack_unpack_bool("\xC2", &sz) == false);
    mu_assert_msgpack_false(1, "\xC2");
    mu_assert(sz == 1);
    
    mu_assert(minipack_unpack_bool("\x00", &sz) == false);
    mu_assert(sz == 0);
    
    return 0;
}

int test_pack_bool() {
    size_t sz;
    uint8_t data[] = {0x00};

    minipack_pack_bool(data, true, &sz);
    mu_assert_mem(data, 1, "\xC3");
    mu_assert(sz == 1);

    minipack_pack_bool(data, false, &sz);
    mu_assert_mem(data, 1, "\xC2");
    mu_assert(sz == 1);

    return 0;
}

int test_fread_bool() {
    mu_assert_fread_bool("tests/fixtures/bool/true", true, 1, 1);
    mu_assert_fread_bool("tests/fixtures/bool/false", false, 1, 1);
    mu_assert_fread_bool("tests/fixtures/fixnum/127", false, 0, 1);
    return 0;
}

int test_fwrite_bool() {
    mu_assert_fwrite_bool("tests/fixtures/bool/true", true, 1, 0);
    mu_assert_fwrite_bool("tests/fixtures/bool/false", false, 1, 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_bool);
    mu_run_test(test_sizeof_bool);
    mu_run_test(test_unpack_bool);
    mu_run_test(test_pack_bool);
    mu_run_test(test_fread_bool);
    mu_run_test(test_fwrite_bool);
    return 0;
}

RUN_TESTS()