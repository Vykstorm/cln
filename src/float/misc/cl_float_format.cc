// float_format().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

namespace cln {

float_format_t float_format (uintL n)
{
// Methode:
// Mindestens 1+n Dezimalstellen (inklusive Vorkommastelle)
// bedeutet mindestens ceiling((1+n)*ln(10)/ln(2)) Bin‰rstellen.
// ln(10)/ln(2) = 3.321928095 = (bin‰r) 11.01010010011010011110000100101111...
//                       = (bin‰r) 100 - 0.10101101100101100001111011010001
// Durch diese Berechnungsmethode wird das Ergebnis sicher >= (1+n)*ln(10)/ln(2)
// sein, evtl. um ein paar Bit zu groﬂ, aber nicht zu klein.
	n = 1+n;
	return (float_format_t)
	       ((n << 2)
		- (n >> 1) - (n >> 3) - (n >> 5) - (n >> 6) - (n >> 8)
		- (n >> 9) - (n >> 12) - (n >> 14) - (n >> 15)
	       );
}

}  // namespace cln
