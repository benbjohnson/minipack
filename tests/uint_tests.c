#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

//--------------------------------------
// Unsigned Int (8-bit)
//--------------------------------------

int test_uint8_read() {
    uint8_t data1[] = {0xCC, 0x00};
    mu_assert(minipack_uint8_read(data1) == 0);
    uint8_t data2[] = {0xCC, 0x02};
    mu_assert(minipack_uint8_read(data2) == 2);
    uint8_t data3[] = {0xCC, 0x14};
    mu_assert(minipack_uint8_read(data3) == 20);
    uint8_t data4[] = {0xCC, 0x7F};
    mu_assert(minipack_uint8_read(data4) == 127);
    uint8_t data5[] = {0xCC, 0xFF};
    mu_assert(minipack_uint8_read(data5) == 255);
    return 0;
}

int test_uint8_write() {
    uint8_t actual1[]   = {0x00, 0x00};
    uint8_t expected1[] = {0xCC, 0x00};
    minipack_uint8_write(actual1, 0);
    mu_assert_mem(actual1, 2, expected1);

    uint8_t actual2[]   = {0x00, 0x00};
    uint8_t expected2[] = {0xCC, 0x02};
    minipack_uint8_write(actual2, 2);
    mu_assert_mem(actual2, 2, expected2);

    uint8_t actual3[]   = {0x00, 0x00};
    uint8_t expected3[] = {0xCC, 0x14};
    minipack_uint8_write(actual3, 20);
    mu_assert_mem(actual3, 2, expected3);

    uint8_t actual4[]   = {0x00, 0x00};
    uint8_t expected4[] = {0xCC, 0x7F};
    minipack_uint8_write(actual4, 127);
    mu_assert_mem(actual4, 2, expected4);

    uint8_t actual5[]   = {0x00, 0x00};
    uint8_t expected5[] = {0xCC, 0xFF};
    minipack_uint8_write(actual5, 255);
    mu_assert_mem(actual5, 2, expected5);

    return 0;
}



//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_uint8_read);
    mu_run_test(test_uint8_write);
    return 0;
}

RUN_TESTS()