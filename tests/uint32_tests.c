#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_sizeof_uint32() {
    mu_assert(minipack_sizeof_elem_and_data("\xCE\x00\x00\x00\x02") == 5);
    return 0;
}

int test_unpack_uint32() {
    size_t sz;
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x00\x02", &sz) == 2);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_uint32("\xCE\x00\x00\x40\x23", &sz) == 16419);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_uint32("\xCE\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert_msgpack_uint32(4294967295, 5, "\xCE\xFF\xFF\xFF\xFF");
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_uint32("\xCE\x00\xFF\x00\xFF", &sz) == 16711935);
    mu_assert(sz == 5);
    return 0;
}

int test_pack_uint32() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_uint32(data, 0, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_uint32(data, 2, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x00\x02");
    mu_assert(sz == 5);

    minipack_pack_uint32(data, 16419, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\x00\x40\x23");
    mu_assert(sz == 5);

    minipack_pack_uint32(data, 4294967295, &sz);
    mu_assert_mem(data, 5, "\xCE\xFF\xFF\xFF\xFF");
    mu_assert(sz == 5);

    minipack_pack_uint32(data, 16711935, &sz);
    mu_assert_mem(data, 5, "\xCE\x00\xFF\x00\xFF");
    mu_assert(sz == 5);

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_sizeof_uint32);
    mu_run_test(test_unpack_uint32);
    mu_run_test(test_pack_uint32);
    return 0;
}

RUN_TESTS()