// print_vector().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_GV_complex.h"
#include "cl_GV_real.h"
#include "cl_GV_rational.h"
#include "cl_GV_integer.h"
#include "cl_GV_io.h"


// Implementation.

#include "cl_output.h"

void print_vector (cl_ostream stream, const cl_print_flags& flags, void (* printfun) (cl_ostream, const cl_print_flags&, const cl_number&), const cl_GV_number& vector)
{
	var uintL len = vector.length();
	if (flags.vector_syntax == vsyntax_commonlisp) {
		fprintchar(stream,'#');
		fprintchar(stream,'(');
	} else
		fprintchar(stream,'[');
	for (var uintL i = 0; i < len; i++) {
		if (i > 0) {
			if (flags.vector_syntax == vsyntax_algebraic)
				fprintchar(stream,',');
			fprintchar(stream,' ');
		}
		// The conversion to cl_number below is needed for SGI CC.
		printfun(stream,flags,(cl_number)vector[i]);
	}
	if (flags.vector_syntax == vsyntax_commonlisp)
		fprintchar(stream,')');
	else
		fprintchar(stream,']');
}
