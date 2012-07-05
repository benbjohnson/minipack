#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_bool() {
    uint8_t data[] = {0xC2, 0xC3, 0x00};

    mu_assert(minipack_is_bool(data+0) == true);
    mu_assert(minipack_is_bool(data+1) == true);
    mu_assert(minipack_is_bool(data+2) == false);

    mu_assert(minipack_is_true(data+0) == false);
    mu_assert(minipack_is_true(data+1) == true);
    mu_assert(minipack_is_true(data+2) == false);

    mu_assert(minipack_is_false(data+0) == true);
    mu_assert(minipack_is_false(data+1) == false);
    mu_assert(minipack_is_false(data+2) == false);

    return 0;
}

int test_bool_read() {
    mu_assert(minipack_unpack_bool("\xC3") == true);
    mu_assert_msgpack_true(1, "\xC3");
    mu_assert(minipack_unpack_bool("\xC2") == false);
    mu_assert_msgpack_false(1, "\xC2");
    return 0;
}

int test_bool_write() {
    uint8_t data[] = {0x00};

    minipack_pack_bool(data, true);
    mu_assert_mem(data, 1, "\xC3");

    minipack_pack_bool(data, false);
    mu_assert_mem(data, 1, "\xC2");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_bool);
    mu_run_test(test_bool_read);
    mu_run_test(test_bool_write);
    return 0;
}

RUN_TESTS()