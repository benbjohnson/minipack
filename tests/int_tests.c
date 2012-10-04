#include "minunit.h"
#include <minipack.h>

#include "memdump.h"

//==============================================================================
//
// Helpers
//
//==============================================================================

#define TMPFILE "tmp/uint"

#define mu_assert_fread_int(FILENAME, VALUE, SZ) do {\
    size_t sz; \
    FILE *file = fopen(FILENAME, "r"); \
    if(file == NULL) mu_fail("Cannot open file: %s", FILENAME); \
    long pos = ftell(file); \
    int64_t value = minipack_fread_int(file, &sz); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(value == VALUE, "Unexpected value: %lld", value); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    fclose(file); \
} while(0)

#define mu_assert_fwrite_int(FILENAME, VALUE, SZ, RC) do {\
    size_t sz; \
    FILE *file = fopen(TMPFILE, "w"); \
    if(file == NULL) mu_fail("Cannot open temp file: %s", TMPFILE); \
    long pos = ftell(file); \
    int rc = minipack_fwrite_int(file, VALUE, &sz); \
    mu_assert_with_msg(rc == RC, "Unexpected return value: %d", rc); \
    mu_assert_with_msg(sz == SZ, "Unexpected size: %ld", sz); \
    mu_assert_with_msg(pos+SZ == ftell(file), "Unexpected file position: %ld", ftell(file)); \
    mu_assert_file(TMPFILE, FILENAME); \
    fclose(file); \
} while(0)


//==============================================================================
//
// Test Cases
//
//==============================================================================

int test_unpack_int() {
    size_t sz;

    // Positive Fixnum
    mu_assert(minipack_unpack_int("\x00", &sz) == 0);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_int("\x7f", &sz) == 127);
    mu_assert(sz == 1);

    // Negative Fixnum
    mu_assert(minipack_unpack_int("\xFF", &sz) == -1);
    mu_assert(sz == 1);
    mu_assert(minipack_unpack_int("\xE0", &sz) == -32);
    mu_assert(sz == 1);

    // 8-bit
    mu_assert(minipack_unpack_int("\xD0\x7F", &sz) == 127);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int("\xD0\x80", &sz) == -128);
    mu_assert(sz == 2);

    // 16-bit
    mu_assert(minipack_unpack_int("\xD1\x03\xE8", &sz) == 1000);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int("\xD1\x7F\xFF", &sz) == 32767);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int("\xD1\x80\x00", &sz) == -32768);
    mu_assert(sz == 3);

    // 32-bit
    mu_assert(minipack_unpack_int("\xD2\x7F\xFF\xFF\xFF", &sz) == 2147483647);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int("\xD2\x80\x00\x00\x00", &sz) == -2147483648);
    mu_assert(sz == 5);

    // 64-bit
    mu_assert(minipack_unpack_int("\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF", &sz) == 9223372036854775807LL);
    mu_assert(sz == 9);
    mu_assert(minipack_unpack_int("\xD3\x80\x00\x00\x00\x00\x00\x00\x01", &sz) == -9223372036854775807LL);
    mu_assert(sz == 9);

    // 8-bit (Unsigned)
    mu_assert(minipack_unpack_int("\xCC\x80", &sz) == 128);
    mu_assert(sz == 2);
    mu_assert(minipack_unpack_int("\xCC\xFF", &sz) == 255);
    mu_assert(sz == 2);

    // 16-bit (Unsigned)
    mu_assert(minipack_unpack_int("\xCD\x01\x00", &sz) == 256);
    mu_assert(sz == 3);
    mu_assert(minipack_unpack_int("\xCD\xFF\xFF", &sz) == 65535);
    mu_assert(sz == 3);

    // 32-bit (Unsigned)
    mu_assert(minipack_unpack_int("\xCE\x00\x01\x00\x00", &sz) == 65536);
    mu_assert(sz == 5);
    mu_assert(minipack_unpack_int("\xCE\xFF\xFF\xFF\xFF", &sz) == 4294967295);
    mu_assert(sz == 5);

    // 64-bit (Unsigned)
    mu_assert(minipack_unpack_int("\xCF\x00\x00\x00\x01\x00\x00\x00\x00", &sz) == 4294967296);
    mu_assert(sz == 9);

    return 0;
}

