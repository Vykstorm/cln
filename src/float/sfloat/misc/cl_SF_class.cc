// cl_class_sfloat.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

cl_class cl_class_sfloat = {
	NULL,		// destructor not used, since not heap objects
	cl_class_flags_subclass_complex | cl_class_flags_subclass_real | cl_class_flags_subclass_float
};

AT_INITIALIZATION(ini_class_sfloat)
{
	cl_immediate_classes[cl_SF_tag] = &cl_class_sfloat;
}
