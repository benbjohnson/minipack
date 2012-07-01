#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_float_read() {
    mu_assert(minipack_float_read("\xCA\x00\x00\x00\x00") == 0);
    mu_assert(minipack_float_read("\xCA\x42\xC8\x00\x00") == 100);
    mu_assert(minipack_float_read("\xCA\xC2\xC8\x00\x00") == -100);
    float value = minipack_float_read("\xCA\x42\xC8\x66\x66");      // = 100.2
    mu_assert_mem(&value, 4, "\x66\x66\xC8\x42");
    return 0;
}

int test_float_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_float_write(data, 0);
    mu_assert_mem(data, 5, "\xCA\x00\x00\x00\x00");

    minipack_float_write(data, 100);
    mu_assert_mem(data, 5, "\xCA\x42\xC8\x00\x00");

    minipack_float_write(data, -100);
    mu_assert_mem(data, 5, "\xCA\xC2\xC8\x00\x00");

    minipack_float_write(data, 100.2);
    mu_assert_mem(data, 5, "\xCA\x42\xC8\x66\x66");

    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_float_read);
    mu_run_test(test_float_write);
    return 0;
}

RUN_TESTS()