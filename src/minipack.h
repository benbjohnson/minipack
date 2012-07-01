#ifndef _minipack_h
#define _minipack_h

#include <inttypes.h>
#include <stdbool.h>


//==============================================================================
//
// Fixnum
//
//==============================================================================

//======================================
// Positive Fixnum
//======================================

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
// Unsigned Int (8-bit)
//======================================

uint8_t minipack_uint8_read(void *ptr);

void minipack_uint8_write(void *ptr, uint8_t value);


//======================================
// Unsigned Int (16-bit)
//======================================

uint16_t minipack_uint16_read(void *ptr);

void minipack_uint16_write(void *ptr, uint16_t value);


//======================================
// Unsigned Int (32-bit)
//======================================

uint32_t minipack_uint32_read(void *ptr);

void minipack_uint32_write(void *ptr, uint32_t value);


//======================================
// Unsigned Int (64-bit)
//======================================

uint64_t minipack_uint64_read(void *ptr);

void minipack_uint64_write(void *ptr, uint64_t value);



//==============================================================================
//
// Signed Integers
//
//==============================================================================

//======================================
// Signed Int (8-bit)
//======================================

int8_t minipack_int8_read(void *ptr);

void minipack_int8_write(void *ptr, int8_t value);


//======================================
// Signed Int (16-bit)
//======================================

int16_t minipack_int16_read(void *ptr);

void minipack_int16_write(void *ptr, int16_t value);


//======================================
// Signed Int (32-bit)
//======================================

int32_t minipack_int32_read(void *ptr);

void minipack_int32_write(void *ptr, int32_t value);


//======================================
// Signed Int (64-bit)
//======================================

int64_t minipack_int64_read(void *ptr);

void minipack_int64_write(void *ptr, int64_t value);



#endif
