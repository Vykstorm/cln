// sqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_rational.h"
#include "cl_float.h"

MAYBE_INLINE
const cl_R sqrt (const cl_RA& x)
{
	var cl_RA w;
	if (sqrtp(x,&w)) // auf Quadrat testen
		return w; // war Quadrat, w ist die Wurzel
	else
		// x in Float umwandeln, dann die Wurzel ziehen:
		return sqrt(cl_float(x));
}
