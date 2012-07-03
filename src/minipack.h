// minipack v0.1.1

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

uint8_t minipack_pos_fixnum_read(void *ptr);

void minipack_pos_fixnum_write(void *ptr, uint8_t value);


//======================================
// Negative Fixnum
//======================================

int8_t minipack_neg_fixnum_read(void *ptr);

void minipack_neg_fixnum_write(void *ptr, int8_t value);



//==============================================================================
//
// Unsigned Integers
//
//==============================================================================

//======================================
// Unsigned Int
//======================================

size_t minipack_uint_sizeof(uint64_t value);

uint64_t minipack_uint_read(void *ptr, size_t *sz);

void minipack_uint_write(void *ptr, uint64_t value, size_t *sz);


//======================================
// Unsigned Int (8-bit)
//======================================

bool minipack_is_uint8(void *ptr);

uint8_t minipack_uint8_read(void *ptr);

void minipack_uint8_write(void *ptr, uint8_t value);


//======================================
// Unsigned Int (16-bit)
//======================================

bool minipack_is_uint16(void *ptr);

uint16_t minipack_uint16_read(void *ptr);

void minipack_uint16_write(void *ptr, uint16_t value);


//======================================
// Unsigned Int (32-bit)
//======================================

bool minipack_is_uint32(void *ptr);

uint32_t minipack_uint32_read(void *ptr);

void minipack_uint32_write(void *ptr, uint32_t value);


//======================================
// Unsigned Int (64-bit)
//======================================

bool minipack_is_uint64(void *ptr);

uint64_t minipack_uint64_read(void *ptr);

void minipack_uint64_write(void *ptr, uint64_t value);



//==============================================================================
//
// Signed Integers
//
//==============================================================================

//======================================
// Signed Int
//======================================

size_t minipack_int_sizeof(int64_t value);

int64_t minipack_int_read(void *ptr, size_t *sz);

void minipack_int_write(void *ptr, int64_t value, size_t *sz);


//======================================
// Signed Int (8-bit)
//======================================

bool minipack_is_int8(void *ptr);

int8_t minipack_int8_read(void *ptr);

void minipack_int8_write(void *ptr, int8_t value);


//======================================
// Signed Int (16-bit)
//======================================

bool minipack_is_int16(void *ptr);

int16_t minipack_int16_read(void *ptr);

void minipack_int16_write(void *ptr, int16_t value);


//======================================
// Signed Int (32-bit)
//======================================

bool minipack_is_int32(void *ptr);

int32_t minipack_int32_read(void *ptr);

void minipack_int32_write(void *ptr, int32_t value);


//======================================
// Signed Int (64-bit)
//======================================

bool minipack_is_int64(void *ptr);

int64_t minipack_int64_read(void *ptr);

void minipack_int64_write(void *ptr, int64_t value);


//==============================================================================
//
// Nil
//
//==============================================================================

//======================================
// Nil
//======================================

void minipack_nil_write(void *ptr);


//==============================================================================
//
// Boolean
//
//==============================================================================

//======================================
// Nil
//======================================

bool minipack_bool_read(void *ptr);

void minipack_bool_write(void *ptr, bool value);


//==============================================================================
//
// Floating-point
//
//==============================================================================

//======================================
// Float
//======================================

float minipack_float_read(void *ptr);

void minipack_float_write(void *ptr, float value);


//======================================
// Double
//======================================

double minipack_double_read(void *ptr);

void minipack_double_write(void *ptr, double value);



//==============================================================================
//
// Raw Bytes
//
//==============================================================================

//======================================
// General
//======================================

size_t minipack_raw_hdr_sizeof(uint32_t length);

uint32_t minipack_raw_read_hdr(void *ptr, size_t *hdrsz);

void minipack_raw_write(void *ptr, uint32_t length, void *bytes, size_t *sz);


//======================================
// Fix raw
//======================================

bool minipack_is_fixraw(void *ptr);

uint8_t minipack_fixraw_read_length(void *ptr);

void minipack_fixraw_write(void *ptr, uint8_t length, void *bytes);


//======================================
// Raw 16
//======================================

bool minipack_is_raw16(void *ptr);

uint16_t minipack_raw16_read_length(void *ptr);

void minipack_raw16_write(void *ptr, uint16_t length, void *bytes);


//======================================
// Raw 32
//======================================

bool minipack_is_raw32(void *ptr);

uint32_t minipack_raw32_read_length(void *ptr);

void minipack_raw32_write(void *ptr, uint32_t length, void *bytes);



//==============================================================================
//
// Array
//
//==============================================================================

//======================================
// Fix array
//======================================

uint8_t minipack_fixarray_read_count(void *ptr);

void minipack_fixarray_write_header(void *ptr, uint8_t count);


//======================================
// Array 16
//======================================

uint16_t minipack_array16_read_count(void *ptr);

void minipack_array16_write_header(void *ptr, uint16_t count);


//======================================
// Array 32
//======================================

uint32_t minipack_array32_read_count(void *ptr);

void minipack_array32_write_header(void *ptr, uint32_t count);



//==============================================================================
//
// Map
//
//==============================================================================

//======================================
// Fix map
//======================================

uint8_t minipack_fixmap_read_count(void *ptr);

void minipack_fixmap_write_header(void *ptr, uint8_t count);


//======================================
// Map 16
//======================================

uint16_t minipack_map16_read_count(void *ptr);

void minipack_map16_write_header(void *ptr, uint16_t count);


//======================================
// Map 32
//======================================

uint32_t minipack_map32_read_count(void *ptr);

void minipack_map32_write_header(void *ptr, uint32_t count);


#endif
