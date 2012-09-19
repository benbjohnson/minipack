#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_sizeof_int64() {
    mu_assert(minipack_sizeof_elem_and_data("\xD3\x00\x00\x00\x00\x00\x00\x03\xE8") == 9);
    return 0;
}

int test_unpack_int64() {
    size_t sz;
    mu_assert(minipack_unpack_int64("\xD3\x00\x00\x00\x00\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_int64("\xD3\x00\x00\x00\x00\x00\x00\x00\x02", &sz) == 2);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_int64("\xD3\x00\x00\x00\x00\x00\x00\x03\xE8", &sz) == 1000);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_int64("\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF", &sz) == 9223372036854775807LL);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_int64("\xD3\x80\x00\x00\x00\x00\x00\x00\x01", &sz) == -9223372036854775807LL);
    mu_assert_msgpack_int64(-9223372036854775807LL, 9, "\xD3\x80\x00\x00\x00\x00\x00\x00\x01");
    mu_assert(sz == 9);
    return 0;
}

int test_pack_int64() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_int64(data, 0, &sz);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    minipack_pack_int64(data, 2, &sz);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x00\x02");
    mu_assert(sz == 9);

    minipack_pack_int64(data, 1000, &sz);
    mu_assert_mem(data, 9, "\xD3\x00\x00\x00\x00\x00\x00\x03\xE8");
    mu_assert(sz == 9);

    minipack_pack_int64(data, 9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF");
    mu_assert(sz == 9);

    minipack_pack_int64(data, -9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x80\x00\x00\x00\x00\x00\x00\x01");
    mu_assert(sz == 9);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_sizeof_int64);
    mu_run_test(test_unpack_int64);
    mu_run_test(test_pack_int64);
    return 0;
}

RUN_TESTS()