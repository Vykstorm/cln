// cl_I (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer_class.h"


// Implementation.

#include "cl_input.h"
#include "cl_integer_io.h"

cl_read_flags cl_I_read_flags = {
	syntax_integer,
	lsyntax_all,
	10,
	{ cl_float_format_ffloat, cl_float_format_lfloat_min, cl_true }
};

cl_I::cl_I (const char * string)
{
	pointer = as_cl_private_thing(
		read_integer(cl_I_read_flags,string,NULL,NULL));
}
