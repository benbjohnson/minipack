#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint8_read() {
    mu_assert(minipack_unpack_uint8("\xCC\x00") == 0);
    mu_assert(minipack_unpack_uint8("\xCC\x02") == 2);
    mu_assert(minipack_unpack_uint8("\xCC\x14") == 20);
    mu_assert(minipack_unpack_uint8("\xCC\x7F") == 127);
    mu_assert_msgpack_uint8(128, 2, "\xCC\x80");
    mu_assert(minipack_unpack_uint8("\xCC\xFF") == 255);
    mu_assert_msgpack_uint8(255, 2, "\xCC\xFF");
    return 0;
}

int test_uint8_write() {
    uint8_t data[] = {0x00, 0x00};

    minipack_pack_uint8(data, 0);
    mu_assert_mem(data, 2, "\xCC\x00");

    minipack_pack_uint8(data, 2);
    mu_assert_mem(data, 2, "\xCC\x02");

    minipack_pack_uint8(data, 20);
    mu_assert_mem(data, 2, "\xCC\x14");

    minipack_pack_uint8(data, 127);
    mu_assert_mem(data, 2, "\xCC\x7F");

    minipack_pack_uint8(data, 255);
    mu_assert_mem(data, 2, "\xCC\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint8_read);
    mu_run_test(test_uint8_write);
    return 0;
}

RUN_TESTS()