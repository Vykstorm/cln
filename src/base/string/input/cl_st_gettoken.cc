// operator>>.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/string.h"


// Implementation.

#include "cln/io.h"
#include "cl_spushstring.h"
#include <cctype>

namespace cln {

std::istream& operator>> (std::istream& stream, cl_string& str)
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

}  // namespace cln
