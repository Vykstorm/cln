// exquo().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"

const cl_I exquo (const cl_I& x, const cl_I& y)
{
// Methode:
// (exquo x y) :==
// (DIVIDE (abs x) (abs y)) -> q,r
// Falls r<>0, Error.
// Falls x,y verschiedene Vorzeichen haben, liefere -q, sonst q.
  var cl_I_div_t q_r = cl_divide(abs(x),abs(y));
  if (!zerop(q_r.remainder)) { cl_error_exquo(x,y); }
  if (minusp(x) == minusp(y))
    { return q_r.quotient; }
    else
    { return -q_r.quotient; }
}
