#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_nil() {
    uint8_t data[] = {0x00, 0xC0};
    mu_assert(minipack_is_nil(data+0) == false);
    mu_assert(minipack_is_nil(data+1) == true);
    return 0;
}

int test_unpack_nil() {
    size_t sz;
    uint8_t data[] = {0xC0, 0x00};

    minipack_unpack_nil(data+0, &sz);
    mu_assert(sz == 1);

    minipack_unpack_nil(data+1, &sz);
    mu_assert(sz == 0);

    return 0;
}

int test_pack_nil() {
    size_t sz;
    uint8_t data[] = {0x00};
    minipack_pack_nil(data, &sz);
    mu_assert_mem(data, 1, "\xC0");
    mu_assert_msgpack_nil(1, "\xC0");
    mu_assert(sz == 1);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_nil);
    mu_run_test(test_unpack_nil);
    mu_run_test(test_pack_nil);
    return 0;
}

RUN_TESTS()