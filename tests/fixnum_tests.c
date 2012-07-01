#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_pfixnum_read() {
    uint8_t data[] = {0x00, 0x02, 0x14, 0x7F, 0x80};
    mu_assert(minipack_pfixnum_read(data+0) == 0);
    mu_assert(minipack_pfixnum_read(data+1) == 2);
    mu_assert(minipack_pfixnum_read(data+2) == 20);
    mu_assert(minipack_pfixnum_read(data+3) == 127);
    mu_assert(minipack_pfixnum_read(data+4) == 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_pfixnum_read);
    return 0;
}

RUN_TESTS()