// print_vector().

// General includes.
#include "base/cl_sysdep.h"

// Specification.
#include "cln/SV_complex.h"
#include "cln/SV_real.h"
#include "cln/SV_rational.h"
#include "cln/SV_integer.h"
#include "vector/cl_SV_io.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void print_vector (std::ostream& stream, const cl_print_flags& flags, void (* printfun) (std::ostream&, const cl_print_flags&, const cl_number&), const cl_SV_number& vector)
{
	var uintC len = vector.length();
	if (flags.vector_syntax == vsyntax_commonlisp) {
		fprintchar(stream,'#');
		fprintchar(stream,'(');
	} else
		fprintchar(stream,'[');
	for (var uintC i = 0; i < len; i++) {
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
