// I_I_to_RA().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_RA.h"


// Implementation.

#include "cl_I.h"

const cl_RA I_I_to_RA (const cl_I& a, const cl_I& b)
{
// Methode:
// falls b=1, a als Ergebnis, sonst der echte Bruch a/b.
	if (eq(b,1))
		return a;
	else
		return allocate_ratio(a,b);
}
