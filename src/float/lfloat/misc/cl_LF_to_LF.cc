// LF_to_LF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF.h"


// Implementation.

const cl_LF LF_to_LF (const cl_LF& x, uintC len)
{
      var uintC oldlen = TheLfloat(x)->len;
      if (len < oldlen) { return shorten(x,len); }
      if (len > oldlen) { return extend(x,len); }
      // len = oldlen
      return x;
}
