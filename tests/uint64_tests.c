#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint64_read() {
    size_t sz;
    mu_assert(minipack_unpack_uint64("\xCF\x00\x00\x00\x00\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_uint64("\xCF\x00\x00\x00\x00\x00\x00\x00\x02", &sz) == 2);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_uint64("\xCF\x00\x00\x00\x00\x00\x00\x40\x23", &sz) == 16419);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_uint64("\xCF\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF", &sz) == 281474976710655LL);
    mu_assert_msgpack_uint64(281474976710655LL, 9, "\xCF\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF");
    mu_assert(sz == 9);
    return 0;
}

int test_uint64_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_uint64(data, 0, &sz);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x00\x00");
    mu_assert(sz == 9);

    minipack_pack_uint64(data, 2, &sz);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x00\x02");
    mu_assert(sz == 9);

    minipack_pack_uint64(data, 16419, &sz);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x40\x23");
    mu_assert(sz == 9);

    minipack_pack_uint64(data, 281474976710655LL, &sz);
    mu_assert_mem(data, 9, "\xCF\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF");
    mu_assert(sz == 9);

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint64_read);
    mu_run_test(test_uint64_write);
    return 0;
}

RUN_TESTS()