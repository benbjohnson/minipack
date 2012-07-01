#ifndef _minipack_h
#define _minipack_h

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

uint8_t minipack_pos_fixnum_read(void *ptr);

void minipack_pos_fixnum_write(void *ptr, uint8_t value);


//======================================
// Negative Fixnum
//======================================

int8_t minipack_neg_fixnum_read(void *ptr);

void minipack_neg_fixnum_write(void *ptr, int8_t value);


//======================================
// Unsigned Int (8-bit)
//======================================

uint8_t minipack_uint8_read(void *ptr);

void minipack_uint8_write(void *ptr, uint8_t value);


#endif
