#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_bool_read() {
    mu_assert(minipack_bool_read("\xC3") == true);
    mu_assert_msgpack_true(1, "\xC3");
    mu_assert(minipack_bool_read("\xC2") == false);
    mu_assert_msgpack_false(1, "\xC2");
    return 0;
}

int test_bool_write() {
    uint8_t data[] = {0x00};

    minipack_bool_write(data, true);
    mu_assert_mem(data, 1, "\xC3");

    minipack_bool_write(data, false);
    mu_assert_mem(data, 1, "\xC2");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_bool_read);
    mu_run_test(test_bool_write);
    return 0;
}

RUN_TESTS()