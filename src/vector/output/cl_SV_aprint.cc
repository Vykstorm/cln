// fprint() for cl_SV_ringelt.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/SV_ringelt.h"


// Implementation.

#include "cln/output.h"

namespace cln {

void fprint (std::ostream& stream, const cl_ring& R, const cl_SV_ringelt& vector)
{
	var const cl_print_flags& flags = default_print_flags;
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
		R->_fprint(stream,vector[i]);
	}
	if (flags.vector_syntax == vsyntax_commonlisp)
		fprintchar(stream,')');
	else
		fprintchar(stream,']');
}

}  // namespace cln
