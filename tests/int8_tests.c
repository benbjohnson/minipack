#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int8_read() {
    mu_assert(minipack_int8_read("\xD0\x00") == 0);
    mu_assert(minipack_int8_read("\xD0\x02") == 2);
    mu_assert(minipack_int8_read("\xD0\xEC") == -20);
    mu_assert(minipack_int8_read("\xD0\x7F") == 127);
    mu_assert(minipack_int8_read("\xD0\x80") == -128);
    mu_assert_msgpack_int8(-128, 2, "\xD0\x80");
    return 0;
}

int test_int8_write() {
    uint8_t data[] = {0x00, 0x00};

    minipack_int8_write(data, 0);
    mu_assert_mem(data, 2, "\xD0\x00");

    minipack_int8_write(data, 2);
    mu_assert_mem(data, 2, "\xD0\x02");

    minipack_int8_write(data, -20);
    mu_assert_mem(data, 2, "\xD0\xEC");

    minipack_int8_write(data, 127);
    mu_assert_mem(data, 2, "\xD0\x7F");

    minipack_int8_write(data, -128);
    mu_assert_mem(data, 2, "\xD0\x80");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int8_read);
    mu_run_test(test_int8_write);
    return 0;
}

RUN_TESTS()