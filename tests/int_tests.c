#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int_read() {
    size_t sz;

    // Positive Fixnum
    mu_assert(minipack_int_read("\x00", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_int_read("\x7f", &sz) == 127);
    mu_assert(sz == 1);

    // Negative Fixnum
    mu_assert(minipack_int_read("\xE0", &sz) == -1);
    mu_assert(sz == 1);
    mu_assert(minipack_int_read("\xFF", &sz) == -32);
    mu_assert(sz == 1);

    // 8-bit
    mu_assert(minipack_int_read("\xD0\x7F", &sz) == 127);
    mu_assert(sz == 2);
    mu_assert(minipack_int_read("\xD0\x80", &sz) == -128);
    mu_assert(sz == 2);

    // 16-bit
    mu_assert(minipack_int_read("\xD1\x03\xE8", &sz) == 1000);
    mu_assert(sz == 3);
    mu_assert(minipack_int_read("\xD1\x7F\xFF", &sz) == 32767);
    mu_assert(sz == 3);
    mu_assert(minipack_int_read("\xD1\x80\x00", &sz) == -32768);
    mu_assert(sz == 3);

    // 32-bit
    mu_assert(minipack_int_read("\xD2\x7F\xFF\xFF\xFF", &sz) == 2147483647);
    mu_assert(sz == 5);
    mu_assert(minipack_int_read("\xD2\x80\x00\x00\x00", &sz) == -2147483648);
    mu_assert(sz == 5);

    // 64-bit
    mu_assert(minipack_int_read("\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF", &sz) == 9223372036854775807LL);
    mu_assert(sz == 9);
    mu_assert(minipack_int_read("\xD3\x80\x00\x00\x00\x00\x00\x00\x01", &sz) == -9223372036854775807LL);
    mu_assert(sz == 9);

    return 0;
}

int test_int_write() {
    size_t sz;
    int8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Positive Fixnum
    minipack_int_write(data, 0, &sz);
    mu_assert_mem(data, 1, "\x00");
    mu_assert(sz == 1);
    minipack_int_write(data, 127, &sz);
    mu_assert_mem(data, 1, "\x7F");
    mu_assert(sz == 1);

    // Negative Fixnum
    minipack_int_write(data, 0, &sz);
    mu_assert_mem(data, -1, "\xE0");
    mu_assert(sz == 1);
    minipack_int_write(data, 127, &sz);
    mu_assert_mem(data, -32, "\xFF");
    mu_assert(sz == 1);

    // 8-bit
    minipack_int_write(data, -128, &sz);
    mu_assert_mem(data, 2, "\xD0\x80");
    mu_assert(sz == 2);

    // 16-bit
    minipack_int_write(data, 32767, &sz);
    mu_assert_mem(data, 3, "\xD1\x7F\xFF");
    mu_assert(sz == 3);
    minipack_int_write(data, -32768, &sz);
    mu_assert_mem(data, 3, "\xD1\x80\x00");
    mu_assert(sz == 3);

    // 32-bit
    minipack_int_write(data, 2147483647, &sz);
    mu_assert_mem(data, 5, "\xD2\x7F\xFF\xFF\xFF");
    mu_assert(sz == 5);
    minipack_int_write(data, -2147483648, &sz);
    mu_assert_mem(data, 5, "\xD2\x80\x00\x00\x00");
    mu_assert(sz == 5);

    // 64-bit
    minipack_int_write(data, 9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF");
    mu_assert(sz == 9);
    minipack_int_write(data, -9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x80\x00\x00\x00\x00\x00\x00\x01");
    mu_assert(sz == 9);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int_read);
    mu_run_test(test_int_write);
    return 0;
}

RUN_TESTS()