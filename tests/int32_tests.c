#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int32_read() {
    mu_assert(minipack_int32_read("\xD2\x00\x00\x00\x00") == 0);
    mu_assert(minipack_int32_read("\xD2\x00\x00\x00\x02") == 2);
    mu_assert(minipack_int32_read("\xD2\x00\x00\x03\xE8") == 1000);
    mu_assert(minipack_int32_read("\xD2\x7F\xFF\xFF\xFF") == 2147483647);
    mu_assert(minipack_int32_read("\xD2\x80\x00\x00\x00") == -2147483648);
    return 0;
}

int test_int32_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_int32_write(data, 0);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x00");

    minipack_int32_write(data, 2);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x02");

    minipack_int32_write(data, 1000);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x03\xE8");

    minipack_int32_write(data, 2147483647);
    mu_assert_mem(data, 5, "\xD2\x7F\xFF\xFF\xFF");

    minipack_int32_write(data, -2147483648);
    mu_assert_mem(data, 5, "\xD2\x80\x00\x00\x00");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int32_read);
    mu_run_test(test_int32_write);
    return 0;
}

RUN_TESTS()