// read_complex().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex_io.h"


// Implementation.

#include "cln/io.h"
#include "cl_spushstring.h"
#include "cln/input.h"

namespace cln {

// We read an entire token (or even more, if it begins with #C) into a
// buffer and then call read_complex() on the buffer.

class pushstring_hack : public cl_spushstring {
public:
	char* start_pointer (void) { return buffer; }
	char* end_pointer (void) { return buffer+index; }
};

static bool number_char_p (char c)
{
	if ((c >= '0') && (c <= '9'))
		return true;
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
		return true;
	switch (c) {
		case '+': case '-': case '.': case '_': case '/':
			return true;
		default:
			return false;
	}
}

const cl_N read_complex (std::istream& stream, const cl_read_flags& flags)
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
		// Read some digits, then a letter, then a list or token.
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
		if (c == '(') {
			var uintL paren_level = 0;
			loop {
				buffer.push(c);
				if (c == '(') paren_level++;
				else if (c == ')') paren_level--;
				if (paren_level == 0) goto done;
				c = freadchar(stream);
				if ((c == cl_EOF) || (c == '\n')) goto syntax;
			}
		}
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
done:
	// Parse the number.
	return read_complex(flags,
	                    buffer.start_pointer(), buffer.end_pointer(),
	                    NULL
	                   );

	// Handle syntax error.
syntax1:	buffer.push(c);
syntax:	throw read_number_bad_syntax_exception(buffer.start_pointer(),buffer.end_pointer());

	// Handle premature EOF.
eof:	throw read_number_eof_exception();
}

}  // namespace cln