int test_pack_int() {
    size_t sz;
    int8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Positive Fixnum
    minipack_pack_int(data, 0, &sz);
    mu_assert_mem(data, 1, "\x00");
    mu_assert(sz == 1);
    minipack_pack_int(data, 127, &sz);
    mu_assert_mem(data, 1, "\x7F");
    mu_assert(sz == 1);

    // Negative Fixnum
    minipack_pack_int(data, 0, &sz);
    mu_assert_mem(data, -1, "\xE0");
    mu_assert(sz == 1);
    minipack_pack_int(data, 127, &sz);
    mu_assert_mem(data, -32, "\xFF");
    mu_assert(sz == 1);

    // 8-bit
    minipack_pack_int(data, -128, &sz);
    mu_assert_mem(data, 2, "\xD0\x80");
    mu_assert(sz == 2);

    // 16-bit
    minipack_pack_int(data, 32767, &sz);
    mu_assert_mem(data, 3, "\xD1\x7F\xFF");
    mu_assert(sz == 3);
    minipack_pack_int(data, -32768, &sz);
    mu_assert_mem(data, 3, "\xD1\x80\x00");
    mu_assert(sz == 3);

    // 32-bit
    minipack_pack_int(data, 2147483647, &sz);
    mu_assert_mem(data, 5, "\xD2\x7F\xFF\xFF\xFF");
    mu_assert(sz == 5);
    minipack_pack_int(data, -2147483648, &sz);
    mu_assert_mem(data, 5, "\xD2\x80\x00\x00\x00");
    mu_assert(sz == 5);

    // 64-bit
    minipack_pack_int(data, 9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF");
    mu_assert(sz == 9);
    minipack_pack_int(data, -9223372036854775807LL, &sz);
    mu_assert_mem(data, 9, "\xD3\x80\x00\x00\x00\x00\x00\x00\x01");
    mu_assert(sz == 9);

    return 0;
}

int test_fread_int() {
    // Fixnum
    mu_assert_fread_int("tests/fixtures/fixnum/0", 0, 1);
    mu_assert_fread_int("tests/fixtures/fixnum/127", 127, 1);
    mu_assert_fread_int("tests/fixtures/fixnum/-1", -1, 1);
    mu_assert_fread_int("tests/fixtures/fixnum/-32", -32, 1);

    // 8-bit
    mu_assert_fread_int("tests/fixtures/int/127", 127, 2);
    mu_assert_fread_int("tests/fixtures/int/-128", -128, 2);

    // 16-bit
    mu_assert_fread_int("tests/fixtures/int/1000", 1000, 3);
    mu_assert_fread_int("tests/fixtures/int/32767", 32767, 3);
    mu_assert_fread_int("tests/fixtures/int/-32768", 32768, 3);

    // 32-bit
    mu_assert_fread_int("tests/fixtures/int/2147483647", 2147483647, 5);
    mu_assert_fread_int("tests/fixtures/int/-2147483648", -2147483648, 5);

    // 64-bit
    mu_assert_fread_int("tests/fixtures/int/9223372036854775807", 9223372036854775807LL, 9);
    mu_assert_fread_int("tests/fixtures/int/-9223372036854775807LL", -9223372036854775807LL, 9);

    // 8-bit (Unsigned)
    mu_assert_fread_int("tests/fixtures/uint/128", 128, 2);
    mu_assert_fread_int("tests/fixtures/uint/255", 255, 2);

    // 16-bit (Unsigned)
    mu_assert_fread_int("tests/fixtures/uint/256", 256, 3);
    mu_assert_fread_int("tests/fixtures/uint/65535", 65535, 3);

    // 32-bit (Unsigned)
    mu_assert_fread_int("tests/fixtures/uint/65536", 65536, 5);
    mu_assert_fread_int("tests/fixtures/uint/4294967295", 4294967295, 5);

    // ERR: Unsigned ints
    mu_assert_fread_int("tests/fixtures/uint/128", 0, 0);
    mu_assert_fread_int("tests/fixtures/uint/255", 0, 0);
    mu_assert_fread_int("tests/fixtures/uint/256", 0, 0);

    return 0;
}

int test_fwrite_int() {
    // Fixnum
    mu_assert_fwrite_int("tests/fixtures/fixnum/0", 0, 1, 0);
    mu_assert_fwrite_int("tests/fixtures/fixnum/127", 127, 1, 0);
    mu_assert_fwrite_int("tests/fixtures/fixnum/-1", -1, 1, 0);
    mu_assert_fwrite_int("tests/fixtures/fixnum/-32", -32, 1, 0);

    // 8-bit
    mu_assert_fwrite_int("tests/fixtures/int/127", 127, 2, 0);
    mu_assert_fwrite_int("tests/fixtures/int/-128", -128, 2, 0);

    // 16-bit
    mu_assert_fwrite_int("tests/fixtures/int/1000", 1000, 3, 0);
    mu_assert_fwrite_int("tests/fixtures/int/32767", 32767, 3, 0);
    mu_assert_fwrite_int("tests/fixtures/int/-32768", 32768, 3, 0);

    // 32-bit
    mu_assert_fwrite_int("tests/fixtures/int/2147483647", 2147483647, 5, 0);
    mu_assert_fwrite_int("tests/fixtures/int/-2147483648", -2147483648, 5, 0);

    // 64-bit
    mu_assert_fwrite_int("tests/fixtures/int/9223372036854775807", 9223372036854775807LL, 9, 0);
    mu_assert_fwrite_int("tests/fixtures/int/-9223372036854775807LL", -9223372036854775807LL, 9, 0);

    return 0;
}


//==============================================================================
//
// Setup
//
//==============================================================================

int all_tests() {
    mu_run_test(test_unpack_int);
    mu_run_test(test_pack_int);
    return 0;
}

RUN_TESTS()