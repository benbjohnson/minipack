#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_fixmap_read_count() {
    mu_assert(minipack_fixmap_read_count("\x80") == 0);
    mu_assert(minipack_fixmap_read_count("\x85") == 5);
    mu_assert(minipack_fixmap_read_count("\x8F") == 15);
    return 0;
}

int test_fixmap_write_header() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_fixmap_write_header(data, 0);
    mu_assert_mem(data, 1, "\x80");

    minipack_fixmap_write_header(data, 5);
    mu_assert_mem(data, 1, "\x85");

    minipack_fixmap_write_header(data, 15);
    mu_assert_mem(data, 1, "\x8F");

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_fixmap_read_count);
    mu_run_test(test_fixmap_write_header);
    return 0;
}

RUN_TESTS()