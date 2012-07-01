#include "minipack.h"

//==============================================================================
//
// Constants
//
//==============================================================================

#define PFIXNUM_TYPE_MASK     0x80
#define PFIXNUM_VALUE_MASK    0x7F


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
// Returns a 64-bit integer value for the fix num.
uint8_t minipack_pfixnum_read(void *ptr)
{
    int8_t value = *((int8_t*)ptr);
    return value & PFIXNUM_VALUE_MASK;
}

// Writes a positive fixnum to a given memory address.
//
// ptr - A pointer to where the fixnum should be written to.
void minipack_pfixnum_write(void *ptr, uint8_t value)
{
    *((int8_t*)ptr) = value & PFIXNUM_VALUE_MASK;
}
