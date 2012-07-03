#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_array16_read_count() {
    mu_assert(minipack_array16_read_count("\xDC\x00\x00") == 0);
    mu_assert(minipack_array16_read_count("\xDC\x00\x05") == 5);
    mu_assert(minipack_array16_read_count("\xDC\x01\x00") == 256);
    mu_assert_msgpack_array(256, 3, "\xDC\x01\00");
    return 0;
}

int test_array16_write_header() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_array16_write_header(data, 0);
    mu_assert_mem(data, 3, "\xDC\x00\x00");

    minipack_array16_write_header(data, 5);
    mu_assert_mem(data, 3, "\xDC\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_array16_read_count);
    mu_run_test(test_array16_write_header);
    return 0;
}

RUN_TESTS()