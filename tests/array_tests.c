#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_array() {
    mu_assert(minipack_is_array("\x90") == true);
    mu_assert(minipack_is_array("\x9F") == true);
    mu_assert(minipack_is_array("\xDC\x00\x00") == true);
    mu_assert(minipack_is_array("\xDD\x00\x00\x00\x00") == true);

    mu_assert(minipack_is_array("\x00") == false);
    mu_assert(minipack_is_array("\xF0") == false);
    return 0;
}

int test_unpack_array() {
    size_t sz;
    
    // Fixarray
    mu_assert(minipack_unpack_array("\x90", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_array("\x9F", &sz) == 15);
    mu_assert(sz == 1);

    // array16
    mu_assert(minipack_unpack_array("\xDC\x00\x10", &sz) == 16);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_array("\xDC\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // array32
    mu_assert(minipack_unpack_array("\xDD\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_array("\xDD\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    return 0;
}

int test_pack_array() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Fixarray
    minipack_pack_array(data, 0, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x90");
    minipack_pack_array(data, 15, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x9F");

    // array16
    minipack_pack_array(data, 16, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDC\x00\x10");
    minipack_pack_array(data, 65535, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDC\xFF\xFF");

    // array32
    minipack_pack_array(data, 65536, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDD\x00\x01\x00\x00");
    minipack_pack_array(data, 4294967295, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDD\xFF\xFF\xFF\xFF");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_array);
    mu_run_test(test_unpack_array);
    mu_run_test(test_pack_array);
    return 0;
}

RUN_TESTS()