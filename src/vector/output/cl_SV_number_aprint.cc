// print_vector().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/SV_complex.h"
#include "cln/SV_real.h"
#include "cln/SV_rational.h"
#include "cln/SV_integer.h"
#include "cl_SV_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_vector (cl_ostream stream, const cl_print_flags& flags, void (* printfun) (cl_ostream, const cl_print_flags&, const cl_number&), const cl_SV_number& vector)
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
		printfun(stream,flags,vector[i]);
	}
	if (flags.vector_syntax == vsyntax_commonlisp)
		fprintchar(stream,')');
	else
		fprintchar(stream,']');
}

}  // namespace cln
