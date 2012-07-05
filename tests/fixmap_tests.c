#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_fixmap() {
    size_t sz;
    
    mu_assert(minipack_unpack_fixmap("\x80", &sz) == 0);
    mu_assert_msgpack_map(0, 1, "\x80");
    mu_assert(sz == 1);

    mu_assert(minipack_unpack_fixmap("\x85", &sz) == 5);
    mu_assert_msgpack_map(5, 1, "\x85");
    mu_assert(sz == 1);

    mu_assert(minipack_unpack_fixmap("\x8F", &sz) == 15);
    mu_assert_msgpack_map(15, 1, "\x8F");
    mu_assert(sz == 1);

    return 0;
}

int test_pack_fixmap() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_fixmap(data, 0, &sz);
    mu_assert_mem(data, 1, "\x80");
    mu_assert(sz == 1);

    minipack_pack_fixmap(data, 5, &sz);
    mu_assert_mem(data, 1, "\x85");
    mu_assert(sz == 1);

    minipack_pack_fixmap(data, 15, &sz);
    mu_assert_mem(data, 1, "\x8F");
    mu_assert(sz == 1);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_fixmap);
    mu_run_test(test_pack_fixmap);
    return 0;
}

RUN_TESTS()