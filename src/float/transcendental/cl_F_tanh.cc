// tanh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

namespace cln {

MAYBE_INLINE
const cl_F tanh (const cl_F& x)
{
// Methode:
// (/ (sinh x) (cosh x))
	var cosh_sinh_t hyp = cosh_sinh(x);
	return The(cl_F)(hyp.sinh) / The(cl_F)(hyp.cosh);
}

}  // namespace cln
