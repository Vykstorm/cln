// cl_SV_ringelt debugging support.

// General includes.
#include "cl_sysdep.h"

// Specification.


// Implementation.

#include "cl_SV_ringelt.h"
#include "cl_io.h"

extern void cl_dprint_unknown (cl_heap* pointer);
static void dprint (cl_heap* pointer)
{
//	var const cl_SV_ringelt& obj = *(const cl_SV_ringelt*)&pointer;
	fprint(cl_debugout, "(cl_SV_ringelt) ");
	cl_dprint_unknown(pointer);
}
AT_INITIALIZATION(dprint_SV_ringelt)
{ cl_register_type_printer(cl_class_svector_ringelt,dprint); }

// This dummy links in this module when <cl_SV_ringelt.h> requires it.
int cl_SV_ringelt_debug_module;
