// print_real().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real_io.h"


// Implementation.

#include "cl_output.h"

void print_real (cl_ostream stream, const cl_print_flags& flags, const cl_R& z)
{
	print_real(stream,(const cl_print_number_flags&)flags,z);
}
