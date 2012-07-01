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

int test_pos_fixnum_read() {
    uint8_t data[] = {0x00, 0x02, 0x14, 0x7F, 0x80};
    mu_assert(mpack_pos_fixnum_read(data+0) == 0);
    mu_assert(mpack_pos_fixnum_read(data+1) == 2);
    mu_assert(mpack_pos_fixnum_read(data+2) == 20);
    mu_assert(mpack_pos_fixnum_read(data+3) == 127);
    mu_assert(mpack_pos_fixnum_read(data+4) == 0);
    return 0;
}

int test_pos_fixnum_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    mpack_pos_fixnum_write(data+0, 0);
    mpack_pos_fixnum_write(data+1, 2);
    mpack_pos_fixnum_write(data+2, 20);
    mpack_pos_fixnum_write(data+3, 127);
    mpack_pos_fixnum_write(data+4, 128);
    mu_assert(data[0] == 0x00);
    mu_assert(data[1] == 0x02);
    mu_assert(data[2] == 0x14);
    mu_assert(data[3] == 0x7F);
    mu_assert(data[4] == 0x00);
    return 0;
}


//--------------------------------------
// Negative Fixnum
//--------------------------------------

int test_neg_fixnum_read() {
    uint8_t data[] = {0xE0, 0xE2, 0xF3, 0xFF};
    mu_assert(mpack_neg_fixnum_read(data+0) == -1);
    mu_assert(mpack_neg_fixnum_read(data+1) == -3);
    mu_assert(mpack_neg_fixnum_read(data+2) == -20);
    mu_assert(mpack_neg_fixnum_read(data+3) == -32);
    return 0;
}

int test_neg_fixnum_write() {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    mpack_neg_fixnum_write(data+0, -1);
    mpack_neg_fixnum_write(data+1, -3);
    mpack_neg_fixnum_write(data+2, -20);
    mpack_neg_fixnum_write(data+3, -32);
    mu_assert(data[0] == 0xE0);
    mu_assert(data[1] == 0xE2);
    mu_assert(data[2] == 0xF3);
    mu_assert(data[3] == 0xFF);
    return 0;
}

//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_pos_fixnum_read);
    mu_run_test(test_pos_fixnum_write);

    mu_run_test(test_neg_fixnum_read);
    mu_run_test(test_neg_fixnum_write);

    return 0;
}

RUN_TESTS()