// I/O through <stdio.h> or <iostream.h>

#ifndef _CL_IO_H
#define _CL_IO_H

#include "cl_types.h"
#include "cl_modules.h"

#if !defined(CL_IO_STDIO) && !defined(CL_IO_IOSTREAM)
// Prefer iostream based I/O - this is what people expect.
#define CL_IO_IOSTREAM
#endif


#if defined(CL_IO_STDIO)

// I/O through <stdio.h>

#include <stdio.h>

#define cl_istream  FILE *
#define cl_ostream  FILE *
#define cl_stdin   stdin
#define cl_stdout  stdout
#define cl_stderr  stderr
extern FILE* cl_debugout;

// Elementary operations on cl_istream

#define cl_EOF  EOF

inline int freadchar (cl_istream stream)
{
	// return fgetc(stream);
	return getc(stream);
}

inline int funreadchar (cl_istream stream, int c)
{
	return ungetc(c,stream);
}

// Elementary operations on cl_ostream

inline void fprintchar (cl_ostream stream, char c)
{
	// fputc(c,stream);
	putc(c,stream);
}

inline void fprint (cl_ostream stream, const char * string)
{
	// fprintf(stream,"%s",string);
	fputs(string,stream);
}

#endif


#if defined(CL_IO_IOSTREAM)

// I/O through <iostream.h>

#ifdef floor
  #undef floor
  #include <iostream.h>
  #define floor cln_floor
#else
  #include <iostream.h>
#endif

#define cl_istream  istream&
#define cl_ostream  ostream&
#define cl_stdin   cin
#define cl_stdout  cout
#define cl_stderr  cerr
extern ostream* cl_debugout_stream;
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

#endif


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


#endif /* _CL_IO_H */
