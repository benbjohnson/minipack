#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_nil_write() {
    uint8_t data[] = {0x00};
    minipack_nil_write(data);
    mu_assert_mem(data, 1, "\xC0");
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_nil_write);
    return 0;
}

RUN_TESTS()