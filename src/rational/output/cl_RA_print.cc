// print_rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational_io.h"


// Implementation.

#include "cl_integer_io.h"
#include "cl_rational.h"
#include "cl_RA.h"

void print_rational (cl_ostream stream, unsigned int base, const cl_RA& z)
{
	if (integerp(z)) {
		DeclareType(cl_I,z);
		print_integer(stream,base,z);
	} else {
		DeclareType(cl_RT,z);
		var const cl_I& num = numerator(z);
		var const cl_I& den = denominator(z);
		// Der Zähler trägt das Vorzeichen.
		print_integer(stream,base,num); // Zähler ausgeben
		fprintchar(stream,'/');
		print_integer(stream,base,den); // Nenner ausgeben
	}
}
