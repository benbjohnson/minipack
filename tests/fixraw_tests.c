#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_fixraw_read_length() {
    mu_assert(minipack_fixraw_read_length("\xA0") == 0);
    mu_assert(minipack_fixraw_read_length("\xA5") == 5);
    mu_assert(minipack_fixraw_read_length("\xBF") == 31);
    return 0;
}

int test_fixraw_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_fixraw_write(data, 0, NULL);
    mu_assert_mem(data, 1, "\xA0");

    minipack_fixraw_write(data, 5, "abcde");
    mu_assert_mem(data, 6, "\xA5" "abcde");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_fixraw_read_length);
    mu_run_test(test_fixraw_write);
    return 0;
}

RUN_TESTS()