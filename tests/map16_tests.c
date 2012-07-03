#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_map16_read_count() {
    mu_assert(minipack_map16_read_count("\xDE\x00\x00") == 0);
    mu_assert(minipack_map16_read_count("\xDE\x00\x05") == 5);
    mu_assert(minipack_map16_read_count("\xDE\x01\x00") == 256);
    mu_assert_msgpack_map(256, 3, "\xDE\x01\x00");
    return 0;
}

int test_map16_write_hdr() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_map16_write_hdr(data, 0);
    mu_assert_mem(data, 3, "\xDE\x00\x00");

    minipack_map16_write_hdr(data, 5);
    mu_assert_mem(data, 3, "\xDE\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_map16_read_count);
    mu_run_test(test_map16_write_hdr);
    return 0;
}

RUN_TESTS()