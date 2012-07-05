#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint_read() {
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

int test_uint_write() {
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


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint_read);
    mu_run_test(test_uint_write);
    return 0;
}

RUN_TESTS()