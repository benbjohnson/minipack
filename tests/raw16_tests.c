#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_raw16_read() {
    mu_assert(minipack_unpack_raw16("\xDA\x00\x00") == 0);
    mu_assert(minipack_unpack_raw16("\xDA\x00\x05") == 5);
    mu_assert(minipack_unpack_raw16("\xDA\x01\x00") == 256);
    mu_assert_msgpack_raw(256, 3, "\xDA\x01\x00");
    return 0;
}

int test_raw16_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_raw16(data, 0, NULL);
    mu_assert_mem(data, 3, "\xDA\x00\x00");

    minipack_pack_raw16(data, 5, "abcde");
    mu_assert_mem(data, 8, "\xDA\x00\x05" "abcde");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_raw16_read);
    mu_run_test(test_raw16_write);
    return 0;
}

RUN_TESTS()