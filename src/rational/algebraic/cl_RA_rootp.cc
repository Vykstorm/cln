// rootp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

#include "cl_RA.h"
#include "cln/integer.h"

namespace cln {

cl_boolean rootp (const cl_RA& x, uintL n, cl_RA* w)
{
// Methode:
// Bei Integers: klar.
// Bei Brüchen a/b : muß a=c^n und b=d^n sein. Dann ist die Wurzel = c/d
// (mit ggT(c,d)=1 und d>1).
	if (integerp(x)) {
		DeclareType(cl_I,x);
		return rootp(x,n,(cl_I*)w);
	} else {
	// x ist Ratio
	DeclareType(cl_RT,x);
	var const cl_I& b = denominator(x);
	var cl_I d;
	if (!rootp(b,n,&d)) // Nenner auf n-te Potenz testen
		return cl_false;
	var const cl_I& a = numerator(x);
	var cl_I c;
	if (!rootp(a,n,&c)) // Zähler auf n-te Potenz testen
		return cl_false;
	// beides n-te Potenzen -> Quotient der Wurzeln bilden
	*w = I_I_to_RT(c,d); return cl_true;
}}

}  // namespace cln
