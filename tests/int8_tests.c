#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_int8_read() {
    size_t sz;
    mu_assert(minipack_unpack_int8("\xD0\x00", &sz) == 0);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int8("\xD0\x02", &sz) == 2);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int8("\xD0\xEC", &sz) == -20);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int8("\xD0\x7F", &sz) == 127);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int8("\xD0\x80", &sz) == -128);
    mu_assert_msgpack_int8(-128, 2, "\xD0\x80");
    mu_assert(sz == 2);
    return 0;
}

int test_int8_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00};

    minipack_pack_int8(data, 0, &sz);
    mu_assert_mem(data, 2, "\xD0\x00");
    mu_assert(sz == 2);

    minipack_pack_int8(data, 2, &sz);
    mu_assert_mem(data, 2, "\xD0\x02");
    mu_assert(sz == 2);

    minipack_pack_int8(data, -20, &sz);
    mu_assert_mem(data, 2, "\xD0\xEC");
    mu_assert(sz == 2);

    minipack_pack_int8(data, 127, &sz);
    mu_assert_mem(data, 2, "\xD0\x7F");
    mu_assert(sz == 2);

    minipack_pack_int8(data, -128, &sz);
    mu_assert_mem(data, 2, "\xD0\x80");
    mu_assert(sz == 2);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_int8_read);
    mu_run_test(test_int8_write);
    return 0;
}

RUN_TESTS()