// I/O of numbers.

#ifndef _CL_NUMBER_IO_H
#define _CL_NUMBER_IO_H

#include "cln/io.h"
#include "cln/number.h"

namespace cln {

// Input.

// Finish with bad syntax.
#ifdef _CL_MACROS_H
nonreturning_function(extern, read_number_bad_syntax, (const char * string, const char * string_limit));
#else
extern void read_number_bad_syntax (const char * string, const char * string_limit);
#endif

// Finish with junk after the number.
#ifdef _CL_MACROS_H
nonreturning_function(extern, read_number_junk, (const char * string_rest, const char * string, const char * string_limit));
#else
extern void read_number_junk (const char * string_rest, const char * string, const char * string_limit);
#endif

// Finish with EOF.
#ifdef _CL_MACROS_H
nonreturning_function(extern, read_number_eof, (void));
#else
extern void read_number_eof (void);
#endif

struct cl_read_flags;

}  // namespace cln

#endif /* _CL_NUMBER_IO_H */
