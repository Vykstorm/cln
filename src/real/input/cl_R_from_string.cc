// cl_R (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real_class.h"


// Implementation.

#include "cl_input.h"
#include "cl_real_io.h"

cl_read_flags cl_R_read_flags = {
	syntax_real,
	lsyntax_all,
	10,
	{ cl_float_format_ffloat, cl_float_format_lfloat_min, cl_true }
};

cl_R::cl_R (const char * string)
{
	pointer = as_cl_private_thing(
		read_real(cl_R_read_flags,string,NULL,NULL));
}
