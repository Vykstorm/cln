// exp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F_tran.h"
#include "cl_float.h"
#include "cl_F.h"
#include "cl_lfloat.h"
#include "cl_LF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"
#include "cl_LF_exponent.cc"

// Division durch ln(2).
inline const cl_F_div_t cl_floor_ln2 (const cl_F& x)
{
	// Bei 0<=x<1/2 kann man sofort q:=0 setzen.
	if (!minusp(x) && (float_exponent(x) < 0))
		return cl_F_div_t(0,x);
	else
		return floor2(x,cl_ln2(x));
}
inline const cl_LF_div_t cl_floor_ln2 (const cl_LF& x)
{
	// Bei 0<=x<1/2 kann man sofort q:=0 setzen.
	if (!minusp(x) && (float_exponent(x) < 0))
		return cl_LF_div_t(0,x);
	else
		return floor2(x,The(cl_LF)(cl_ln2(x)));
}

const cl_F exp (const cl_F& x)
{
// Methode:
// d := (float-digits x),
// Genauigkeit um sqrt(d)+max(integer-length(e)) Bits erhöhen,
// (q,r) := (floor x ln(2))
// Ergebnis ist exp(q*ln(2)+r) = (scale-float exp(r) q).

	// Rechengenauigkeit erhöhen und durch ln(2) dividieren:
	if (longfloatp(x) && (TheLfloat(x)->len >= 84)) {
		DeclareType(cl_LF,x);
		var cl_LF_div_t q_r = cl_floor_ln2(extend(x,TheLfloat(x)->len+1));
		var cl_I& q = q_r.quotient;
		var cl_LF& r = q_r.remainder;
		return cl_float(scale_float(expx_ratseries(r),q),x);
	} else {
		var cl_F_div_t q_r = cl_floor_ln2(cl_F_extendsqrtx(x));
		var cl_I& q = q_r.quotient;
		var cl_F& r = q_r.remainder;
		return cl_float(scale_float(expx_naive(r),q),x);
	}
}
