#include <minipack.h>
#include <msgpack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_is_map() {
    mu_assert(minipack_is_map("\x80") == true);
    mu_assert(minipack_is_map("\x8F") == true);
    mu_assert(minipack_is_map("\xDE\x00\x00") == true);
    mu_assert(minipack_is_map("\xDF\x00\x00\x00\x00") == true);

    mu_assert(minipack_is_map("\x00") == false);
    mu_assert(minipack_is_map("\xF0") == false);
    return 0;
}

int test_map_read() {
    size_t sz;
    
    // Fixmap
    mu_assert(minipack_unpack_map("\x80", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_map("\x8F", &sz) == 15);
    mu_assert(sz == 1);

    // map16
    mu_assert(minipack_unpack_map("\xDE\x00\x10", &sz) == 16);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_map("\xDE\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // map32
    mu_assert(minipack_unpack_map("\xDF\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_map("\xDF\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    return 0;
}

int test_map_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Fixmap
    minipack_pack_map(data, 0, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x80");
    minipack_pack_map(data, 15, &sz);
    mu_assert(sz == 1);
    mu_assert_mem(data, 1, "\x8F");

    // map16
    minipack_pack_map(data, 16, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDE\x00\x10");
    minipack_pack_map(data, 65535, &sz);
    mu_assert(sz == 3);
    mu_assert_mem(data, 3, "\xDE\xFF\xFF");

    // map32
    minipack_pack_map(data, 65536, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDF\x00\x01\x00\x00");
    minipack_pack_map(data, 4294967295, &sz);
    mu_assert(sz == 5);
    mu_assert_mem(data, 5, "\xDF\xFF\xFF\xFF\xFF");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_map);
    mu_run_test(test_map_read);
    mu_run_test(test_map_write);
    return 0;
}

RUN_TESTS()