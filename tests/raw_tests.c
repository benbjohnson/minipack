#include <stdlib.h>
#include <string.h>
#include <minipack.h>

#include "minunit.h"
#include "memdump.h"

//==============================================================================
//
// Test Cases
//
//==============================================================================

void init_ptr(void **ptr, uint32_t sz, uint32_t byte)
{
    if(*ptr) free(*ptr);
    *ptr = malloc(sz);
    memset(*ptr, sz, byte);
}

int test_is_raw() {
    mu_assert(minipack_is_raw("\xA0") == true);
    mu_assert(minipack_is_raw("\xBF") == true);
    mu_assert(minipack_is_raw("\xBF") == true);
    mu_assert(minipack_is_raw("\xDA\x00\x90") == true);
    mu_assert(minipack_is_raw("\xDB\x00\x90") == true);

    mu_assert(minipack_is_raw("\x00") == false);
    mu_assert(minipack_is_raw("\xF0") == false);
    return 0;
}

int test_raw_hdr_sizeof() {
    // Fix raw
    mu_assert(minipack_raw_hdr_sizeof(0) == 1);
    mu_assert(minipack_raw_hdr_sizeof(31) == 1);

    // raw16
    mu_assert(minipack_raw_hdr_sizeof(32) == 3);
    mu_assert(minipack_raw_hdr_sizeof(65535) == 3);

    // raw32
    mu_assert(minipack_raw_hdr_sizeof(65536) == 5);
    mu_assert(minipack_raw_hdr_sizeof(4294967295) == 5);

    return 0;
}

int test_raw_read_hdr() {
    size_t sz;

    // Fix raw
    mu_assert(minipack_raw_read_hdr("\xA0", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_raw_read_hdr("\xBF", &sz) == 31);
    mu_assert(sz == 1);
    
    // raw 16
    mu_assert(minipack_raw_read_hdr("\xDA\x00\x20", &sz) == 32);
    mu_assert(sz == 3);
    mu_assert(minipack_raw_read_hdr("\xDA\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);
    
    // raw 32
    mu_assert(minipack_raw_read_hdr("\xDB\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_raw_read_hdr("\xDB\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);
    
    return 0;
}

int test_raw_write() {
    size_t sz;
    void *ptr = NULL, *bytes = NULL;
    
    // Fix raw
    init_ptr(&ptr, 1, 0);
    minipack_raw_write(ptr, 0, NULL, &sz);
    mu_assert_mem(ptr, 1, "\xA0");
    mu_assert(sz == 1);

    init_ptr(&ptr, 32, 0);
    minipack_raw_write(ptr, 31, "1234567890123456789012345678901", &sz);
    mu_assert_mem(ptr, 1, "\xBF" "1234567890123456789012345678901");
    mu_assert(sz == 32);

    // raw16
    init_ptr(&ptr, 35, 0);
    minipack_raw_write(ptr, 32, "12345678901234567890123456789012", &sz);
    mu_assert_mem(ptr, 3, "\xDA\x00\x20" "12345678901234567890123456789012");
    mu_assert(sz == 35);

    init_ptr(&ptr, 65538, 0);
    init_ptr(&bytes, 65535, 1);
    minipack_raw_write(ptr, 65535, bytes, &sz);
    mu_assert_mem(ptr, 3, "\xDA\xFF\xFF");
    mu_assert_mem(ptr+3, 65535, bytes);
    mu_assert(sz == 65538);

    // raw32
    init_ptr(&ptr, 65541, 0);
    init_ptr(&bytes, 65536, 2);
    minipack_raw_write(ptr, 65536, bytes, &sz);
    mu_assert_mem(ptr, 3, "\xDB\x00\x01\x00\x00");
    mu_assert_mem(ptr+3, 65536, bytes);
    mu_assert(sz == 65541);

    free(ptr);
    free(bytes);
    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_is_raw);
    mu_run_test(test_raw_hdr_sizeof);
    mu_run_test(test_raw_read_hdr);
    mu_run_test(test_raw_write);
    return 0;
}

RUN_TESTS()