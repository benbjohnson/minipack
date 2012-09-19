#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_sizeof_map32() {
    mu_assert(minipack_sizeof_elem_and_data("\xDF\x00\x00\x00\x05") == 0);
    return 0;
}

int test_unpack_map32() {
    size_t sz;
    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 5);

    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x00\x05", &sz) == 5);
    mu_assert(sz == 5);

    mu_assert(minipack_unpack_map32("\xDF\x00\x00\x01\x00", &sz) == 256);
    mu_assert_msgpack_map(65536, 5, "\xDF\x00\x01\x00\x00");
    mu_assert(sz == 5);

    return 0;
}

int test_pack_map32() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_map32(data, 0, &sz);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x00");
    mu_assert(sz == 5);

    minipack_pack_map32(data, 5, &sz);
    mu_assert_mem(data, 5, "\xDF\x00\x00\x00\x05");
    mu_assert(sz == 5);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_sizeof_map32);
    mu_run_test(test_unpack_map32);
    mu_run_test(test_pack_map32);
    return 0;
}

RUN_TESTS()