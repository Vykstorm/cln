// cl_SF_to_I().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_SF.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"

const cl_I cl_SF_to_I (const cl_SF& x)
{
      // x entpacken:
      var cl_signean sign;
      var sintL exp;
      var uint32 mant;
      SF_decode(x, { return 0; }, sign=,exp=,mant=);
      exp = exp-(SF_mant_len+1);
      return ash( L_to_FN(sign==0
                          ? (sintL)mant // mant als Fixnum >0
                          : -(sintL)mant // -mant als Fixnum <0
                         ),
                  exp
                );
}
