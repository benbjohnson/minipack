#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_sizeof_fixraw() {
    mu_assert(minipack_sizeof_elem_and_data("\xA5" "abcde") == 6);
    return 0;
}

int test_unpack_fixraw() {
    size_t sz;
    
    mu_assert(minipack_unpack_fixraw("\xA0", &sz) == 0);
    mu_assert_msgpack_raw_body(0, NULL, 1, "\xA0");
    mu_assert(sz == 1);
    
    mu_assert(minipack_unpack_fixraw("\xA5", &sz) == 5);
    mu_assert_msgpack_raw_body(5, "abcde", 6, "\xA5" "abcde");
    mu_assert(sz == 1);
    
    mu_assert(minipack_unpack_fixraw("\xBF", &sz) == 31);
    mu_assert_msgpack_raw_body(31, "1234567890123456789012345678901", 32, "\xBF" "1234567890123456789012345678901");
    mu_assert(sz == 1);
    
    return 0;
}

int test_pack_fixraw() {
    size_t sz;
    uint8_t data[] = {0x00};

    minipack_pack_fixraw(data, 0, &sz);
    mu_assert_mem(data, 1, "\xA0");
    mu_assert(sz == 1);

    minipack_pack_fixraw(data, 5, &sz);
    mu_assert_mem(data, 1, "\xA5");
    mu_assert(sz == 1);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_sizeof_fixraw);
    mu_run_test(test_unpack_fixraw);
    mu_run_test(test_pack_fixraw);
    return 0;
}

RUN_TESTS()