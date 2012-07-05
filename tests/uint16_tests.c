#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_uint16() {
    size_t sz;
    mu_assert(minipack_unpack_uint16("\xCD\x00\x00", &sz) == 0);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_uint16("\xCD\x00\x02", &sz) == 2);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_uint16("\xCD\x40\x23", &sz) == 16419);
    mu_assert_msgpack_uint16(16419, 3, "\xCD\x40\x23");
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_uint16("\xCD\xFF\xFF", &sz) == 65535);
    mu_assert_msgpack_uint16(65535, 3, "\xCD\xFF\xFF");
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_uint16("\xCD\x00\xFF", &sz) == 255);
    mu_assert(sz == 3);
    return 0;
}

int test_pack_uint16() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00};

    minipack_pack_uint16(data, 0, &sz);
    mu_assert_mem(data, 3, "\xCD\x00\x00");
    mu_assert(sz == 3);

    minipack_pack_uint16(data, 2, &sz);
    mu_assert_mem(data, 3, "\xCD\x00\x02");
    mu_assert(sz == 3);

    minipack_pack_uint16(data, 16419, &sz);
    mu_assert_mem(data, 3, "\xCD\x40\x23");
    mu_assert(sz == 3);

    minipack_pack_uint16(data, 65535, &sz);
    mu_assert_mem(data, 3, "\xCD\xFF\xFF");
    mu_assert(sz == 3);

    minipack_pack_uint16(data, 255, &sz);
    mu_assert_mem(data, 3, "\xCD\x00\xFF");
    mu_assert(sz == 3);

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_uint16);
    mu_run_test(test_pack_uint16);
    return 0;
}

RUN_TESTS()