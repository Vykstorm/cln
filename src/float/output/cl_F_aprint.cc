// print_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float_io.h"


// Implementation.

#include "cl_output.h"

void print_float (cl_ostream stream, const cl_print_flags& flags, const cl_F& z)
{
	print_float(stream,(const cl_print_number_flags&)flags,z);
}
