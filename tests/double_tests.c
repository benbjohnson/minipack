#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_double() {
    mu_assert(minipack_is_double("\xCB\x00\x00\x00\x00\x00\x00\x00\x00") == true);
    mu_assert(minipack_is_double("\xCA\x00\x00\x00\x00\x00\x00\x00\x00") == false);
    return 0;
}

int test_double_read() {
    mu_assert(minipack_double_read("\xCB\x00\x00\x00\x00\x00\x00\x00\x00") == 0);
    mu_assert_msgpack_double(0, 9, "\xCB\x00\x00\x00\x00\x00\x00\x00\x00");
    mu_assert(minipack_double_read("\xCB\x40\x59\x00\x00\x00\x00\x00\x00") == 100);
    mu_assert_msgpack_double(100, 9, "\xCB\x40\x59\x00\x00\x00\x00\x00\x00");
    mu_assert(minipack_double_read("\xCB\xC0\x59\x00\x00\x00\x00\x00\x00") == -100);
    mu_assert_msgpack_double(-100, 9, "\xCB\xC0\x59\x00\x00\x00\x00\x00\x00");
    double value = minipack_double_read("\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");      // = 100.2
    mu_assert_mem(&value, 8, "\xCD\xCC\xCC\xCC\xCC\x0C\x59\x40");
    mu_assert_msgpack_double(100.2, 9, "\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");
    return 0;
}

int test_double_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_double_write(data, 0);
    mu_assert_mem(data, 9, "\xCB\x00\x00\x00\x00\x00\x00\x00\x00");

    minipack_double_write(data, 100);
    mu_assert_mem(data, 9, "\xCB\x40\x59\x00\x00\x00\x00\x00\x00");

    minipack_double_write(data, -100);
    mu_assert_mem(data, 9, "\xCB\xC0\x59\x00\x00\x00\x00\x00\x00");

    minipack_double_write(data, 100.2);
    mu_assert_mem(data, 9, "\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");

    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_double);
    mu_run_test(test_double_read);
    mu_run_test(test_double_write);
    return 0;
}

RUN_TESTS()