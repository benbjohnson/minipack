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

int test_nil_write() {
    uint8_t data[] = {0x00};
    minipack_pack_nil(data);
    mu_assert_mem(data, 1, "\xC0");
    mu_assert_msgpack_nil(1, "\xC0");
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_nil);
    mu_run_test(test_nil_write);
    return 0;
}

RUN_TESTS()