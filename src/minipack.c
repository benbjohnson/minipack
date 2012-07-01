#include "minipack.h"
#include "string.h"
#include "../tests/memdump.h"

//==============================================================================
//
// Constants
//
//==============================================================================

//--------------------------------------
// Fixnum
//--------------------------------------

#define POS_FIXNUM_MAX          127
#define POS_FIXNUM_TYPE         0x00
#define POS_FIXNUM_TYPE_MASK    0x80
#define POS_FIXNUM_VALUE_MASK   0x7F
#define POS_FIXNUM_SIZE         1

#define NEG_FIXNUM_TYPE         0xE0
#define NEG_FIXNUM_TYPE_MASK    0xE0
#define NEG_FIXNUM_VALUE_MASK   0x1F
#define NEG_FIXNUM_SIZE         1


//--------------------------------------
// Unsigned integers
//--------------------------------------

#define UINT8_TYPE              0xCC
#define UINT8_SIZE              2

#define UINT16_TYPE             0xCD
#define UINT16_SIZE             3

#define UINT32_TYPE             0xCE
#define UINT32_SIZE             5

#define UINT64_TYPE             0xCF
#define UINT64_SIZE             9


//--------------------------------------
// Signed integers
//--------------------------------------

#define INT8_TYPE               0xD0
#define INT8_SIZE               2

#define INT16_TYPE              0xD1
#define INT16_SIZE              3

#define INT32_TYPE              0xD2
#define INT32_SIZE              5

#define INT64_TYPE              0xD3
#define INT64_SIZE              9


//--------------------------------------
// Nil
//--------------------------------------

#define NIL_TYPE                0xC0
#define NIL_SIZE                1


//--------------------------------------
// Boolean
//--------------------------------------

#define TRUE_TYPE                0xC3
#define FALSE_TYPE               0xC2
#define BOOL_SIZE                1


//--------------------------------------
// Floating point
//--------------------------------------

#define FLOAT_TYPE              0xCA
#define FLOAT_SIZE              5

#define DOUBLE_TYPE             0xCB
#define DOUBLE_SIZE             9


//--------------------------------------
// Raw bytes
//--------------------------------------

#define FIXRAW_TYPE             0xA0
#define FIXRAW_TYPE_MASK        0xE0
#define FIXRAW_VALUE_MASK       0x1F
#define FIXRAW_HDRSIZE          1

#define RAW16_TYPE              0xDA
#define RAW16_HDRSIZE           3

#define RAW32_TYPE              0xDB
#define RAW32_HDRSIZE           5


//--------------------------------------
// Array
//--------------------------------------

#define FIXARRAY_TYPE           0x90
#define FIXARRAY_TYPE_MASK      0xF0
#define FIXARRAY_VALUE_MASK     0x0F
#define FIXARRAY_HDRSIZE        1

#define ARRAY16_TYPE            0xDC
#define ARRAY16_HDRSIZE         3

#define ARRAY32_TYPE            0xDD
#define ARRAY32_HDRSIZE         5


//--------------------------------------
// Map
//--------------------------------------

#define FIXMAP_TYPE             0x80
#define FIXMAP_TYPE_MASK        0xF0
#define FIXMAP_VALUE_MASK       0x0F
#define FIXMAP_HDRSIZE          1

#define MAP16_TYPE              0xDE
#define MAP16_HDRSIZE           3

#define MAP32_TYPE              0xDF
#define MAP32_HDRSIZE           5


//==============================================================================
//
// Byte Order
//
//==============================================================================

#include <sys/types.h>

#ifndef BYTE_ORDER
#if defined(linux) || defined(__linux__)
# include <endian.h>
#else
# include <machine/endian.h>
#endif
#endif

#if !defined(BYTE_ORDER)
#error "Undefined byte order"
#endif

