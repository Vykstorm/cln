// I/O through <iostream>

#ifndef _CL_IO_H
#define _CL_IO_H

#include "cln/types.h"
#include "cln/modules.h"

// I/O through <iostream>

#ifdef floor
  #undef floor
  #include <iostream>
  #define floor cln_floor
#else
  #include <iostream>
#endif

namespace cln {

typedef std::istream& cl_istream;
typedef std::ostream& cl_ostream;
extern std::ostream* cl_debugout_stream;
#define cl_debugout  (*cl_debugout_stream)

// Elementary operations on cl_istream

#define cl_EOF  (-1)

inline int freadchar (cl_istream stream)
{
	char c;
	if (stream.get(c))
		return c;
	else
		// EOF or error
		return cl_EOF;
}

inline int funreadchar (cl_istream stream, int c)
{
	if (c != cl_EOF)
		stream.putback((char)c);
	return c;
}

// Elementary operations on cl_ostream

inline void fprintchar (cl_ostream stream, char c)
{
	stream.put(c);
}

inline void fprint (cl_ostream stream, const char * string)
{
	stream << string;
}


extern void fprintdecimal (cl_ostream stream, unsigned long x);
extern void fprintdecimal (cl_ostream stream, long x);

inline void fprintdecimal (cl_ostream stream, unsigned int x)
{
	fprintdecimal(stream,(unsigned long)x);
}
inline void fprintdecimal (cl_ostream stream, int x)
{
	fprintdecimal(stream,(long)x);
}

extern void fprinthexadecimal (cl_ostream stream, unsigned long x);
extern void fprinthexadecimal (cl_ostream stream, long x);

inline void fprinthexadecimal (cl_ostream stream, unsigned int x)
{
	fprinthexadecimal(stream,(unsigned long)x);
}
inline void fprinthexadecimal (cl_ostream stream, int x)
{
	fprinthexadecimal(stream,(long)x);
}


class cl_print_flags;
class cl_print_number_flags;
class cl_print_real_flags;
class cl_print_rational_flags;
class cl_print_float_flags;
CL_REQUIRE(cl_prin_globals)


// Define the customary << and >> operators.

#define CL_DEFINE_PRINT_OPERATOR(_class_)  \
inline cl_ostream operator<< (cl_ostream stream, const _class_& x)	\
{									\
	fprint(stream,x);						\
	return stream;							\
}
	
}  // namespace cln

#endif /* _CL_IO_H */
