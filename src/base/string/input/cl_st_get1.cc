// cl_fget().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/string.h"


// Implementation.

#include "cln/io.h"
#include "cl_spushstring.h"

namespace cln {

const cl_string cl_fget (cl_istream stream, char delim)
{
	var cl_spushstring buffer;
	// Handling of eofp is tricky: EOF is reached when (!stream.good()) || (stream.get()==EOF).
	while (stream.good()) {
		var int c = stream.get();
		if (c==EOF)
			break;	// std::ios::eofbit already set
		if (c==delim) {
			stream.unget();
			break;
		}
		buffer.push(c);
	}
	return buffer.contents();
}

}  // namespace cln
