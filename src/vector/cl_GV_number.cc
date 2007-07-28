// cl_make_heap_GV_number().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_GV_number)

// Specification.
#include "cln/GV_number.h"


// Implementation.

#include "cln/exception.h"
#include "cl_offsetof.h"

namespace cln {

static void cl_gvector_number_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_GV_number*)pointer).~cl_heap_GV();
#else
	(*(cl_heap_GV_number*)pointer).~cl_heap_GV_number();
#endif
}

cl_class cl_class_gvector_number = {
	cl_gvector_number_destructor,
	0
};


static inline cl_heap_GV_number * outcast (cl_GV_inner<cl_number>* vec)
{
	return (cl_heap_GV_number *)((char *) vec - offsetof(cl_heap_GV_number,v));
}
static inline const cl_heap_GV_number * outcast (const cl_GV_inner<cl_number>* vec)
{
	return (const cl_heap_GV_number *)((const char *) vec - offsetof(cl_heap_GV_number,v));
}


// Vectors of numbers.

struct cl_heap_GV_number_general : public cl_heap_GV_number {
	cl_number data[1];
	// Standard allocation disabled.
	void* operator new (size_t size) { unused size; throw runtime_exception(); }
	// Standard deallocation disabled.
	void operator delete (void* ptr) { unused ptr; throw runtime_exception(); }
	// No default constructor.
	cl_heap_GV_number_general ();
};

static const cl_number general_element (const cl_GV_inner<cl_number>* vec, uintC index)
{
	return ((const cl_heap_GV_number_general *) outcast(vec))->data[index];
}

static void general_set_element (cl_GV_inner<cl_number>* vec, uintC index, const cl_number& x)
{
	((cl_heap_GV_number_general *) outcast(vec))->data[index] = x;
}

static void general_do_delete (cl_GV_inner<cl_number>* vec)
{
	var cl_heap_GV_number_general* hv = (cl_heap_GV_number_general *) outcast(vec);
	var uintC len = hv->v.length();
	for (var uintC i = 0; i < len; i++)
		hv->data[i].~cl_number();
}

static void general_copy_elements (const cl_GV_inner<cl_number>* srcvec, uintC srcindex, cl_GV_inner<cl_number>* destvec, uintC destindex, uintC count)
{
	if (count > 0) {
		var const cl_heap_GV_number_general* srcv =
		  (const cl_heap_GV_number_general *) outcast(srcvec);
		var cl_heap_GV_number_general* destv =
		  (cl_heap_GV_number_general *) outcast(destvec);
		var uintC srclen = srcv->v.length();
		var uintC destlen = destv->v.length();
		if (!(srcindex <= srcindex+count && srcindex+count <= srclen))
			throw runtime_exception();
		if (!(destindex <= destindex+count && destindex+count <= destlen))
			throw runtime_exception();
		do {
			destv->data[destindex++] = srcv->data[srcindex++];
		} while (--count > 0);
	}
}

static cl_GV_vectorops<cl_number> general_vectorops = {
	general_element,
	general_set_element,
	general_do_delete,
	general_copy_elements
};

cl_heap_GV_number* cl_make_heap_GV_number (uintC len)
{
	var cl_heap_GV_number_general* hv = (cl_heap_GV_number_general*) malloc_hook(offsetofa(cl_heap_GV_number_general,data)+sizeof(cl_number)*len);
	hv->refcount = 1;
	hv->type = &cl_class_gvector_number;
	new (&hv->v) cl_GV_inner<cl_number> (len,&general_vectorops);
	for (var uintC i = 0; i < len; i++)
		init1(cl_number, hv->data[i]) ();
	return hv;
}

// An empty vector.
const cl_GV_number cl_null_GV_number = cl_GV_number((uintC)0);

}  // namespace cln

CL_PROVIDE_END(cl_GV_number)
