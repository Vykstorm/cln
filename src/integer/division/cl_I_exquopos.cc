// exquopos().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"

const cl_I exquopos (const cl_I& x, const cl_I& y)
{
// Methode:
// (exquopos x y) :==
// (DIVIDE x y) -> q,r
// Falls r<>0, Error.
// Liefere q.
  var cl_I_div_t q_r = cl_divide(x,y);
  if (!zerop(q_r.remainder)) { cl_error_exquo(x,y); }
  return q_r.quotient;
}
