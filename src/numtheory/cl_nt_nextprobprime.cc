// nextprobprime().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_numtheory.h"


// Implementation.

#include "cl_real.h"

const cl_I nextprobprime (const cl_R& x)
{
	if (minusp(x))
		return 2;
	// Now x >= 0.
	var cl_I n = ceiling1(x);
	if (n <= 2)
		return 2;
	// Now n>=3.
	if (evenp(n))
		n = n+1;
	// Now n>=3 odd.
	loop {
		if (isprobprime(n))
			return n;
		n = n+2;
	}
}
