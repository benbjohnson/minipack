#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int16_read() {
    mu_assert(minipack_int16_read("\xD1\x00\x00") == 0);
    mu_assert(minipack_int16_read("\xD1\x00\x02") == 2);
    mu_assert(minipack_int16_read("\xD1\x03\xE8") == 1000);
    mu_assert(minipack_int16_read("\xD1\x7F\xFF") == 32767);
    mu_assert(minipack_int16_read("\xD1\x80\x00") == -32768);
    return 0;
}

int test_int16_write() {
    uint8_t data[] = {0x00, 0x00, 0x00};

    minipack_int16_write(data, 0);
    mu_assert_mem(data, 3, "\xD1\x00\x00");

    minipack_int16_write(data, 2);
    mu_assert_mem(data, 3, "\xD1\x00\x02");

    minipack_int16_write(data, 1000);
    mu_assert_mem(data, 3, "\xD1\x03\xE8");

    minipack_int16_write(data, 32767);
    mu_assert_mem(data, 3, "\xD1\x7F\xFF");

    minipack_int16_write(data, 32768);
    mu_assert_mem(data, 3, "\xD1\x80\x00");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int16_read);
    mu_run_test(test_int16_write);
    return 0;
}

RUN_TESTS()