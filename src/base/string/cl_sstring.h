// Simple strings.

#ifndef _CL_SSTRING_H
#define _CL_SSTRING_H

// Liefert einen String.
// Mit cl_malloc_hook() alloziert, mit cl_free_hook() freizugeben.
extern char * cl_sstring (const char * ptr, uintL len);

#endif /* _CL_SSTRING_H */
