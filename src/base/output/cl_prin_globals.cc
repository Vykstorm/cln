// Global variables in CLN

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_prin_globals)

// Specification.
#include "cln/output.h"


// Implementation.

namespace cln {

cl_print_flags default_print_flags;
#if 0 // The default constructors already do this.
AT_INITIALIZATION(default_print_flags)
{
	default_print_flags.rational_base = 10;
	default_print_flags.rational_readably = cl_false;
	default_print_flags.float_readably = cl_false;
	default_print_flags.default_float_format = float_format_ffloat;
	default_print_flags.complex_readably = cl_false;
	default_print_flags.vector_syntax = vsyntax_pretty;
	default_print_flags.univpoly_varname = "x";
}
#endif

}  // namespace cln

CL_PROVIDE_END(cl_prin_globals)
