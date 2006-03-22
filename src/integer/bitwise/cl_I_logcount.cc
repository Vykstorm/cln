// logcount().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_D.h"
#include "cl_low.h"

namespace cln {

uintL logcount (const cl_I& x)
{
	if (fixnump(x))
	  { var uintV x32 = FN_to_V(x); // x als intDsize-Bit-Zahl
	    if (FN_V_minusp(x,(sintV)x32)) { x32 = ~ x32; } // falls <0, komplementieren
            #if (intVsize>32)
            #define x64 x32
            logcount_64(); // Bits von x32 zählen
            #undef x64
            #else
	    logcount_32(); // Bits von x32 zählen
            #endif
	    return x32;
	  }
          else
          { var const uintD* MSDptr;
            var uintC len;
            BN_to_NDS_nocopy(x, MSDptr=,len=,); // DS zu x bilden, len>0.
            var uintL bitcount = 0; // Bitzähler
            var const uintD* ptr = MSDptr; // läuft durch die Digits durch
            var uintD sign = sign_of_sintD(mspref(ptr,0)); // Vorzeichen
            dotimespC(len,len,
              { bitcount += (uintL)logcountD(msprefnext(ptr) ^ sign); });
            // 0 <= bitcount < intDsize*2^intCsize.
            return bitcount;
          }
}

}  // namespace cln
