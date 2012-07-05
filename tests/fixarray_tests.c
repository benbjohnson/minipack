#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_fixarray() {
    size_t sz;

    mu_assert(minipack_unpack_fixarray("\x90", &sz) == 0);
    mu_assert(sz == 1);

    mu_assert(minipack_unpack_fixarray("\x95", &sz) == 5);
    mu_assert(sz == 1);

    mu_assert(minipack_unpack_fixarray("\x9F", &sz) == 15);
    mu_assert(sz == 1);

    return 0;
}

int test_pack_fixarray() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_pack_fixarray(data, 0, &sz);
    mu_assert_mem(data, 1, "\x90");
    mu_assert_msgpack_array(0, 1, "\x90");
    mu_assert(sz == 1);

    minipack_pack_fixarray(data, 5, &sz);
    mu_assert_mem(data, 1, "\x95");
    mu_assert_msgpack_array(5, 1, "\x95");
    mu_assert(sz == 1);

    minipack_pack_fixarray(data, 15, &sz);
    mu_assert_mem(data, 1, "\x9F");
    mu_assert_msgpack_array(15, 1, "\x9F");
    mu_assert(sz == 1);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_fixarray);
    mu_run_test(test_pack_fixarray);
    return 0;
}

RUN_TESTS()