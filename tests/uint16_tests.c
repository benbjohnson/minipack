#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint16_read() {
    mu_assert(minipack_unpack_uint16("\xCD\x00\x00") == 0);
    mu_assert(minipack_unpack_uint16("\xCD\x00\x02") == 2);
    mu_assert(minipack_unpack_uint16("\xCD\x40\x23") == 16419);
    mu_assert_msgpack_uint16(16419, 3, "\xCD\x40\x23");
    mu_assert(minipack_unpack_uint16("\xCD\xFF\xFF") == 65535);
    mu_assert_msgpack_uint16(65535, 3, "\xCD\xFF\xFF");
    mu_assert(minipack_unpack_uint16("\xCD\x00\xFF") == 255);
    return 0;
}

int test_uint16_write() {
    uint8_t data[] = {0x00, 0x00, 0x00};

    minipack_pack_uint16(data, 0);
    mu_assert_mem(data, 3, "\xCD\x00\x00");

    minipack_pack_uint16(data, 2);
    mu_assert_mem(data, 3, "\xCD\x00\x02");

    minipack_pack_uint16(data, 16419);
    mu_assert_mem(data, 3, "\xCD\x40\x23");

    minipack_pack_uint16(data, 65535);
    mu_assert_mem(data, 3, "\xCD\xFF\xFF");

    minipack_pack_uint16(data, 255);
    mu_assert_mem(data, 3, "\xCD\x00\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint16_read);
    mu_run_test(test_uint16_write);
    return 0;
}

RUN_TESTS()