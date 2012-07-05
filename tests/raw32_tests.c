#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_raw32() {
    size_t sz;
    
    mu_assert(minipack_unpack_raw32("\xDB\x00\x00\x00\x00", &sz) == 0);
    mu_assert(sz == 5);
    
    mu_assert(minipack_unpack_raw32("\xDB\x00\x00\x00\x05", &sz) == 5);
    mu_assert(sz == 5);

    mu_assert(minipack_unpack_raw32("\xDB\x01\x00\x00\x00", &sz) == 16777216);
    mu_assert_msgpack_raw(16777216, 5, "\xDB\x01\x00\x00\x00");
    mu_assert(sz == 5);

    return 0;
}

int test_pack_raw32() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_raw32(data, 0, &sz);
    mu_assert_mem(data, 5, "\xDB\x00\x00\x00\x00");

    minipack_pack_raw32(data, 5, &sz);
    mu_assert_mem(data, 5, "\xDB\x00\x00\x00\x05");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_raw32);
    mu_run_test(test_pack_raw32);
    return 0;
}

RUN_TESTS()