// Extendable strings.

#ifndef _CL_SPUSHSTRING_H
#define _CL_SPUSHSTRING_H

#include "cl_object.h"
#include "cl_malloc.h"
#include "cl_sstring.h"
#include "cl_abort.h"

class cl_spushstring {
protected:
	char * buffer;
	uintL alloc; // allocated size of buffer
	uintL index; // index into buffer, 0 <= index <= alloc
public:
// Constructor. When constructed, the string is empty.
	cl_spushstring ();
// Destructor.
	~cl_spushstring ();
// Forget the contents.
	void reset ();
// Add a character at the end.
	void push (char);
// Adds several characters at the end at once.
	void append (const char * ptr, uintL len);
// Get the contents as a string. Free it using cl_free_hook() when done.
	char* contents ();
// Look at the contents.
	uintL length () const;
	char operator[] (uintL i) const;
};
inline cl_spushstring::cl_spushstring ()
{
	alloc = 20; // Must be > 0.
	buffer = (char *) cl_malloc_hook(alloc);
	index = 0;
}
inline cl_spushstring::~cl_spushstring ()
{
	cl_free_hook(buffer);
}
inline void cl_spushstring::reset ()
{
	index = 0;
}
inline char* cl_spushstring::contents ()
{
	return cl_sstring(buffer,index);
}
inline uintL cl_spushstring::length () const
{
	return index;
}
inline char cl_spushstring::operator[] (uintL i) const
{
	if (!(i < index)) cl_abort();
	return buffer[i];
}

#endif /* _CL_SPUSHSTRING_H */
