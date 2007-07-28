// floating_point_overflow_exception().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cln/io.h"

namespace cln {

floating_point_overflow_exception::floating_point_overflow_exception ()
	: floating_point_exception("floating point overflow.")
{}

}  // namespace cln
