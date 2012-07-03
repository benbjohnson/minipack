#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_fixarray_read_count() {
    mu_assert(minipack_fixarray_read_count("\x90") == 0);
    mu_assert(minipack_fixarray_read_count("\x95") == 5);
    mu_assert(minipack_fixarray_read_count("\x9F") == 15);
    return 0;
}

int test_fixarray_write_header() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_fixarray_write_header(data, 0);
    mu_assert_mem(data, 1, "\x90");
    mu_assert_msgpack_array(0, 1, "\x90");

    minipack_fixarray_write_header(data, 5);
    mu_assert_mem(data, 1, "\x95");
    mu_assert_msgpack_array(5, 1, "\x95");

    minipack_fixarray_write_header(data, 15);
    mu_assert_mem(data, 1, "\x9F");
    mu_assert_msgpack_array(15, 1, "\x9F");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_fixarray_read_count);
    mu_run_test(test_fixarray_write_header);
    return 0;
}

RUN_TESTS()