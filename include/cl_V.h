// Vectors.

#ifndef _CL_V_H
#define _CL_V_H

#include "cl_object.h"

struct cl_V_any : public cl_gcpointer {
	// Constructors.
	cl_V_any () {}
	cl_V_any (const cl_V_any&);
	cl_V_any (cl_private_thing p) : cl_gcpointer (p) {}
	// Assignment operators.
	cl_V_any& operator= (const cl_V_any&);
};
CL_DEFINE_COPY_CONSTRUCTOR2(cl_V_any,cl_gcpointer)
CL_DEFINE_ASSIGNMENT_OPERATOR(cl_V_any,cl_V_any)

#endif /* _CL_V_H */
