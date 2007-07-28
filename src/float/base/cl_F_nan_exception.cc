// floating_point_nan_exception().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cln/io.h"

namespace cln {

floating_point_nan_exception::floating_point_nan_exception ()
	: floating_point_exception("floating point NaN occurred.")
{}

}  // namespace cln
