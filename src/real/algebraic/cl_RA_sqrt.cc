// sqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cln/rational.h"
#include "cln/float.h"

namespace cln {

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

}  // namespace cln
