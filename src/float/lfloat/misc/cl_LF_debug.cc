// cl_LF debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_lfloat.h"
#include "cl_io.h"
#include "cl_float_io.h"

static void dprint (cl_heap* pointer)
{
	var const cl_LF& obj = *(const cl_LF*)&pointer;
	fprint(cl_debugout, "(cl_LF) ");
	fprint(cl_debugout, obj);
}
AT_INITIALIZATION(dprint_LF)
{ cl_register_type_printer(cl_class_lfloat,dprint); }

// This dummy links in this module when <cl_lfloat.h> requires it.
int cl_LF_debug_module;
