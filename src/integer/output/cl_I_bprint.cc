// print_integer().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer_io.h"


// Implementation.

#include "cl_output.h"

void print_integer (cl_ostream stream, const cl_print_number_flags& flags, const cl_I& z)
{
	print_integer(stream,(const cl_print_real_flags&)flags,z);
}
