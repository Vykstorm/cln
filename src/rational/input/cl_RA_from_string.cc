// cl_RA (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational_class.h"


// Implementation.

#include "cl_input.h"
#include "cl_rational_io.h"

cl_read_flags cl_RA_read_flags = {
	syntax_rational,
	lsyntax_all,
	10,
	{ cl_float_format_ffloat, cl_float_format_lfloat_min, cl_true }
};

cl_RA::cl_RA (const char * string)
{
	pointer = as_cl_private_thing(
		read_rational(cl_RA_read_flags,string,NULL,NULL));
}
