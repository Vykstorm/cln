// cos().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N cos (const cl_N& x)
{
// Methode:
// x reell -> klar
// x = a+bi -> (complex (* (cos a) (cosh b)) (- (* (sin a) (sinh b))))
	if (realp(x)) {
		DeclareType(cl_R,x);
		return cos(x);
	} else {
		DeclareType(cl_C,x);
		// x=a+bi
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		var cl_cosh_sinh_t hyp_b = cl_cosh_sinh(b); // cosh(b), sinh(b) errechnen
		var cl_cos_sin_t trig_a = cl_cos_sin(a); // cos(a), sin(a) errechnen
		return complex(trig_a.cos * hyp_b.cosh, // cos(a)*cosh(b)
			       - (trig_a.sin * hyp_b.sinh) // -sin(a)*sinh(b)
			      );
	}
}
