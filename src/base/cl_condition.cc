// Conditions.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_condition.h"


// Implementation.

// This tells the compiler to put the `cl_condition' vtable into this file.
void cl_condition::dummy () {}

// The destructor must be defined although it is virtual and abstract.
#if !(defined(__GNUC__) && (__GNUC__ == 2) && (__GNUC_MINOR__ < 8))
cl_condition::~cl_condition () {}
#endif
