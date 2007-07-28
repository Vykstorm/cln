// I_I_div_RA().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_RA.h"


// Implementation.

#include "cln/exception.h"
#include "cl_I.h"

namespace cln {

const cl_RA I_I_div_RA (const cl_I& a, const cl_I& b)
{
// Methode:
// Falls b=0: Error.
// Falls b>0: I_posI_div_RA anwenden.
// Falls b<0: I_posI_div_RA auf (- a) und (- b) anwenden.
	if (eq(b,0))
		throw division_by_0_exception();
	if (minusp(b))
		return I_posI_div_RA(-a,-b);
	else
		return I_posI_div_RA(a,b);
}

}  // namespace cln
