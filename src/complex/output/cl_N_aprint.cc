// print_complex().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex_io.h"


// Implementation.

#include "cl_output.h"

void print_complex (cl_ostream stream, const cl_print_flags& flags, const cl_N& z)
{
	print_complex(stream,(const cl_print_number_flags&)flags,z);
}
