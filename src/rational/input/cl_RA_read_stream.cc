// read_rational().
// This file contains a slimmed down version of read_real().
// It does not pull in all the floating-point, complex and transcendental
// function code.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational_io.h"


// Implementation.

#include "cln/input.h"
#include "cln/io.h"
#include "cl_spushstring.h"

namespace cln {

// We read an entire token (or even more, if it begins with #C) into a
// buffer and then call read_rational() on the buffer.

class pushstring_hack : public cl_spushstring {
public:
	char* start_pointer (void) { return buffer; }
	char* end_pointer (void) { return buffer+index; }
};

static cl_boolean number_char_p (char c)
{
	if ((c >= '0') && (c <= '9'))
		return cl_true;
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
		return cl_true;
	switch (c) {
		case '+': case '-': case '.': case '_': case '/':
			return cl_true;
		default:
			return cl_false;
	}
}

const cl_RA read_rational (std::istream& stream, const cl_read_flags& flags)
{
	// One pre-allocated buffer. This reduces the allocation/free cost.
	static pushstring_hack buffer;

	var int c;
	// Skip whitespace at the beginning.
	loop {
		c = freadchar(stream);
		if (c == cl_EOF) goto eof;
		if ((c == ' ') || (c == '\t') || (c == '\n'))
			continue;
		else
			break;
	}
	// Found first non-whitespace character.
	// Numbers cannot cross lines. We can treat EOF and '\n' the same way.
	buffer.reset();
	if (c == '#') {
		if (!(flags.lsyntax & lsyntax_commonlisp))
			goto syntax1;
		buffer.push(c);
		// Read some digits, then a letter, then a token.
		loop {
			c = freadchar(stream);
			if (c == cl_EOF) goto eof;
			buffer.push(c);
			if ((c >= '0') && (c <= '9'))
				continue;
			else
				break;
		}
		if (!(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'))))
			goto syntax1;
		c = freadchar(stream);
		if (c == cl_EOF) goto eof;
	}
	// Read a number token.
	if (!number_char_p(c))
		goto syntax1;
	loop {
		buffer.push(c);
		c = freadchar(stream);
		if (c == cl_EOF)
			break;
		if (!number_char_p(c)) {
			funreadchar(stream,c);
			break;
		}
	}
	// Parse the number.
	return read_rational(flags,
	                     buffer.start_pointer(), buffer.end_pointer(),
	                     NULL
	                    );

	// Handle syntax error.
syntax1:	buffer.push(c);
	read_number_bad_syntax(buffer.start_pointer(),buffer.end_pointer());

	// Handle premature EOF.
eof:	read_number_eof();
}

}  // namespace cln
