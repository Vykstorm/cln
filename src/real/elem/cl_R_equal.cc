// cl_equal().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_RA.h"
#include "cl_integer.h"

inline cl_boolean cl_equal (const cl_F& x, const cl_F& y)
{
	return (cl_boolean) (cl_compare(x,y) == 0);
}

cl_boolean cl_equal (const cl_R& x, const cl_R& y)
{
// Methode:
// Beide rational oder beide Floats -> klar.
// Eine rational, eine Float ->
//   Die rationale Zahl muß einen Zweierpotenz-Nenner haben, sonst verschieden.
//   Die rationale Zahl zum Float machen, vergleichen.
//   Verschieden -> Das war's.
//   Gleich -> Das Float mit RATIONAL rational machen, nochmals vergleichen.
	realcase2(x
	,	realcase2(y
		,	// beides rationale Zahlen
			return cl_equal(x,y);
		,	// x rational, y Float -> x in Float umwandeln
			if (!power2p(denominator(x)))
				return cl_false;
			if (!cl_equal(cl_float(x,y),y))
				return cl_false;
			return cl_equal(x,rational(y));
		);
	,	realcase2(y
		,	// x Float, y rational -> y in Float umwandeln
			if (!power2p(denominator(y)))
				return cl_false;
			if (!cl_equal(x,cl_float(y,x)))
				return cl_false;
			return cl_equal(rational(x),y);
		,	// beides Floats
			return cl_equal(x,y);
		);
	);
}
