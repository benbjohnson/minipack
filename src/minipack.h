// minipack v0.2.0

#ifndef _minipack_h
#define _minipack_h

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


//==============================================================================
//
// Fixnum
//
//==============================================================================

//======================================
// Positive Fixnum
//======================================

bool minipack_is_pos_fixnum(void *ptr);

uint8_t minipack_unpack_pos_fixnum(void *ptr, size_t *sz);

void minipack_pack_pos_fixnum(void *ptr, uint8_t value, size_t *sz);


//======================================
// Negative Fixnum
//======================================

int8_t minipack_unpack_neg_fixnum(void *ptr, size_t *sz);

void minipack_pack_neg_fixnum(void *ptr, int8_t value, size_t *sz);



//==============================================================================
//
// Unsigned Integers
//
//==============================================================================

//======================================
// Unsigned Int
//======================================

size_t minipack_sizeof_uint(uint64_t value);

uint64_t minipack_unpack_uint(void *ptr, size_t *sz);

void minipack_pack_uint(void *ptr, uint64_t value, size_t *sz);


//======================================
// Unsigned Int (8-bit)
//======================================

bool minipack_is_uint8(void *ptr);

uint8_t minipack_unpack_uint8(void *ptr, size_t *sz);

void minipack_pack_uint8(void *ptr, uint8_t value, size_t *sz);


//======================================
// Unsigned Int (16-bit)
//======================================

bool minipack_is_uint16(void *ptr);

uint16_t minipack_unpack_uint16(void *ptr, size_t *sz);

void minipack_pack_uint16(void *ptr, uint16_t value, size_t *sz);


//======================================
// Unsigned Int (32-bit)
//======================================

bool minipack_is_uint32(void *ptr);

uint32_t minipack_unpack_uint32(void *ptr, size_t *sz);

void minipack_pack_uint32(void *ptr, uint32_t value, size_t *sz);


//======================================
// Unsigned Int (64-bit)
//======================================

bool minipack_is_uint64(void *ptr);

uint64_t minipack_unpack_uint64(void *ptr, size_t *sz);

void minipack_pack_uint64(void *ptr, uint64_t value, size_t *sz);



//==============================================================================
//
// Signed Integers
//
//==============================================================================

//======================================
// Signed Int
//======================================

size_t minipack_int_sizeof(int64_t value);

int64_t minipack_unpack_int(void *ptr, size_t *sz);

void minipack_pack_int(void *ptr, int64_t value, size_t *sz);


//======================================
// Signed Int (8-bit)
//======================================

bool minipack_is_int8(void *ptr);

int8_t minipack_unpack_int8(void *ptr, size_t *sz);

void minipack_pack_int8(void *ptr, int8_t value, size_t *sz);


//======================================
// Signed Int (16-bit)
//======================================

bool minipack_is_int16(void *ptr);

int16_t minipack_unpack_int16(void *ptr, size_t *sz);

void minipack_pack_int16(void *ptr, int16_t value, size_t *sz);


//======================================
// Signed Int (32-bit)
//======================================

bool minipack_is_int32(void *ptr);

int32_t minipack_unpack_int32(void *ptr, size_t *sz);

void minipack_pack_int32(void *ptr, int32_t value, size_t *sz);


//======================================
// Signed Int (64-bit)
//======================================

bool minipack_is_int64(void *ptr);

int64_t minipack_unpack_int64(void *ptr, size_t *sz);

void minipack_pack_int64(void *ptr, int64_t value, size_t *sz);


//==============================================================================
//
// Nil
//
//==============================================================================

//======================================
// Nil
//======================================

bool minipack_is_nil(void *ptr);

void minipack_pack_nil(void *ptr, size_t *sz);

void minipack_unpack_nil(void *ptr, size_t *sz);


//==============================================================================
//
// Boolean
//
//==============================================================================

//======================================
// Bool
//======================================

bool minipack_is_bool(void *ptr);

bool minipack_is_true(void *ptr);

