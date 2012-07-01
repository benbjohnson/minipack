#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_double_read() {
    mu_assert(minipack_double_read("\xCB\x00\x00\x00\x00\x00\x00\x00\x00") == 0);
    mu_assert(minipack_double_read("\xCB\x40\x59\x00\x00\x00\x00\x00\x00") == 100);
    mu_assert(minipack_double_read("\xCB\xC0\x59\x00\x00\x00\x00\x00\x00") == -100);
    double value = minipack_double_read("\xCB\x40\x59\x0C\xCC\xCC\xCC\xCC\xCD");      // = 100.2
    mu_assert_mem(&value, 8, "\xCD\xCC\xCC\xCC\xCC\x0C\x59\x40");
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
    mu_run_test(test_double_read);
    mu_run_test(test_double_write);
    return 0;
}

RUN_TESTS()