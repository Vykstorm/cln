// extend().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF.h"


// Implementation.

#include "cl_LF_impl.h"
#include "cl_DS.h"

const cl_LF extend (const cl_LF& x, uintC len)
{
      var Lfloat y = allocate_lfloat(len,TheLfloat(x)->expo,TheLfloat(x)->sign); // neues LF
      { var uintC oldlen = TheLfloat(x)->len; // alte Länge, < len
        // Mantisse von x nach y kopieren:
        var uintD* ptr = copy_loop_msp(arrayMSDptr(TheLfloat(x)->data,oldlen),arrayMSDptr(TheLfloat(y)->data,len),oldlen);
        // und mit Null-Digits ergänzen:
        clear_loop_msp(ptr,len-oldlen);
      }
      return y;
}
