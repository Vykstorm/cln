// cl_make_heap_SV_number().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_SV_number)

// Specification.
#include "cl_SV_number.h"


// Implementation.

#include "cl_abort.h"


static void cl_svector_number_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_SV_number*)pointer).~cl_heap_SV();
#else
	(*(cl_heap_SV_number*)pointer).~cl_heap_SV_number();
#endif
}

cl_class cl_class_svector_number = {
	cl_svector_number_destructor,
	0
};

cl_heap_SV_number* cl_make_heap_SV_number_uninit (uintL len)
{
	var cl_heap_SV_number* hv = (cl_heap_SV_number*) cl_malloc_hook(sizeof(cl_heap_SV_number)+sizeof(cl_number)*len);
	hv->refcount = 1;
	hv->type = &cl_class_svector_number;
	new (&hv->v) cl_SV_inner<cl_number> (len);
	// Have to fill hv->v[i] (0 <= i < len) yourself.
	return hv;
}

cl_heap_SV_number* cl_make_heap_SV_number (uintL len)
{
	var cl_heap_SV_number* hv = (cl_heap_SV_number*) cl_malloc_hook(sizeof(cl_heap_SV_number)+sizeof(cl_number)*len);
	hv->refcount = 1;
	hv->type = &cl_class_svector_number;
	new (&hv->v) cl_SV_inner<cl_number> (len);
	for (var uintL i = 0; i < len; i++)
		init1(cl_number, hv->v[i]) (0);
	return hv;
}

// An empty vector.
const cl_SV_number cl_null_SV_number = cl_SV_number((uintL)0);

CL_PROVIDE_END(cl_SV_number)
