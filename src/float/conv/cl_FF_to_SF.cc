// cl_FF_to_SF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cl_FF.h"
#include "cl_SF.h"

const cl_SF cl_FF_to_SF (const cl_FF& x)
{
	// x entpacken:
	var cl_signean sign;
	var sintL exp;
	var uint32 mant;
	FF_decode(x, { return SF_0; }, sign=,exp=,mant=);
	// 23-16 Bits wegrunden:
	var const int shiftcount = FF_mant_len-SF_mant_len;
	if ( ((mant & bit(shiftcount-1)) ==0) // Bit 6 war 0 -> abrunden
	     || ( ((mant & (bit(shiftcount-1)-1)) ==0) // war 1, Bits 5..0 >0 -> aufrunden
	          // round-to-even
	          && ((mant & bit(shiftcount)) ==0)
	   )    )
	  // abrunden
	  { mant = mant >> shiftcount; }
	  else
	  // aufrunden
	  { mant = mant >> shiftcount;
	    mant = mant+1;
	    if (mant >= bit(SF_mant_len+1))
	      // Überlauf durchs Runden
	      { mant = mant>>1; exp = exp+1; } // Mantisse rechts schieben
	  }
	return encode_SF(sign,exp,mant);
}
