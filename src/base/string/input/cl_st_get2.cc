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
// Sun C++ doesn't have istream::unget() and istream::set().
  #define unget()  putback(c)
  #define set(x)  setf(x)
#endif

const cl_string cl_fget (cl_istream stream, int n, char delim)
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
		if (--n <= 0) {
			stream.unget();
			#if defined(__GNUG__) && (__GNUC_MINOR__ < 8)
			stream.set(ios::failbit);
			#else // new ANSI C++
			stream.setstate(ios::failbit);
			#endif
			break;
		}
		buffer.push(c);
	}
	return buffer.contents();
}

#endif
