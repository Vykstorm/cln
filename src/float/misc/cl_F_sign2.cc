// float_sign().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

const cl_F float_sign (const cl_F& x, const cl_F& y)
{
  // Methode:
  // Falls x<0 xor y<0, Ergebnis (- y), sonst Ergebnis y.
	if (minusp(x) != minusp(y))
		return -y;
	else
		return y;
}
