// cl_round_pi2().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

const cl_F_div_t cl_round_pi2 (const cl_F& x)
{
	if (float_exponent(x) < 0)
		// Exponent <0 -> |x|<1/2 -> |x/(pi/2)| < 1/2, also Division unnötig
		return cl_F_div_t(0,x); // Quotient 0, Rest x
	else
		// x durch pi/2 (mit hinreichender Genauigkeit) dividieren
		return round2(x,scale_float(cl_pi(x),-1));
}
