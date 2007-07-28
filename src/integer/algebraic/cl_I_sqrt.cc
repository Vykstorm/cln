// isqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cln/number.h"
#include "cln/io.h"
#include "cln/integer_io.h"
#include "cln/exception.h"
#include "cl_I.h"
#include "cl_DS.h"
#include <sstream>

namespace cln {

cl_boolean isqrt (const cl_I& x, cl_I* w)
{
	if (minusp(x)) {
		std::ostringstream buf;
		fprint(buf, "isqrt: applied to negative number: ");
		fprint(buf, x);
		throw runtime_exception(buf.str());
	}
	CL_ALLOCA_STACK;
	var const uintD* x_MSDptr;
	var uintC x_len;
	var const uintD* x_LSDptr;
	I_to_NDS_nocopy(x, x_MSDptr=,x_len=,x_LSDptr=,cl_true,); // Digit sequence >=0 zu x
	var DS y;
	var cl_boolean squarep;
	UDS_sqrt(x_MSDptr,x_len,x_LSDptr, &y, squarep=); // Wurzel ziehen
	*w = NUDS_to_I(y.MSDptr,y.len); // als Integer
	return squarep;
}
// Bit complexity (x of length N): O(M(N)).

}  // namespace cln
