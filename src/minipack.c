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
