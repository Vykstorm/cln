// print_rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational_io.h"


// Implementation.

#include "cl_output.h"

void print_rational (cl_ostream stream, const cl_print_flags& flags, const cl_RA& z)
{
	print_rational(stream,(const cl_print_number_flags&)flags,z);
}
