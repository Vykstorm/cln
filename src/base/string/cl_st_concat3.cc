// cl_string concatenation.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_st_make0.cc"

const cl_string operator+ (const cl_string& str1, const char* str2)
{
    unsigned long len1 = strlen(str1);
    unsigned long len2 = strlen(str2);
    var cl_heap_string* str = cl_make_heap_string(len1+len2);
    var char * ptr = &str->data[0];
    {
        var const char * ptr1 = asciz(str1);
        for (var unsigned long count = len1; count > 0; count--)
            *ptr++ = *ptr1++;
    }
    {
        var const char * ptr2 = asciz(str2);
        for (var unsigned long count = len2; count > 0; count--)
            *ptr++ = *ptr2++;
    }
    *ptr++ = '\0';
    return str;
}
