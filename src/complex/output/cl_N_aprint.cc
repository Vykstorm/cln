// print_complex().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_complex (cl_ostream stream, const cl_print_flags& flags, const cl_N& z)
{
	print_complex(stream,(const cl_print_number_flags&)flags,z);
}

}  // namespace cln
