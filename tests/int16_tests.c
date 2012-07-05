#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_int16() {
    size_t sz;
    mu_assert(minipack_unpack_int16("\xD1\x00\x00", &sz) == 0);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int16("\xD1\x00\x02", &sz) == 2);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int16("\xD1\x03\xE8", &sz) == 1000);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int16("\xD1\x7F\xFF", &sz) == 32767);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int16("\xD1\x80\x00", &sz) == -32768);
    mu_assert_msgpack_int16(-32768, 3, "\xD1\x80\x00");
    mu_assert(sz == 3);
    return 0;
}

int test_pack_int16() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00};

    minipack_pack_int16(data, 0, &sz);
    mu_assert_mem(data, 3, "\xD1\x00\x00");
    mu_assert(sz == 3);

    minipack_pack_int16(data, 2, &sz);
    mu_assert_mem(data, 3, "\xD1\x00\x02");
    mu_assert(sz == 3);

    minipack_pack_int16(data, 1000, &sz);
    mu_assert_mem(data, 3, "\xD1\x03\xE8");
    mu_assert(sz == 3);

    minipack_pack_int16(data, 32767, &sz);
    mu_assert_mem(data, 3, "\xD1\x7F\xFF");
    mu_assert(sz == 3);

    minipack_pack_int16(data, 32768, &sz);
    mu_assert_mem(data, 3, "\xD1\x80\x00");
    mu_assert(sz == 3);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_int16);
    mu_run_test(test_pack_int16);
    return 0;
}

RUN_TESTS()