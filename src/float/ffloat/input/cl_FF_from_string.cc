// cl_FF (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat_class.h"


// Implementation.

#include "cl_ffloat.h"
#include "cl_input.h"
#include "cl_float_io.h"

cl_read_flags cl_FF_read_flags = {
	syntax_ffloat,
	lsyntax_all,
	10,
	{ cl_float_format_ffloat, cl_float_format_lfloat_min, cl_false }
};

cl_FF::cl_FF (const char * string)
{
	pointer = as_cl_private_thing(
		As(cl_FF)(read_float(cl_FF_read_flags,string,NULL,NULL)));
}
