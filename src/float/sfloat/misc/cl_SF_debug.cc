// cl_SF debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_sfloat.h"
#include "cl_io.h"
#include "cl_float_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_SF& obj = *(const cl_SF*)&pointer;
	fprint(cl_debugout, "(cl_SF) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_SF)
{ cl_register_type_printer(cl_class_sfloat,dprint); }

// This dummy links in this module when <cl_sfloat.h> requires it.
int cl_SF_debug_module;
