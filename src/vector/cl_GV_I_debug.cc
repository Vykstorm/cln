// cl_GV_I debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_GV_integer.h"
#include "cl_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_GV_I& obj = *(const cl_GV_I*)&pointer;
	fprint(cl_debugout, "(cl_GV_I) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_GV_I)
{ cl_register_type_printer(cl_class_gvector_integer,dprint); }

// This dummy links in this module when <cl_GV_integer.h> requires it.
int cl_GV_I_debug_module;
