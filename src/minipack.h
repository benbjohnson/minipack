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
// Fixnum
//======================================

uint8_t minipack_pfixnum_read(void *ptr);

void minipack_pfixnum_write(void *ptr, uint8_t value);


#endif
