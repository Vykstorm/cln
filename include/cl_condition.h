// Conditions (a.k.a. exceptions)

#ifndef _CL_CONDITION_H
#define _CL_CONDITION_H

#include "cl_malloc.h"
#include "cl_io.h"

struct cl_condition {
	// Allocation.
	void* operator new (size_t size) { return cl_malloc_hook(size); }
	// Deallocation.
	void operator delete (void* ptr) { cl_free_hook(ptr); }
	// Name.
	virtual const char * name () const = 0;
	// Print.
	virtual void print (cl_ostream) const = 0;
	// Virtual destructor.
	virtual ~cl_condition ()
	#if defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ < 8) // workaround gcc bug
		{}
	#else
		= 0;
	#endif
private:
	virtual void dummy ();
};
#define SUBCLASS_cl_condition() \
public:									  \
	/* Allocation. */						  \
	void* operator new (size_t size) { return cl_malloc_hook(size); } \
	/* Deallocation. */						  \
	void operator delete (void* ptr) { cl_free_hook(ptr); }

// Functions which want to raise a condition return a `cl_condition*'.
// The caller checks this value. NULL means no condition. The one who
// disposes the condition (handles it without resignalling it) should
// call `delete' on the condition pointer.

#endif /* _CL_CONDITION_H */
