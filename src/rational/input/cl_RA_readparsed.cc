// read_rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational_io.h"


// Implementation.

#include "cl_RA.h"
#include "cl_I.h"
#include "cl_N.h"

const cl_RA read_rational (unsigned int base, cl_signean sign, const char * string, uintL index1, uintL index3, uintL index2)
{
	var uintL index3_1 = index3+1; // Index der ersten Nennerziffer
	var cl_I den = // Nenner
	  digits_to_I(&string[index3_1],index2-index3_1,(uintD)base);
	if (zerop(den)) // Division durch 0 abfangen
		{ cl_error_division_by_0(); }
	var cl_I num = // Zähler
	  digits_to_I(&string[index1],index3-index1,(uintD)base);
	if (!(sign == 0))
		num = -num; // incl. Vorzeichen
	return I_posI_div_RA(num,den);
}