uint64_t bswap64(uint64_t value)
{
    return (
        ((value & 0x00000000000000FF) << 56) |
        ((value & 0x000000000000FF00) << 40) |
        ((value & 0x0000000000FF0000) << 24) |
        ((value & 0x00000000FF000000) << 8) |
        ((value & 0x000000FF00000000) >> 8) |
        ((value & 0x0000FF0000000000) >> 24) |
        ((value & 0x00FF000000000000) >> 40) |
        ((value & 0xFF00000000000000) >> 56)
    );
}

#if (BYTE_ORDER == LITTLE_ENDIAN)
#define htonll(x) bswap64(x)
#define ntohll(x) bswap64(x)
#else
#define htonll(x) x
#define ntohll(x) x
#endif


//==============================================================================
//
// Fixnum
//
//==============================================================================

//--------------------------------------
// Positive Fixnum
//--------------------------------------

// Checks if an element is a positive fixnum.
//
// ptr - A pointer to the element.
//
// Returns true if the element is a positive fixnum, otherwise returns false.
bool minipack_is_pos_fixnum(void *ptr)
{
    return (*((uint8_t*)ptr) & POS_FIXNUM_TYPE_MASK) == POS_FIXNUM_TYPE;
}

// Reads a positive fixnum from a given memory address.
//
// ptr - A pointer to where the fixnum should be read from.
//
// Returns an unsigned 8-bit integer value for the fixnum.
uint8_t minipack_pos_fixnum_read(void *ptr)
{
    uint8_t value = *((uint8_t*)ptr);
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



//==============================================================================
//
// Unsigned Integers
//
//==============================================================================

//--------------------------------------
// Unsigned Int
//--------------------------------------

// Retrieves the size, in bytes, of how large an element will be.
//
// value - The value to calculate the size of.
//
// Returns the number of bytes needed for the element.
size_t minipack_uint_sizeof(uint64_t value)
{
    if(value <= POS_FIXNUM_MAX) {
        return POS_FIXNUM_SIZE;
    }
    else if(value <= UINT8_MAX) {
        return UINT8_SIZE;
    }
    else if(value <= UINT16_MAX) {
        return UINT16_SIZE;
    }
    else if(value <= UINT32_MAX) {
        return UINT32_SIZE;
    }
    else if(value <= UINT64_MAX) {
        return UINT64_SIZE;
    }

    return 0;
}

// Reads an unsigned integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
// sz  - A pointer to where the size of the element should be stored.
//
// Returns the number of bytes in the element.
uint64_t minipack_uint_read(void *ptr, size_t *sz)
{
    if(minipack_is_pos_fixnum(ptr)) {
        *sz = POS_FIXNUM_SIZE;
        return (uint64_t)minipack_pos_fixnum_read(ptr);
    }
    else if(minipack_is_uint8(ptr)) {
        *sz = UINT8_SIZE;
        return (uint64_t)minipack_uint8_read(ptr);
    }
    else if(minipack_is_uint16(ptr)) {
        *sz = UINT16_SIZE;
        return (uint64_t)minipack_uint16_read(ptr);
    }
    else if(minipack_is_uint32(ptr)) {
        *sz = UINT32_SIZE;
        return (uint64_t)minipack_uint32_read(ptr);
    }
    else if(minipack_is_uint64(ptr)) {
        *sz = UINT64_SIZE;
        return minipack_uint64_read(ptr);
    }
    else {
        *sz = 0;
        return 0;
    }
}

// Writes an unsigned integer to a given memory address.
//
// ptr   - A pointer to where the integer should be written to.
// value - The value to write.
// sz    - A pointer to where the size of the element will be returned.
void minipack_uint_write(void *ptr, uint64_t value, size_t *sz)
{
    *sz = minipack_uint_sizeof(value);

    if(value <= POS_FIXNUM_MAX) {
        minipack_pos_fixnum_write(ptr, (uint8_t)value);
    }
    else if(value <= UINT8_MAX) {
        minipack_uint8_write(ptr, (uint8_t)value);
    }
    else if(value <= UINT16_MAX) {
        minipack_uint16_write(ptr, (uint16_t)value);
    }
    else if(value <= UINT32_MAX) {
        minipack_uint32_write(ptr, (uint32_t)value);
    }
    else if(value <= UINT64_MAX) {
        minipack_uint64_write(ptr, value);
    }
}


//--------------------------------------
// Unsigned Int (8-bit)
//--------------------------------------

// Checks if an element is an unsigned 8-bit integer.
//
// ptr - A pointer to the element.
//
// Returns true if the element is an 8-bit integer, otherwise returns false.
bool minipack_is_uint8(void *ptr)
{
    return (*((uint8_t*)ptr) == UINT8_TYPE);
}

// Reads an unsigned 8-bit integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
//
// Returns an unsigned 8-bit integer value.
uint8_t minipack_uint8_read(void *ptr)
{
    return *((uint8_t*)(ptr+1));
}

// Writes an unsigned 8-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_uint8_write(void *ptr, uint8_t value)
{
    *((uint8_t*)ptr)     = UINT8_TYPE;
    *((uint8_t*)(ptr+1)) = value;
}


//--------------------------------------
// Unsigned Int (16-bit)
//--------------------------------------

// Checks if an element is an unsigned 16-bit integer.
//
// ptr - A pointer to the element.
//
// Returns true if the element is an 16-bit integer, otherwise returns false.
bool minipack_is_uint16(void *ptr)
{
    return (*((uint8_t*)ptr) == UINT16_TYPE);
}

// Reads an unsigned 16-bit integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
//
// Returns an unsigned 16-bit integer value.
uint16_t minipack_uint16_read(void *ptr)
{
    uint16_t value = *((uint16_t*)(ptr+1));
    return ntohs(value);
}

// Writes an unsigned 16-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_uint16_write(void *ptr, uint16_t value)
{
    *((uint8_t*)ptr)      = UINT16_TYPE;
    *((uint16_t*)(ptr+1)) = htons(value);
}


//--------------------------------------
// Unsigned Int (32-bit)
//--------------------------------------

// Checks if an element is an unsigned 32-bit integer.
//
// ptr - A pointer to the element.
//
// Returns true if the element is an 32-bit integer, otherwise returns false.
bool minipack_is_uint32(void *ptr)
{
    return (*((uint8_t*)ptr) == UINT32_TYPE);
}

// Reads an unsigned 32-bit integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
//
// Returns an unsigned 32-bit integer value.
uint32_t minipack_uint32_read(void *ptr)
{
    uint32_t value = *((uint32_t*)(ptr+1));
    return ntohl(value);
}

// Writes an unsigned 32-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_uint32_write(void *ptr, uint32_t value)
{
    *((uint8_t*)ptr)      = UINT32_TYPE;
    *((uint32_t*)(ptr+1)) = htonl(value);
}


//--------------------------------------
// Unsigned Int (64-bit)
//--------------------------------------

// Checks if an element is an unsigned 64-bit integer.
//
// ptr - A pointer to the element.
//
// Returns true if the element is an 64-bit integer, otherwise returns false.
bool minipack_is_uint64(void *ptr)
{
    return (*((uint8_t*)ptr) == UINT64_TYPE);
}

// Reads an unsigned 64-bit integer from a given memory address.
//
// ptr - A pointer to where the unsigned int should be read from.
//
// Returns an unsigned 64-bit integer value.
uint64_t minipack_uint64_read(void *ptr)
{
    uint64_t value = *((uint64_t*)(ptr+1));
    return ntohll(value);
}

// Writes an unsigned 64-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_uint64_write(void *ptr, uint64_t value)
{
    *((uint8_t*)ptr)      = UINT64_TYPE;
    *((uint64_t*)(ptr+1)) = htonll(value);
}


//==============================================================================
//
// Signed Integers
//
//==============================================================================

//--------------------------------------
// Signed Int (8-bit)
//--------------------------------------

// Reads an signed 8-bit integer from a given memory address.
//
// ptr - A pointer to where the signed int should be read from.
//
// Returns an signed 8-bit integer value.
int8_t minipack_int8_read(void *ptr)
{
    return *((int8_t*)(ptr+1));
}

// Writes an signed 8-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_int8_write(void *ptr, int8_t value)
{
    *((uint8_t*)ptr)    = INT8_TYPE;
    *((int8_t*)(ptr+1)) = value;
}


//--------------------------------------
// Signed Int (16-bit)
//--------------------------------------

// Reads an signed 16-bit integer from a given memory address.
//
// ptr - A pointer to where the signed int should be read from.
//
// Returns an signed 16-bit integer value.
int16_t minipack_int16_read(void *ptr)
{
    return ntohs(*((int16_t*)(ptr+1)));
}

// Writes an signed 16-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_int16_write(void *ptr, int16_t value)
{
    *((uint8_t*)ptr)     = INT16_TYPE;
    *((int16_t*)(ptr+1)) = htons(value);
}


//--------------------------------------
// Signed Int (32-bit)
//--------------------------------------

// Reads an signed 32-bit integer from a given memory address.
//
// ptr - A pointer to where the signed int should be read from.
//
// Returns an signed 32-bit integer value.
int32_t minipack_int32_read(void *ptr)
{
    return ntohl(*((int32_t*)(ptr+1)));
}

// Writes an signed 32-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_int32_write(void *ptr, int32_t value)
{
    *((uint8_t*)ptr)     = INT32_TYPE;
    *((int32_t*)(ptr+1)) = htonl(value);
}


//--------------------------------------
// Signed Int (64-bit)
//--------------------------------------

// Reads an signed 64-bit integer from a given memory address.
//
// ptr - A pointer to where the signed int should be read from.
//
// Returns an signed 64-bit integer value.
int64_t minipack_int64_read(void *ptr)
{
    return ntohll(*((int64_t*)(ptr+1)));
}

// Writes an signed 64-bit integer to a given memory address.
//
// ptr - A pointer to where the integer should be written to.
void minipack_int64_write(void *ptr, int64_t value)
{
    *((uint8_t*)ptr)     = INT64_TYPE;
    *((int64_t*)(ptr+1)) = htonll(value);
}


//==============================================================================
//
// Nil
//
//==============================================================================

//--------------------------------------
// Nil
//--------------------------------------

// Writes a nil to a given memory address.
//
// ptr - A pointer to where the nil should be written to.
void minipack_nil_write(void *ptr)
{
    *((uint8_t*)ptr) = NIL_TYPE;
}


//==============================================================================
//
// Boolean
//
//==============================================================================

//--------------------------------------
// Boolean
//--------------------------------------

// Reads a boolean from a given memory address.
//
// ptr - A pointer to where the boolean should be read from.
//
// Returns a boolean value.
bool minipack_bool_read(void *ptr)
{
    return (*(uint8_t*)ptr == TRUE_TYPE);
}

// Writes a boolean to a given memory address.
//
// ptr - A pointer to where the boolean should be written to.
void minipack_bool_write(void *ptr, bool value)
{
    if(value) {
        *((uint8_t*)ptr) = TRUE_TYPE;
    }
    else {
        *((uint8_t*)ptr) = FALSE_TYPE;
    }
}


//==============================================================================
//
// Floating-point
//
//==============================================================================

//--------------------------------------
// Float
//--------------------------------------

// Reads a float from a given memory address.
//
// ptr - A pointer to where the float should be read from.
//
// Returns a float value.
float minipack_float_read(void *ptr)
{
    // Cast bytes to int32 to use ntohl.
    uint32_t value = *((uint32_t*)(ptr+1));
    value = ntohl(value);
    return *((float*)&value);
}

// Writes a float to a given memory address.
//
// ptr - A pointer to where the float should be written to.
void minipack_float_write(void *ptr, float value)
{
    uint32_t bytes = htonl(*((uint32_t*)&value));
    *((uint8_t*)ptr)   = FLOAT_TYPE;
    *((float*)(ptr+1)) = *((float*)&bytes);
}


//--------------------------------------
// Double
//--------------------------------------

// Reads a double from a given memory address.
//
// ptr - A pointer to where the double should be read from.
//
// Returns a double value.
double minipack_double_read(void *ptr)
{
    // Cast bytes to int64 to use ntohll.
    uint64_t value = *((uint64_t*)(ptr+1));
    value = ntohll(value);
    return *((double*)&value);
}

// Writes a double to a given memory address.
//
// ptr - A pointer to where the double should be written to.
void minipack_double_write(void *ptr, double value)
{
    uint64_t bytes = htonll(*((uint64_t*)&value));
    *((uint8_t*)ptr)    = DOUBLE_TYPE;
    *((double*)(ptr+1)) = *((double*)&bytes);
}



//==============================================================================
//
// Raw Bytes
//
//==============================================================================

//--------------------------------------
// Fix raw
//--------------------------------------

// Reads the number of bytes in a fix raw from a given memory address.
//
// ptr - A pointer to where the fix raw should be read from.
//
// Returns the length of the bytes.
uint8_t minipack_fixraw_read_length(void *ptr)
{
    return *((uint8_t*)ptr) & FIXRAW_VALUE_MASK;
}

// Writes a fix raw byte array to a given memory address.
//
// ptr - A pointer to where the bytes should be written to.
void minipack_fixraw_write(void *ptr, uint8_t length, void *bytes)
{
    // Write length.
    *((uint8_t*)ptr) = (length & FIXRAW_VALUE_MASK) | FIXRAW_TYPE;
    
    // Write raw bytes.
    memmove(ptr+1, bytes, length);
}


//--------------------------------------
// Raw 16
//--------------------------------------

// Reads the number of bytes in a raw 16 from a given memory address.
//
// ptr - A pointer to where the raw 16 should be read from.
//
// Returns the length of the bytes.
uint16_t minipack_raw16_read_length(void *ptr)
{
    return ntohs(*((uint16_t*)(ptr+1)));
}

// Writes a raw 16 byte array to a given memory address.
//
// ptr - A pointer to where the bytes should be written to.
void minipack_raw16_write(void *ptr, uint16_t length, void *bytes)
{
    // Write header.
    *((uint8_t*)ptr)      = RAW16_TYPE;
    *((uint16_t*)(ptr+1)) = htons(length);
    
    // Write raw bytes.
    memmove(ptr+RAW16_HDRSIZE, bytes, length);
}


//--------------------------------------
// Raw 32
//--------------------------------------

// Reads the number of bytes in a raw 32 from a given memory address.
//
// ptr - A pointer to where the raw 32 should be read from.
//
// Returns the length of the bytes.
uint32_t minipack_raw32_read_length(void *ptr)
{
    return ntohl(*((uint32_t*)(ptr+1)));
}

// Writes a raw 32 byte array to a given memory address.
//
// ptr - A pointer to where the bytes should be written to.
void minipack_raw32_write(void *ptr, uint32_t length, void *bytes)
{
    // Write header.
    *((uint8_t*)ptr)      = RAW32_TYPE;
    *((uint32_t*)(ptr+1)) = htonl(length);
    
    // Write raw bytes.
    memmove(ptr+RAW32_HDRSIZE, bytes, length);
}



//==============================================================================
//
// Array
//
//==============================================================================

//--------------------------------------
// Fix array
//--------------------------------------

// Reads the number of elements in a fix array from a given memory address.
//
// ptr - A pointer to where the fix array should be read from.
//
// Returns the number of elements in the array.
uint8_t minipack_fixarray_read_count(void *ptr)
{
    return *((uint8_t*)ptr) & FIXARRAY_VALUE_MASK;
}

// Writes a fix array header to a given memory address.
//
// ptr   - A pointer to where the header should be written to.
// count - The number of elements in the array.
void minipack_fixarray_write_header(void *ptr, uint8_t count)
{
    *((uint8_t*)ptr) = (count & FIXARRAY_VALUE_MASK) | FIXARRAY_TYPE;
}


//--------------------------------------
// Array 16
//--------------------------------------

// Reads the number of elements in an array 16 from a given memory address.
//
// ptr - A pointer to where the array 16 should be read from.
//
// Returns the number of elements in the array
uint16_t minipack_array16_read_count(void *ptr)
{
    return ntohs(*((uint16_t*)(ptr+1)));
}

// Writes an array 16 header to a given memory address.
//
// ptr - A pointer to where the header should be written to.
void minipack_array16_write_header(void *ptr, uint16_t count)
{
    // Write header.
    *((uint8_t*)ptr)      = ARRAY16_TYPE;
    *((uint16_t*)(ptr+1)) = htons(count);
}


//--------------------------------------
// Array 32
//--------------------------------------

// Reads the number of elements in an array 32 from a given memory address.
//
// ptr - A pointer to where the array 32 should be read from.
//
// Returns the number of elements in the array
uint32_t minipack_array32_read_count(void *ptr)
{
    return ntohl(*((uint32_t*)(ptr+1)));
}

// Writes an array 32 header to a given memory address.
//
// ptr - A pointer to where the header should be written to.
void minipack_array32_write_header(void *ptr, uint32_t count)
{
    // Write header.
    *((uint8_t*)ptr)      = ARRAY32_TYPE;
    *((uint32_t*)(ptr+1)) = htonl(count);
}


//==============================================================================
//
// Map
//
//==============================================================================

//--------------------------------------
// Fix map
//--------------------------------------

// Reads the number of elements in a fix map from a given memory address.
//
// ptr - A pointer to where the fix map should be read from.
//
// Returns the number of elements in the map.
uint8_t minipack_fixmap_read_count(void *ptr)
{
    return *((uint8_t*)ptr) & FIXMAP_VALUE_MASK;
}

// Writes a fix map header to a given memory address.
//
// ptr   - A pointer to where the header should be written to.
// count - The number of elements in the map.
void minipack_fixmap_write_header(void *ptr, uint8_t count)
{
    *((uint8_t*)ptr) = (count & FIXMAP_VALUE_MASK) | FIXMAP_TYPE;
}


//--------------------------------------
// Map 16
//--------------------------------------

// Reads the number of elements in an map 16 from a given memory address.
//
// ptr - A pointer to where the map 16 should be read from.
//
// Returns the number of elements in the map.
uint16_t minipack_map16_read_count(void *ptr)
{
    return ntohs(*((uint16_t*)(ptr+1)));
}

// Writes an map 16 header to a given memory address.
//
// ptr - A pointer to where the header should be written to.
void minipack_map16_write_header(void *ptr, uint16_t count)
{
    // Write header.
    *((uint8_t*)ptr)      = MAP16_TYPE;
    *((uint16_t*)(ptr+1)) = htons(count);
}


//--------------------------------------
// Map 32
//--------------------------------------

// Reads the number of elements in an map 32 from a given memory address.
//
// ptr - A pointer to where the map 32 should be read from.
//
// Returns the number of elements in the map
uint32_t minipack_map32_read_count(void *ptr)
{
    return ntohl(*((uint32_t*)(ptr+1)));
}

// Writes an map 32 header to a given memory address.
//
// ptr - A pointer to where the header should be written to.
void minipack_map32_write_header(void *ptr, uint32_t count)
{
    // Write header.
    *((uint8_t*)ptr)      = MAP32_TYPE;
    *((uint32_t*)(ptr+1)) = htonl(count);
}



