// cl_SF (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat_class.h"


// Implementation.

#include "cl_sfloat.h"
#include "cl_input.h"
#include "cl_float_io.h"

cl_read_flags cl_SF_read_flags = {
	syntax_sfloat,
	lsyntax_all,
	10,
	{ cl_float_format_sfloat, cl_float_format_lfloat_min, cl_false }
};

cl_SF::cl_SF (const char * string)
{
	pointer = as_cl_private_thing(
		As(cl_SF)(read_float(cl_SF_read_flags,string,NULL,NULL)));
}
