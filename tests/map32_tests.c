#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_map32_read_count() {
    mu_assert(minipack_map32_read_count("\xDF\x00\x00\x00\x00") == 0);
    mu_assert(minipack_map32_read_count("\xDF\x00\x00\x00\x05") == 5);
    mu_assert(minipack_map32_read_count("\xDF\x00\x00\x01\x00") == 256);
    mu_assert_msgpack_map(65536, 5, "\xDF\x00\x01\x00\x00");
    return 0;
}

int test_map32_write_header() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_map32_write_header(data, 0);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x00");

    minipack_map32_write_header(data, 5);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_map32_read_count);
    mu_run_test(test_map32_write_header);
    return 0;
}

RUN_TESTS()