#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_array32_read_count() {
    mu_assert(minipack_array32_read_count("\xDD\x00\x00\x00\x00") == 0);
    mu_assert(minipack_array32_read_count("\xDD\x00\x00\x00\x05") == 5);
    mu_assert(minipack_array32_read_count("\xDD\x00\x00\x01\x00") == 256);
    mu_assert_msgpack_array(65536, 5, "\xDD\00\x01\00\00");
    return 0;
}

int test_array32_write_hdr() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_array32_write_hdr(data, 0);
    mu_assert_mem(data, 5, "\xDD\x00\x00\x00\x00");

    minipack_array32_write_hdr(data, 5);
    mu_assert_mem(data, 5, "\xDD\x00\x00\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_array32_read_count);
    mu_run_test(test_array32_write_hdr);
    return 0;
}

RUN_TESTS()