// cl_float_format().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

cl_float_format_t cl_float_format (uintL n)
{
// Methode:
// Mindestens 1+n Dezimalstellen (inklusive Vorkommastelle)
// bedeutet mindestens ceiling((1+n)*ln(10)/ln(2)) Binärstellen.
// ln(10)/ln(2) = 3.321928095 = (binär) 11.01010010011010011110000100101111...
//                       = (binär) 100 - 0.10101101100101100001111011010001
// Durch diese Berechnungsmethode wird das Ergebnis sicher >= (1+n)*ln(10)/ln(2)
// sein, evtl. um ein paar Bit zu groß, aber nicht zu klein.
	n = 1+n;
	return (cl_float_format_t)
	       ((n << 2)
		- (n >> 1) - (n >> 3) - (n >> 5) - (n >> 6) - (n >> 8)
		- (n >> 9) - (n >> 12) - (n >> 14) - (n >> 15)
	       );
}
