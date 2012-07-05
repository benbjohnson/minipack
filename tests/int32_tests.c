#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int32_read() {
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x00\x00") == 0);
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x00\x02") == 2);
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x03\xE8") == 1000);
    mu_assert(minipack_unpack_int32("\xD2\x7F\xFF\xFF\xFF") == 2147483647);
    mu_assert(minipack_unpack_int32("\xD2\x80\x00\x00\x00") == -2147483648);
    mu_assert_msgpack_int32(-2147483648, 5, "\xD2\x80\x00\x00\x00");
    return 0;
}

int test_int32_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_int32(data, 0);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x00");

    minipack_pack_int32(data, 2);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x02");

    minipack_pack_int32(data, 1000);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x03\xE8");

    minipack_pack_int32(data, 2147483647);
    mu_assert_mem(data, 5, "\xD2\x7F\xFF\xFF\xFF");

    minipack_pack_int32(data, -2147483648);
    mu_assert_mem(data, 5, "\xD2\x80\x00\x00\x00");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int32_read);
    mu_run_test(test_int32_write);
    return 0;
}

RUN_TESTS()