// minus1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

const cl_I minus1 (const cl_I& x)
{
	if (fixnump(x))
	  { // x ist Fixnum
	    if (x.word != cl_combine(cl_FN_tag,bit(cl_value_len-1)))
		// bleibt Fixnum: direkt 1 subtrahieren
		// This assumes cl_value_shift + cl_value_len == cl_word_size.
		{ return cl_I_from_word(x.word - cl_combine(0,1)); }
          }
        // die sichere Methode
        { CL_ALLOCA_STACK;
          var uintD* MSDptr;
          var uintC len;
          var uintD* LSDptr;
          I_to_NDS_1(x, MSDptr=,len=,LSDptr=); // NDS zu x bilden.
          DS_minus1_plus(LSDptr,len); // von der NDS 1 subtrahieren
          return DS_to_I(MSDptr,len); // wieder zum Integer machen
        }
}
