// Global variables in CLN

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_prin_globals)

// Specification.
#include "cl_output.h"


// Implementation.

cl_print_flags cl_default_print_flags;
#if 0 // The default constructors already do this.
AT_INITIALIZATION(cl_default_print_flags)
{
	cl_default_print_flags.rational_base = 10;
	cl_default_print_flags.rational_readably = cl_false;
	cl_default_print_flags.float_readably = cl_false;
	cl_default_print_flags.default_float_format = cl_float_format_ffloat;
	cl_default_print_flags.complex_readably = cl_false;
	cl_default_print_flags.vector_syntax = vsyntax_pretty;
	cl_default_print_flags.univpoly_varname = "x";
}
#endif

CL_PROVIDE_END(cl_prin_globals)
