// cl_fget().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#ifdef CL_IO_IOSTREAM

#include "cl_io.h"
#include "cl_spushstring.h"

#if ((defined(__sparc__) || defined(__rs6000__) || defined(__mips__)) && !defined(__GNUC__))
// Sun C++ doesn't have istream::unget().
  #define unget()  putback(c)
#endif

const cl_string cl_fget (cl_istream stream, char delim)
{
	var cl_spushstring buffer;
	// Handling of eofp is tricky: EOF is reached when (!stream.good()) || (stream.get()==EOF).
	while (stream.good()) {
		var int c = stream.get();
		if (c==EOF)
			break;	// ios::eofbit already set
		if (c==delim) {
			stream.unget();
			break;
		}
		buffer.push(c);
	}
	return buffer.contents();
}

#endif
