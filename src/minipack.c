#include "minipack.h"

//==============================================================================
//
// Constants
//
//==============================================================================

#define POS_FIXNUM_TYPE         0x00
#define POS_FIXNUM_TYPE_MASK    0x80
#define POS_FIXNUM_VALUE_MASK   0x7F
#define POS_FIXNUM_SIZE         1

#define NEG_FIXNUM_TYPE         0xE0
#define NEG_FIXNUM_TYPE_MASK    0xE0
#define NEG_FIXNUM_VALUE_MASK   0x1F
#define NEG_FIXNUM_SIZE         1

#define UINT8_TYPE              0xCC
#define UINT8_SIZE              2

#define UINT16_TYPE             0xCD
#define UINT16_SIZE             3

#define UINT32_TYPE             0xCE
#define UINT32_SIZE             5

#define UINT64_TYPE             0xCF
#define UINT64_SIZE             9


//==============================================================================
//
// Functions
//
//==============================================================================

//--------------------------------------
// Positive Fixnum
//--------------------------------------

// Reads a positive fixnum from a given memory address.
//
// ptr - A pointer to where the fixnum should be read from.
//
// Returns an unsigned 8-bit integer value for the fixnum.
uint8_t minipack_pos_fixnum_read(void *ptr)
{
    int8_t value = *((uint8_t*)ptr);
    return value & POS_FIXNUM_VALUE_MASK;
}

// Writes a positive fixnum to a given memory address.
//
// ptr - A pointer to where the fixnum should be written to.
void minipack_pos_fixnum_write(void *ptr, uint8_t value)
{
    *((uint8_t*)ptr) = value & POS_FIXNUM_VALUE_MASK;
}


//--------------------------------------
// Negative Fixnum
//--------------------------------------

// Reads a negative fixnum from a given memory address.
//
// ptr - A pointer to where the fixnum should be read from.
//
// Returns a signed 8-bit integer value for the fixnum.
int8_t minipack_neg_fixnum_read(void *ptr)
{
    int8_t value = *((int8_t*)ptr);
    return ((value & NEG_FIXNUM_VALUE_MASK) + 1) * -1;
}

// Writes a negative fixnum from a given memory address.
//
// ptr - A pointer to where the fixnum should be written to.
void minipack_neg_fixnum_write(void *ptr, int8_t value)
{
    *((int8_t*)ptr) = (((value * -1) - 1) & NEG_FIXNUM_VALUE_MASK) | NEG_FIXNUM_TYPE;
}


//--------------------------------------
// Unsigned Int (8-bit)
//--------------------------------------

// Reads an unsigned 8-bit integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
//
// Returns an unsigned 8-bit integer value.
uint8_t minipack_uint8_read(void *ptr)
{
    return *((uint8_t*)(ptr+1));
}

// Writes a positive fixnum to a given memory address.
//
// ptr - A pointer to where the fixnum should be written to.
void minipack_uint8_write(void *ptr, uint8_t value)
{
    *((uint8_t*)ptr)     = UINT8_TYPE;
    *((uint8_t*)(ptr+1)) = value;
}
