// cl_compare().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_float.h"

cl_signean cl_compare (const cl_R& x, const cl_R& y)
{
  // Methode:
  // Beide rational oder beide Floats -> klar.
  // Eine rational, eine Float ->
  //   Die rationale Zahl zum Float machen, vergleichen.
  //   Verschieden -> Das war's.
  //   Gleich -> Das Float mit RATIONAL rational machen, nochmals vergleichen.
	realcase2(x
	,	realcase2(y
		,	// beides rationale Zahlen
			return cl_compare(x,y);
		,	// x rational, y Float -> x in Float umwandeln
			var cl_signean result = cl_compare(cl_float(x,y),y);
			if (result != signean_null)
				return result;
			return cl_compare(x,rational(y));
		);
	,	realcase2(y
		,	// x Float, y rational -> y in Float umwandeln
			var cl_signean result = cl_compare(x,cl_float(y,x));
			if (result != signean_null)
				return result;
			return cl_compare(rational(x),y);
		,	// beides Floats
			return cl_compare(x,y);
		);
	);
}
