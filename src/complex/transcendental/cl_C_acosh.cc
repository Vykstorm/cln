// acosh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"
#include "cl_R.h"
#include "cl_rational.h"
#include "cl_RA.h"
#include "cl_float.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_F_from_R_def.cc"

const cl_N acosh (const cl_N& z)
{
// Methode:
// Wert und Branch Cuts nach der Formel CLTL2, S. 314:
//   arcosh(z) = 2 log(sqrt((z+1)/2)+sqrt((z-1)/2))
// Sei z=x+iy.
// Falls y=0:
//   Falls x rational:
//     Bei x=1: Ergebnis 0.
//     Bei x=1/2: Ergebnis pi/3 i.
//     Bei x=0: Ergebnis pi/2 i.
//     Bei x=-1/2: Ergebnis 2pi/3 i.
//     Bei x=-1: Ergebnis pi i.
//   Falls x<-1:
//     x in Float umwandeln, Ergebnis log(sqrt(x^2-1)-x) + i pi.
// Sonst nach (!) mit u = sqrt((z+1)/2) und v = sqrt((z-1)/2) :
// arcosh(z) = 4 artanh(v/(u+1)) = 4 artanh(sqrt((z-1)/2)/(1+sqrt((z+1)/2)))

// Um für zwei Zahlen u,v mit u^2-v^2=1 und u,v beide in Bild(sqrt)
// (d.h. Realteil>0.0 oder Realteil=0.0 und Imaginärteil>=0.0)
// log(u+v) zu berechnen:
//               log(u+v) = 2 artanh(v/(u+1))                            (!)
// (Beweis: 2 artanh(v/(u+1)) = log(1+(v/(u+1))) - log(1-(v/(u+1)))
//  = log((1+u+v)/(u+1)) - log((1+u-v)/(u+1)) == log((1+u+v)/(1+u-v))
//  = log(u+v) mod 2 pi i, und beider Imaginärteil ist > -pi und <= pi.)

	cl_C_R u_v;
	if (realp(z)) {
		DeclareType(cl_R,z);
		// y=0
		var const cl_R& x = z;
		if (rationalp(x)) {
			DeclareType(cl_RA,x);
			// x rational
			if (integerp(x)) {
				DeclareType(cl_I,x);
				// x Integer
				if (eq(x,0)) // x=0 -> Ergebnis pi/2 i
					return complex_C(0,scale_float(cl_pi(),-1));
				if (eq(x,1)) // x=1 -> Ergebnis 0
					return 0;
				if (eq(x,-1)) // x=-1 -> Ergebnis pi i
					return complex_C(0,cl_pi());
			} else {
				DeclareType(cl_RT,x);
				// x Ratio
				if (eq(denominator(x),2)) { // Nenner = 2 ?
					if (eq(numerator(x),1)) // x=1/2 -> Ergebnis pi/3 i
						return complex_C(0,cl_pi()/3);
					if (eq(numerator(x),-1)) // x=-1/2 -> Ergebnis 2pi/3 i
						return complex_C(0,scale_float(cl_pi(),1)/3);
				}
			}
		}
		if (x < cl_I(-1)) {
			// x < -1
			var cl_F xf = cl_float(x);
			var cl_F& x = xf;
			// x Float <= -1
			// log(sqrt(x^2-1)-x), ein Float >=0, Imaginärteil pi
			return complex_C(ln(sqrt(square(x)-1)-x),cl_pi());
		}
	}
	return 4 * atanh( sqrt(minus1(z)/2) / plus1(sqrt(plus1(z)/2)) );
}
