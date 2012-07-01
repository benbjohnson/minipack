#ifndef _mpack_h
#define _mpack_h

#include <inttypes.h>
#include <stdbool.h>


//==============================================================================
//
// Functions
//
//==============================================================================

//======================================
// Positive Fixnum
//======================================

uint8_t mpack_pos_fixnum_read(void *ptr);

void mpack_pos_fixnum_write(void *ptr, uint8_t value);


//======================================
// Negative Fixnum
//======================================

int8_t mpack_neg_fixnum_read(void *ptr);

void mpack_neg_fixnum_write(void *ptr, int8_t value);


//======================================
// Unsigned Int (8-bit)
//======================================

uint8_t mpack_uint8_read(void *ptr);

void mpack_uint8_write(void *ptr, uint8_t value);


//======================================
// Unsigned Int (16-bit)
//======================================

uint16_t mpack_uint16_read(void *ptr);

void mpack_uint16_write(void *ptr, uint16_t value);


//======================================
// Unsigned Int (32-bit)
//======================================

uint32_t mpack_uint32_read(void *ptr);

void mpack_uint32_write(void *ptr, uint32_t value);


//======================================
// Unsigned Int (64-bit)
//======================================

uint64_t mpack_uint64_read(void *ptr);

void mpack_uint64_write(void *ptr, uint64_t value);


#endif
