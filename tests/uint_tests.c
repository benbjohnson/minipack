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
    mu_assert(minipack_uint_read("\x00", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_uint_read("\x7f", &sz) == 127);
    mu_assert(sz == 1);

    // 8-bit
    mu_assert(minipack_uint_read("\xCC\x80", &sz) == 128);
    mu_assert(sz == 2);
    mu_assert(minipack_uint_read("\xCC\xFF", &sz) == 255);
    mu_assert(sz == 2);

    // 16-bit
    mu_assert(minipack_uint_read("\xCD\x01\x00", &sz) == 256);
    mu_assert(sz == 3);
    mu_assert(minipack_uint_read("\xCD\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // 32-bit
    mu_assert(minipack_uint_read("\xCE\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_uint_read("\xCE\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    // 64-bit
    mu_assert(minipack_uint_read("\xCF\x00\x00\x00\x01\x00\x00\x00\x00", &sz) == 4294967296);
    mu_assert(sz == 9);

    return 0;
}

int test_uint_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Fixnum
    minipack_uint_write(data, 0, &sz);
    mu_assert_mem(data, 1, "\x00");
    mu_assert(sz == 1);
    minipack_uint_write(data, 127, &sz);
    mu_assert_mem(data, 1, "\x7F");
    mu_assert(sz == 1);

    // 8-bit
    minipack_uint_write(data, 128, &sz);
    mu_assert_mem(data, 2, "\xCC\x80");
    mu_assert(sz == 2);
    minipack_uint_write(data, 255, &sz);
    mu_assert_mem(data, 2, "\xCC\xFF");
    mu_assert(sz == 2);

    // 16-bit
    minipack_uint_write(data, 256, &sz);
    mu_assert_mem(data, 3, "\xCD\x01\x00");
    mu_assert(sz == 3);
    minipack_uint_write(data, 65535, &sz);
    mu_assert_mem(data, 3, "\xCD\xFF\xFF");
    mu_assert(sz == 3);

    // 32-bit
    minipack_uint_write(data, 65536, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\x01\x00\x00");
    mu_assert(sz == 5);
    minipack_uint_write(data, 4294967295, &sz);
    mu_assert_mem(data, 5, "\xCE\xFF\xFF\xFF\xFF");
    mu_assert(sz == 5);

    // 64-bit
    minipack_uint_write(data, 4294967296, &sz);
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