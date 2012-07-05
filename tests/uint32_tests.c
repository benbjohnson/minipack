#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint32_read() {
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x00\x00") == 0);
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x00\x02") == 2);
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x40\x23") == 16419);
    mu_assert(minipack_unpack_uint32("\xCE\xFF\xFF\xFF\xFF") == 4294967295);
    mu_assert_msgpack_uint32(4294967295, 5, "\xCE\xFF\xFF\xFF\xFF");
    mu_assert(minipack_unpack_uint32("\xCE\x00\xFF\x00\xFF") == 16711935);
    return 0;
}

int test_uint32_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_uint32(data, 0);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x00\x00");

    minipack_pack_uint32(data, 2);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x00\x02");

    minipack_pack_uint32(data, 16419);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x40\x23");

    minipack_pack_uint32(data, 4294967295);
    mu_assert_mem(data, 5, "\xCE\xFF\xFF\xFF\xFF");

    minipack_pack_uint32(data, 16711935);
    mu_assert_mem(data, 5, "\xCE\x00\xFF\x00\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint32_read);
    mu_run_test(test_uint32_write);
    return 0;
}

RUN_TESTS()