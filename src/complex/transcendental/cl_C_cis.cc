// cis().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N cis (const cl_N& x)
{
// Methode:
// x reell -> (complex (cos x) (sin x))
// x = a+bi -> (complex (* (exp (- b)) (cos a)) (* (exp (- b)) (sin a)))
	if (realp(x)) {
		DeclareType(cl_R,x);
		var cl_cos_sin_t trig = cl_cos_sin(x);
		return complex(trig.cos, trig.sin);
	} else {
		DeclareType(cl_C,x);
		// x=a+bi
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var cl_cos_sin_t trig_a = cl_cos_sin(a); // cos(a), sin(a) errechnen
		var cl_R exp_minusb = exp(-b); // (exp (- b))
		return complex(exp_minusb*trig_a.cos, // (* (exp (- b)) (cos a))
			       exp_minusb*trig_a.sin); // (* (exp (- b)) (sin a))
	}
}
