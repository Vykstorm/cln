// operator>>.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_string.h"


// Implementation.

#ifdef CL_IO_IOSTREAM

#include "cl_io.h"
#include "cl_spushstring.h"
#include <ctype.h>

#if ((defined(__sparc__) || defined(__rs6000__) || defined(__mips__)) && !defined(__GNUC__))
// Sun C++ doesn't have istream::unget().
  #define unget()  putback(c)
#endif

cl_istream operator>> (cl_istream stream, cl_string& str)
{
	var cl_spushstring buffer;
	var int n = stream.width();
	// Handling of eofp is tricky: EOF is reached when (!stream.good()) || (stream.get()==EOF).
	int c;
	// Skip whitespace.
	while (stream.good()) {
		c = stream.get();
		if (c==EOF)
			break;
		if (!isspace(c)) {
			if (--n == 0) {
				// stream.width()==1, means no characters.
				stream.unget();
				break;
			}
			// If stream.width()==0, n gets negative and never 0.
			goto nonws;
		}
	}
	goto done;
	// Read non-whitespace.
	while (stream.good()) {
		c = stream.get();
		if (c==EOF)
			break;
		if (isspace(c)) {
			stream.unget();
			break;
		}
	    nonws:
		buffer.push(c);
		if (--n == 0)
			break;
	}
    done:
	str = buffer.contents();
	stream.width(0);
	return stream;
}

#endif
