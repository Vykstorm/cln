// cl_F (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float_class.h"


// Implementation.

#include "cl_float.h"
#include "cl_input.h"
#include "cl_float_io.h"

cl_read_flags cl_F_read_flags = {
	syntax_float,
	lsyntax_all,
	10,
	{ cl_float_format_ffloat, cl_float_format_lfloat_min, cl_true }
};

cl_F::cl_F (const char * string)
{
	pointer = as_cl_private_thing(
		read_float(cl_F_read_flags,string,NULL,NULL));
}
