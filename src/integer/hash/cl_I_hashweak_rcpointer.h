// cl_I hash tables

#ifndef _CL_I_HASHWEAK_RCPOINTER_H
#define _CL_I_HASHWEAK_RCPOINTER_H

#include "cl_number.h"
#include "cl_integer.h"

// For the sake of gcc-2.7.x, this declaration must come before cl_hash1.h.
extern unsigned long hashcode (const cl_I& x);

#include "cl_hash1weak.h"

// Equality.
static inline bool equal (const cl_I& x, const cl_I& y)
{ return (bool)cl_equal(x,y); }

typedef cl_htentry1<cl_I,cl_rcpointer> cl_htentry_from_integer_to_rcpointer;

typedef cl_heap_weak_hashtable_1<cl_I,cl_rcpointer> cl_heap_weak_hashtable_from_integer_to_rcpointer;

typedef _cl_hashtable_iterator<cl_htentry_from_integer_to_rcpointer> cl_hashtable_from_integer_to_rcpointer_iterator;

struct cl_wht_from_integer_to_rcpointer : public cl_gcpointer {
	// Constructors.
	cl_wht_from_integer_to_rcpointer (cl_boolean (*maygc_htentry) (const cl_htentry_from_integer_to_rcpointer&));
	cl_wht_from_integer_to_rcpointer (const cl_wht_from_integer_to_rcpointer&);
	// Assignment operators.
	cl_wht_from_integer_to_rcpointer& operator= (const cl_wht_from_integer_to_rcpointer&);
	// Iterator.
	cl_hashtable_from_integer_to_rcpointer_iterator iterator () const
	{ return ((cl_heap_weak_hashtable_from_integer_to_rcpointer*)pointer)->iterator(); }
	// Lookup.
	cl_rcpointer * get (const cl_I& x) const;
	// Store.
	void put (const cl_I& x, const cl_rcpointer& y) const;
};

#endif /* _CL_I_HASHWEAK_RCPOINTER_H */
