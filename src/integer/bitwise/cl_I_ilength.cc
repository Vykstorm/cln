// integer_length().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"

uintL integer_length (const cl_I& x)
{
	if (fixnump(x))
	  { var uintL bitcount = 0;
	    var uint32 x_ = FN_to_L(x); // x als 32-Bit-Zahl
	    if (FN_L_minusp(x,(sint32)x_)) { x_ = ~ x_; } // falls <0, komplementieren
	    if (!(x_==0)) { integerlength32(x_,bitcount=); }
	    return bitcount; // 0 <= bitcount < 32.
	  }
          else
          { var const uintD* MSDptr;
            var uintC len;
            BN_to_NDS_nocopy(x, MSDptr=,len=,); // normalisierte DS zu x bilden.
            var uintL bitcount = intDsize*(uintL)(len-1); // Anzahl Digits mal intDsize
            // MSDigit nehmen, testen, welches das höchste Bit ist, das vom
            // Vorzeichenbit abweicht:
            var uintD msd = mspref(MSDptr,0); // MSDigit
            if ((sintD)msd < 0) { msd = ~msd; } // falls negativ, invertieren
            // Position des höchsten Bits in msd suchen und entsprechend bit_count
            // erhöhen (um höchstens intDsize-1):
            if (!(msd == 0)) { integerlengthD(msd, bitcount += ); }
            return bitcount; // 0 <= bitcount < intDsize*2^intCsize.
          }
}
