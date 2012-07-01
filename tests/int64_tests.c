#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int64_read() {
    mu_assert(mpack_int64_read("\xD3\x00\x00\x00\x00\x00\x00\x00\x00") == 0);
    mu_assert(mpack_int64_read("\xD3\x00\x00\x00\x00\x00\x00\x00\x02") == 2);
    mu_assert(mpack_int64_read("\xD3\x00\x00\x00\x00\x00\x00\x03\xE8") == 1000);
    mu_assert(mpack_int64_read("\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF") == 9223372036854775807LL);
    mu_assert(mpack_int64_read("\xD3\x80\x00\x00\x00\x00\x00\x00\x01") == -9223372036854775807LL);
    return 0;
}

int test_int64_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    mpack_int64_write(data, 0);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x00\x00");

    mpack_int64_write(data, 2);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x00\x02");

    mpack_int64_write(data, 1000);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x03\xE8");

    mpack_int64_write(data, 9223372036854775807LL);
    mu_assert_mem(data, 9, "\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF");

    mpack_int64_write(data, -9223372036854775807LL);
    mu_assert_mem(data, 9, "\xD3\x80\x00\x00\x00\x00\x00\x00\x01");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int64_read);
    mu_run_test(test_int64_write);
    return 0;
}

RUN_TESTS()