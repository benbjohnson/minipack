#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint16_read() {
    mu_assert(minipack_uint16_read("\xCD\x00\x00") == 0);
    mu_assert(minipack_uint16_read("\xCD\x00\x02") == 2);
    mu_assert(minipack_uint16_read("\xCD\x40\x23") == 16419);
    mu_assert(minipack_uint16_read("\xCD\xFF\xFF") == 65535);
    mu_assert(minipack_uint16_read("\xCD\x00\xFF") == 255);
    return 0;
}

int test_uint16_write() {
    uint8_t data[] = {0x00, 0x00, 0x00};

    minipack_uint16_write(data, 0);
    mu_assert_mem(data, 3, "\xCD\x00\x00");

    minipack_uint16_write(data, 2);
    mu_assert_mem(data, 3, "\xCD\x00\x02");

    minipack_uint16_write(data, 16419);
    mu_assert_mem(data, 3, "\xCD\x40\x23");

    minipack_uint16_write(data, 65535);
    mu_assert_mem(data, 3, "\xCD\xFF\xFF");

    minipack_uint16_write(data, 255);
    mu_assert_mem(data, 3, "\xCD\x00\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint16_read);
    mu_run_test(test_uint16_write);
    return 0;
}

RUN_TESTS()