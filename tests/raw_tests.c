#include <stdlib.h>
#include <string.h>
#include <minipack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

void init_ptr(void **ptr, uint32_t sz, uint32_t byte)
{
    if(*ptr) free(*ptr);
    *ptr = malloc(sz);
    memset(*ptr, sz, byte);
}

int test_is_raw() {
    mu_assert(minipack_is_raw("\xA0") == true);
    mu_assert(minipack_is_raw("\xBF") == true);
    mu_assert(minipack_is_raw("\xBF") == true);
    mu_assert(minipack_is_raw("\xDA\x00\x90") == true);
    mu_assert(minipack_is_raw("\xDB\x00\x90") == true);

    mu_assert(minipack_is_raw("\x00") == false);
    mu_assert(minipack_is_raw("\xF0") == false);
    return 0;
}

int test_raw_sizeof() {
    // Fix raw
    mu_assert(minipack_raw_sizeof(0) == 1);
    mu_assert(minipack_raw_sizeof(31) == 1);

    // raw16
    mu_assert(minipack_raw_sizeof(32) == 3);
    mu_assert(minipack_raw_sizeof(65535) == 3);

    // raw32
    mu_assert(minipack_raw_sizeof(65536) == 5);
    mu_assert(minipack_raw_sizeof(4294967295) == 5);

    return 0;
}

int test_unpack_raw() {
    size_t sz;

    // Fix raw
    mu_assert(minipack_unpack_raw("\xA0", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_raw("\xBF", &sz) == 31);
    mu_assert(sz == 1);
    
    // raw 16
    mu_assert(minipack_unpack_raw("\xDA\x00\x20", &sz) == 32);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_raw("\xDA\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);
    
    // raw 32
    mu_assert(minipack_unpack_raw("\xDB\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_raw("\xDB\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);
    
    return 0;
}

int test_pack_raw() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Fix raw
    minipack_pack_raw(data, 0, &sz);
    mu_assert_mem(data, 1, "\xA0");
    mu_assert(sz == 1);

    minipack_pack_raw(data, 31, &sz);
    mu_assert_mem(data, 1, "\xBF");
    mu_assert(sz == 1);

    // raw16
    minipack_pack_raw(data, 32, &sz);
    mu_assert_mem(data, 3, "\xDA\x00\x20");
    mu_assert(sz == 3);

    minipack_pack_raw(data, 65535, &sz);
    mu_assert_mem(data, 3, "\xDA\xFF\xFF");
    mu_assert(sz == 3);

    // raw32
    minipack_pack_raw(data, 65536, &sz);
    mu_assert_mem(data, 5, "\xDB\x00\x01\x00\x00");
    mu_assert(sz == 5);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_raw);
    mu_run_test(test_raw_sizeof);
    mu_run_test(test_unpack_raw);
    mu_run_test(test_pack_raw);
    return 0;
}

RUN_TESTS()