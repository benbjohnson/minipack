#include "minunit.h"
#include <minipack.h>
#include <msgpack.h>

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
    size_t sz;
    uint8_t data[] = {0x00, 0x02, 0x14, 0x7F, 0x80};
    mu_assert(minipack_unpack_pos_fixnum(data+0, &sz) == 0);
    mu_assert_msgpack_uint8(0, 1, data+0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_pos_fixnum(data+1, &sz) == 2);
    mu_assert_msgpack_uint8(2, 1, data+1);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_pos_fixnum(data+2, &sz) == 20);
    mu_assert_msgpack_uint8(20, 1, data+2);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_pos_fixnum(data+3, &sz) == 127);
    mu_assert_msgpack_uint8(127, 1, data+3);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_pos_fixnum(data+4, &sz) == 0);
    return 0;
}

int test_pos_fixnum_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    minipack_pack_pos_fixnum(data+0, 0, &sz);
    mu_assert(data[0] == 0x00);
    mu_assert(sz == 1);
    minipack_pack_pos_fixnum(data+1, 2, &sz);
    mu_assert(data[1] == 0x02);
    mu_assert(sz == 1);
    minipack_pack_pos_fixnum(data+2, 20, &sz);
    mu_assert(data[2] == 0x14);
    mu_assert(sz == 1);
    minipack_pack_pos_fixnum(data+3, 127, &sz);
    mu_assert(data[3] == 0x7F);
    mu_assert(sz == 1);
    minipack_pack_pos_fixnum(data+4, 128, &sz);
    mu_assert(data[4] == 0x00);
    mu_assert(sz == 1);
    return 0;
}


//--------------------------------------
// Negative Fixnum
//--------------------------------------

int test_neg_fixnum_read() {
    size_t sz;
    uint8_t data[] = {0xFF, 0xFD, 0xEC, 0xE0};
    mu_assert(minipack_unpack_neg_fixnum(data+0, &sz) == -1);
    mu_assert_msgpack_int8(-1, 1, data+0);
    mu_assert(minipack_unpack_neg_fixnum(data+1, &sz) == -3);
    mu_assert_msgpack_int8(-3, 1, data+1);
    mu_assert(minipack_unpack_neg_fixnum(data+2, &sz) == -20);
    mu_assert_msgpack_int8(-20, 1, data+2);
    mu_assert(minipack_unpack_neg_fixnum(data+3, &sz) == -32);
    mu_assert_msgpack_int8(-32, 1, data+3);
    return 0;
}

int test_neg_fixnum_write() {
    size_t sz;
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    minipack_pack_neg_fixnum(data+0, -1, &sz);
    mu_assert(data[0] == 0xFF);
    minipack_pack_neg_fixnum(data+1, -3, &sz);
    mu_assert(data[1] == 0xFD);
    minipack_pack_neg_fixnum(data+2, -20, &sz);
    mu_assert(data[2] == 0xEC);
    minipack_pack_neg_fixnum(data+3, -32, &sz);
    mu_assert(data[3] == 0xE0);
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