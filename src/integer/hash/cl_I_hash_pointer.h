// cl_I hash tables

#ifndef _CL_I_HASH_POINTER_H
#define _CL_I_HASH_POINTER_H

#include "cl_number.h"
#include "cl_integer.h"

// For the sake of gcc-2.7.x, this declaration must come before cl_hash1.h.
extern unsigned long hashcode (const cl_I& x);

#include "cl_hash1.h"

// Equality.
static inline bool equal (const cl_I& x, const cl_I& y)
{ return (bool)cl_equal(x,y); }

typedef cl_htentry1<cl_I,void*> cl_htentry_from_integer_to_pointer;

typedef cl_heap_hashtable_1<cl_I,void*> cl_heap_hashtable_from_integer_to_pointer;

typedef _cl_hashtable_iterator<cl_htentry_from_integer_to_pointer> cl_hashtable_from_integer_to_pointer_iterator;

struct cl_ht_from_integer_to_pointer : public cl_gcpointer {
	// Constructors.
	cl_ht_from_integer_to_pointer ();
	cl_ht_from_integer_to_pointer (const cl_ht_from_integer_to_pointer&);
	// Assignment operators.
	cl_ht_from_integer_to_pointer& operator= (const cl_ht_from_integer_to_pointer&);
	// Iterator.
	cl_hashtable_from_integer_to_pointer_iterator iterator () const
	{ return ((cl_heap_hashtable_from_integer_to_pointer*)pointer)->iterator(); }
	// Lookup.
	void* * get (const cl_I& x) const;
	// Store.
	void put (const cl_I& x, void* y) const;
};

#endif /* _CL_I_HASH_POINTER_H */
