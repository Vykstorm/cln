// cl_C debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_complex.h"
#include "cl_io.h"
#include "cl_complex_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_N& obj = *(const cl_N*)&pointer;
	fprint(cl_debugout, "(cl_N) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_N)
{ cl_register_type_printer(cl_class_complex,dprint); }

// This dummy links in this module when <cl_complex.h> requires it.
int cl_C_debug_module;

extern int cl_R_debug_module;
static void* dummy[] = { &dummy,
	&cl_R_debug_module
};
