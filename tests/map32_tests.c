#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_map32_read() {
    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x00\x00") == 0);
    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x00\x05") == 5);
    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x01\x00") == 256);
    mu_assert_msgpack_map(65536, 5, "\xDF\x00\x01\x00\x00");
    return 0;
}

int test_map32_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_map32(data, 0);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x00");

    minipack_pack_map32(data, 5);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_map32_read);
    mu_run_test(test_map32_write);
    return 0;
}

RUN_TESTS()