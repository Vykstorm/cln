// cl_string hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

unsigned long hashcode (const cl_string& str)
{
    var unsigned long code = 0x61284AF3;
    // We walk through all characters. It may take some time for very
    // long strings, but it's better than completely ignoring some characters.
    var long len = str.length();
    var const char * ptr = str.asciz();
    for (; len > 0; len--) {
        var unsigned char c = *ptr++;
        code = (code << 5) | (code >> 27); // rotate left 5 bits
        code += (long)c << 16;
        code ^= (long)c;
        code &= 0xFFFFFFFF;
    }
    return code;
}
