// print_rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_rational (cl_ostream stream, const cl_print_real_flags& flags, const cl_RA& z)
{
	print_rational(stream,(const cl_print_rational_flags&)flags,z);
}

}  // namespace cln
