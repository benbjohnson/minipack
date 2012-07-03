#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>

//==============================================================================
//
// Minunit
//
//==============================================================================

#define mu_fail(MSG, ...) do {\
    fprintf(stderr, "%s:%d: " MSG "\n", __FILE__, __LINE__, ##__VA_ARGS__);\
    return 1;\
} while(0)

#define mu_assert(TEST) do {\
    if (!(TEST)) {\
        fprintf(stderr, "%s:%d: %s \n", __FILE__, __LINE__, #TEST);\
        return 1;\
    }\
} while (0)

#define mu_assert_with_msg(TEST, MSG, ...) do {\
    if (!(TEST)) {\
        fprintf(stderr, "%s:%d: %s " MSG "\n", __FILE__, __LINE__, #TEST, ##__VA_ARGS__);\
        return 1;\
    }\
} while (0)

#define mu_run_test(TEST) do {\
    fprintf(stderr, "%s\n", #TEST);\
    int rc = TEST();\
    tests_run++; \
    if (rc) {\
        fprintf(stderr, "\n  Test Failure: %s()\n", #TEST);\
        return rc;\
    }\
} while (0)

#define RUN_TESTS() int main() {\
   fprintf(stderr, "== %s ==\n", __FILE__);\
   int rc = all_tests();\
   fprintf(stderr, "\n");\
   return rc;\
}

int tests_run;



//==============================================================================
//
// Memory
//
//==============================================================================

#define mu_assert_mem(PTR, COUNT, BYTES) do {\
    char *chars = (char*)BYTES; \
    uint8_t *bytes = (uint8_t*)chars; \
    int i; \
    for(i=0; i<COUNT; i++) { \
        if(((uint8_t*)PTR)[i] != bytes[i]) { \
            mu_fail("Memory does not match at byte: %d", i); \
        } \
    } \
} while(0)


//==============================================================================
//
// Msgpakc
//
//==============================================================================

#define mu_assert_msgpack0(FUNC, LENGTH, BYTES) do {\
    msgpack_sbuffer* buffer = msgpack_sbuffer_new(); \
    msgpack_packer* packer = msgpack_packer_new(buffer, msgpack_sbuffer_write); \
    FUNC(packer); \
    mu_assert_with_msg(buffer->size == LENGTH, "; Actual: %ld", buffer->size); \
    mu_assert_mem(buffer->data, LENGTH, BYTES); \
    msgpack_sbuffer_free(buffer); \
    msgpack_packer_free(packer); \
} while(0)

#define mu_assert_msgpack1(FUNC, VALUE, LENGTH, BYTES) do {\
    msgpack_sbuffer* buffer = msgpack_sbuffer_new(); \
    msgpack_packer* packer = msgpack_packer_new(buffer, msgpack_sbuffer_write); \
    FUNC(packer, VALUE); \
    memdump(buffer->data, buffer->size); \
    mu_assert_with_msg(buffer->size == LENGTH, "; Actual: %ld", buffer->size); \
    mu_assert_mem(buffer->data, LENGTH, BYTES); \
    msgpack_sbuffer_free(buffer); \
    msgpack_packer_free(packer); \
} while(0)

#define mu_assert_msgpack2(FUNC, VALUE1, VALUE2, LENGTH, BYTES) do {\
    msgpack_sbuffer* buffer = msgpack_sbuffer_new(); \
    msgpack_packer* packer = msgpack_packer_new(buffer, msgpack_sbuffer_write); \
    FUNC(packer, VALUE1, VALUE2); \
    mu_assert_with_msg(buffer->size == LENGTH, "; Actual: %ld", buffer->size); \
    mu_assert_mem(buffer->data, LENGTH, BYTES); \
    msgpack_sbuffer_free(buffer); \
    msgpack_packer_free(packer); \
} while(0)

#define mu_assert_msgpack_uint8(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_uint8, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_uint16(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_uint16, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_uint32(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_uint32, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_uint64(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_uint64, VALUE, LENGTH, BYTES)

#define mu_assert_msgpack_int8(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_int8, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_int16(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_int16, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_int32(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_int32, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_int64(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_int64, VALUE, LENGTH, BYTES)

#define mu_assert_msgpack_float(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_float, VALUE, LENGTH, BYTES)
#define mu_assert_msgpack_double(VALUE, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_double, VALUE, LENGTH, BYTES)

#define mu_assert_msgpack_nil(LENGTH, BYTES) mu_assert_msgpack0(msgpack_pack_nil, LENGTH, BYTES)
#define mu_assert_msgpack_true(LENGTH, BYTES) mu_assert_msgpack0(msgpack_pack_true, LENGTH, BYTES)
#define mu_assert_msgpack_false(LENGTH, BYTES) mu_assert_msgpack0(msgpack_pack_false, LENGTH, BYTES)

#define mu_assert_msgpack_array(COUNT, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_array, COUNT, LENGTH, BYTES)
#define mu_assert_msgpack_map(COUNT, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_map, COUNT, LENGTH, BYTES)

#define mu_assert_msgpack_raw_hdr(COUNT, LENGTH, BYTES) mu_assert_msgpack1(msgpack_pack_raw, COUNT, LENGTH, BYTES)
#define mu_assert_msgpack_raw(COUNT, DATA, LENGTH, BYTES) do {\
    char *chars = (char*)DATA; \
    msgpack_sbuffer* buffer = msgpack_sbuffer_new(); \
    msgpack_packer* packer = msgpack_packer_new(buffer, msgpack_sbuffer_write); \
    msgpack_pack_raw(packer, COUNT); \
    msgpack_pack_raw_body(packer, (void*)chars, COUNT); \
    mu_assert_with_msg(buffer->size == LENGTH, "; Actual: %ld", buffer->size); \
    mu_assert_mem(buffer->data, LENGTH, BYTES); \
    msgpack_sbuffer_free(buffer); \
    msgpack_packer_free(packer); \
} while(0)
