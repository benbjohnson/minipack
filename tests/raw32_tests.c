#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_raw32_read_length() {
    mu_assert(minipack_raw32_read_length("\xDB\x00\x00\x00\x00") == 0);
    mu_assert(minipack_raw32_read_length("\xDB\x00\x00\x00\x05") == 5);
    mu_assert(minipack_raw32_read_length("\xDB\x01\x00\x00\x00") == 16777216);
    mu_assert_msgpack_raw_hdr(16777216, 5, "\xDB\x01\x00\x00\x00");
    return 0;
}

int test_raw32_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_raw32_write(data, 0, NULL);
    mu_assert_mem(data, 5, "\xDB\x00\x00\x00\x00");

    minipack_raw32_write(data, 5, "abcde");
    mu_assert_mem(data, 10, "\xDB\x00\x00\x00\x05" "abcde");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_raw32_read_length);
    mu_run_test(test_raw32_write);
    return 0;
}

RUN_TESTS()