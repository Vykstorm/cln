// cl_LF (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat_class.h"


// Implementation.

#include "cl_lfloat.h"
#include "cl_input.h"
#include "cl_float_io.h"

cl_read_flags cl_LF_read_flags = {
	syntax_lfloat,
	lsyntax_all,
	10,
	{ cl_float_format_lfloat_min, cl_float_format_lfloat_min, cl_false }
};

cl_LF::cl_LF (const char * string)
{
	pointer = as_cl_private_thing(
		As(cl_LF)(read_float(cl_LF_read_flags,string,NULL,NULL)));
}
