#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_uint64_read() {
    mu_assert(minipack_uint64_read("\xCF\x00\x00\x00\x00\x00\x00\x00\x00") == 0);
    mu_assert(minipack_uint64_read("\xCF\x00\x00\x00\x00\x00\x00\x00\x02") == 2);
    mu_assert(minipack_uint64_read("\xCF\x00\x00\x00\x00\x00\x00\x40\x23") == 16419);
    mu_assert(minipack_uint64_read("\xCF\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF") == 281474976710655LL);
    return 0;
}

int test_uint64_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    minipack_uint64_write(data, 0);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x00\x00");

    minipack_uint64_write(data, 2);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x00\x02");

    minipack_uint64_write(data, 16419);
    mu_assert_mem(data, 9, "\xCF\x00\x00\x00\x00\x00\x00\x40\x23");

    minipack_uint64_write(data, 281474976710655LL);
    mu_assert_mem(data, 9, "\xCF\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF");

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint64_read);
    mu_run_test(test_uint64_write);
    return 0;
}

RUN_TESTS()