bool minipack_is_false(void *ptr);

bool minipack_unpack_bool(void *ptr, size_t *sz);

void minipack_pack_bool(void *ptr, bool value, size_t *sz);


//==============================================================================
//
// Floating-point
//
//==============================================================================

//======================================
// Float
//======================================

bool minipack_is_float(void *ptr);

float minipack_unpack_float(void *ptr, size_t *sz);

void minipack_pack_float(void *ptr, float value, size_t *sz);


//======================================
// Double
//======================================

bool minipack_is_double(void *ptr);

double minipack_unpack_double(void *ptr, size_t *sz);

void minipack_pack_double(void *ptr, double value, size_t *sz);



//==============================================================================
//
// Raw Bytes
//
//==============================================================================

//======================================
// General
//======================================

bool minipack_is_raw(void *ptr);

size_t minipack_raw_sizeof(uint32_t length);

uint32_t minipack_unpack_raw(void *ptr, size_t *sz);

void minipack_pack_raw(void *ptr, uint32_t length, size_t *sz);


//======================================
// Fix raw
//======================================

bool minipack_is_fixraw(void *ptr);

uint8_t minipack_unpack_fixraw(void *ptr, size_t *sz);

void minipack_pack_fixraw(void *ptr, uint8_t length, size_t *sz);


//======================================
// Raw 16
//======================================

bool minipack_is_raw16(void *ptr);

uint16_t minipack_unpack_raw16(void *ptr, size_t *sz);

void minipack_pack_raw16(void *ptr, uint16_t length, size_t *sz);


//======================================
// Raw 32
//======================================

bool minipack_is_raw32(void *ptr);

uint32_t minipack_unpack_raw32(void *ptr, size_t *sz);

void minipack_pack_raw32(void *ptr, uint32_t length, size_t *sz);



//==============================================================================
//
// Array
//
//==============================================================================

//======================================
// General
//======================================

bool minipack_is_array(void *ptr);

size_t minipack_array_sizeof(uint32_t count);

uint32_t minipack_unpack_array(void *ptr, size_t *sz);

void minipack_pack_array(void *ptr, uint32_t count, size_t *sz);


//======================================
// Fix array
//======================================

bool minipack_is_fixarray(void *ptr);

uint8_t minipack_unpack_fixarray(void *ptr, size_t *sz);

void minipack_pack_fixarray(void *ptr, uint8_t count, size_t *sz);


//======================================
// Array 16
//======================================

bool minipack_is_array16(void *ptr);

uint16_t minipack_unpack_array16(void *ptr, size_t *sz);

void minipack_pack_array16(void *ptr, uint16_t count, size_t *sz);


//======================================
// Array 32
//======================================

bool minipack_is_array32(void *ptr);

uint32_t minipack_unpack_array32(void *ptr, size_t *sz);

void minipack_pack_array32(void *ptr, uint32_t count, size_t *sz);



//==============================================================================
//
// Map
//
//==============================================================================

//======================================
// General
//======================================

bool minipack_is_map(void *ptr);

size_t minipack_map_sizeof(uint32_t count);

uint32_t minipack_unpack_map(void *ptr, size_t *sz);

void minipack_pack_map(void *ptr, uint32_t count, size_t *sz);


//======================================
// Fix map
//======================================

bool minipack_is_fixmap(void *ptr);

uint8_t minipack_unpack_fixmap(void *ptr, size_t *sz);

void minipack_pack_fixmap(void *ptr, uint8_t count, size_t *sz);


//======================================
// Map 16
//======================================

bool minipack_is_map16(void *ptr);

uint16_t minipack_unpack_map16(void *ptr, size_t *sz);

void minipack_pack_map16(void *ptr, uint16_t count, size_t *sz);


//======================================
// Map 32
//======================================

bool minipack_is_map32(void *ptr);

uint32_t minipack_unpack_map32(void *ptr, size_t *sz);

void minipack_pack_map32(void *ptr, uint32_t count, size_t *sz);


#endif
