// class cl_composite_condition.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_modinteger.h"


// Implementation.

#include "cl_io.h"
#include "cl_integer_io.h"

const char * cl_composite_condition::name () const
{ return "cl_composite_condition"; }

void cl_composite_condition::print (cl_ostream strm) const
{
	fprint(strm, "Exception <cl_composite_condition> occurred: p = ");
	fprint(strm, p);
	fprint(strm, " is not a prime, ");
	if (zerop(factor))
		fprint(strm, "no factor found");
	else {
		fprint(strm, "factor found: ");
		fprint(strm, factor);
	}
	fprint(strm, "\n");
}
