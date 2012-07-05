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
    size_t sz;
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x00\x02", &sz) == 2);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int32("\xD2\x00\x00\x03\xE8", &sz) == 1000);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int32("\xD2\x7F\xFF\xFF\xFF", &sz) == 2147483647);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int32("\xD2\x80\x00\x00\x00", &sz) == -2147483648);
    mu_assert_msgpack_int32(-2147483648, 5, "\xD2\x80\x00\x00\x00");
    mu_assert(sz == 5);
    return 0;
}

int test_int32_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_int32(data, 0, &sz);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_int32(data, 2, &sz);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x00\x02");
    mu_assert(sz == 5);

    minipack_pack_int32(data, 1000, &sz);
    mu_assert_mem(data, 5, "\xD2\x00\x00\x03\xE8");
    mu_assert(sz == 5);

    minipack_pack_int32(data, 2147483647, &sz);
    mu_assert_mem(data, 5, "\xD2\x7F\xFF\xFF\xFF");
    mu_assert(sz == 5);

    minipack_pack_int32(data, -2147483648, &sz);
    mu_assert_mem(data, 5, "\xD2\x80\x00\x00\x00");
    mu_assert(sz == 5);

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