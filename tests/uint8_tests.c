#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint8_read() {
    mu_assert(minipack_uint8_read("\xCC\x00") == 0);
    mu_assert(minipack_uint8_read("\xCC\x02") == 2);
    mu_assert(minipack_uint8_read("\xCC\x14") == 20);
    mu_assert(minipack_uint8_read("\xCC\x7F") == 127);
    mu_assert(minipack_uint8_read("\xCC\xFF") == 255);
    return 0;
}

int test_uint8_write() {
    uint8_t data[] = {0x00, 0x00};

    minipack_uint8_write(data, 0);
    mu_assert_mem(data, 2, "\xCC\x00");

    minipack_uint8_write(data, 2);
    mu_assert_mem(data, 2, "\xCC\x02");

    minipack_uint8_write(data, 20);
    mu_assert_mem(data, 2, "\xCC\x14");

    minipack_uint8_write(data, 127);
    mu_assert_mem(data, 2, "\xCC\x7F");

    minipack_uint8_write(data, 255);
    mu_assert_mem(data, 2, "\xCC\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint8_read);
    mu_run_test(test_uint8_write);
    return 0;
}

RUN_TESTS()