#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

//--------------------------------------
// Positive Fixnum
//--------------------------------------

int test_pfixnum_read() {
    uint8_t data[] = {0x00, 0x02, 0x14, 0x7F, 0x80};
    mu_assert(minipack_pfixnum_read(data+0) == 0);
    mu_assert(minipack_pfixnum_read(data+1) == 2);
    mu_assert(minipack_pfixnum_read(data+2) == 20);
    mu_assert(minipack_pfixnum_read(data+3) == 127);
    mu_assert(minipack_pfixnum_read(data+4) == 0);
    return 0;
}

int test_pfixnum_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    minipack_pfixnum_write(data+0, 0);
    minipack_pfixnum_write(data+1, 2);
    minipack_pfixnum_write(data+2, 20);
    minipack_pfixnum_write(data+3, 127);
    minipack_pfixnum_write(data+4, 128);
    mu_assert(data[0] == 0);
    mu_assert(data[1] == 2);
    mu_assert(data[2] == 20);
    mu_assert(data[3] == 127);
    mu_assert(data[4] == 0);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_pfixnum_read);
    mu_run_test(test_pfixnum_write);
    return 0;
}

RUN_TESTS()