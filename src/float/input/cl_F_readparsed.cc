// read_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float_io.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"
#include "cl_rational.h"
#include "cl_RA.h"
#include "cl_float.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"
#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"

const cl_F read_float (unsigned int base, cl_float_format_t prec, cl_signean sign, const char * string, uintL index1, uintL index4, uintL index2, uintL index3)
{
	var cl_I exponent;
	{
		var uintL exp_len = index2-index4; // Anzahl Stellen des Exponenten
		if (exp_len > 0) {
			var const char * ptr = &string[index4]; // zeigt auf den Exponentmarker
			ptr++; exp_len--; // Exponentmarker überlesen
			var cl_signean exp_sign = 0; // Exponenten-Vorzeichen
			switch (*ptr) {
				case '-': exp_sign = ~exp_sign; // Vorzeichen := negativ
				case '+': ptr++; exp_len--; // Exponenten-Vorzeichen überlesen
				default: ;
			}
			exponent = digits_to_I(ptr,exp_len,(uintD)base); // Exponent in Integer umwandeln
			if (!(exp_sign==0))
				exponent = -exponent; // incl. Vorzeichen
		} else {
			// kein Exponent da
			exponent = 0;
		}
	}
	// exponent = Exponent als Integer.
	var cl_RA base_power = expt(base,exponent-(index4-index3)); // zu multiplizierende Zehnerpotenz
	var cl_I mantisse = // Mantisse als Integer
	  digits_to_I(&string[index1],index4-index1,(uintD)base);
	// Mantisse (Integer) und Zehnerpotenz (rational >0) unelegant zusammenmultiplizieren:
	var cl_RA ratvalue;
	if (integerp(base_power)) {
		DeclareType(cl_I,base_power);
		ratvalue = mantisse * base_power;
	} else {
		// falls mantisse/=0, in exponent=1/10^i den Zähler durch mantisse
		// ersetzen (liefert ungekürzten Bruch, Vorsicht!)
		DeclareType(cl_RT,base_power);
		if (zerop(mantisse))
			ratvalue = 0;
		else {
			ASSERT(TheRatio(base_power)->refcount == 1);
			TheRatio(base_power)->numerator = mantisse;
			ratvalue = base_power;
		}
	}
	// ratvalue = Mantisse * Zehnerpotenz, als ungekürzte rationale Zahl!
	floatformatcase(prec
	,	// in Short-Float umwandeln
		{
			var cl_SF x = cl_RA_to_SF(ratvalue);
			if (sign==0) { return x; } else { return -x; }
		}
	,	// in Single-Float umwandeln
		{
			var cl_FF x = cl_RA_to_FF(ratvalue);
			if (sign==0) { return x; } else { return -x; }
		}
	,	// in Double-Float umwandeln
		{
			var cl_DF x = cl_RA_to_DF(ratvalue);
			if (sign==0) { return x; } else { return -x; }
		}
	,	// in Long-Float umwandeln
		{
			var cl_LF x = cl_RA_to_LF(ratvalue,len);
			if (sign==0) { return x; } else { return -x; }
		}
	);
}
