// cl_DF (const char *) constructor.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat_class.h"


// Implementation.

#include "cl_dfloat.h"
#include "cl_input.h"
#include "cl_float_io.h"

cl_read_flags cl_DF_read_flags = {
	syntax_dfloat,
	lsyntax_all,
	10,
	{ cl_float_format_dfloat, cl_float_format_lfloat_min, cl_false }
};

cl_DF::cl_DF (const char * string)
{
	pointer = as_cl_private_thing(
		As(cl_DF)(read_float(cl_DF_read_flags,string,NULL,NULL)));
}
