// read_integer().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer_io.h"


// Implementation.

#include "cl_I.h"

const cl_I read_integer (unsigned int base, cl_signean sign, const char * string, uintL index1, uintL index2)
{
	var cl_I x = digits_to_I(&string[index1],index2-index1,(uintD)base);
	if (sign == 0)
		return x;
	else
		return -x; // negatives Vorzeichen -> Vorzeichenwechsel
}
