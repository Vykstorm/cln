// ldb().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cln/integer.h"
#include "cl_I.h"
#include "cl_I_byte.h"

namespace cln {

const cl_I ldb (const cl_I& n, const cl_byte& b)
{
      // Methode:
      // (ldb (byte s p) n) extrahiere die Bits p,...,p+s-1 von n.
      // l:=(integer-length n)
      // Falls l <= p :
      //   Falls n>=0: 0, falls n<0: 2^s - 1 (s Einsenbits).
      // Falls p <= l :
      //   q:=min(p+s,l).
      //   Extrahiere die Bits p,...,q-1 von n.
      //   Falls p+s>l und n<0, füge p+s-l Einsenbits an (addiere 2^s-2^(l-p)).
      var uintL s = b.size;
      var uintL p = b.position;
      var uintL l = integer_length(n); // l = (integer-length n)
      if (l<=p)
        // l<=p
        if (!minusp(n))
          // n>=0
          return 0; // 0 als Ergebnis
          else
          // n<0
          return cl_fullbyte(0,s); // 2^s-2^0 als Ergebnis
        else
        // l>p
        { var cl_I erg = ldb_extract(n,p,(p+s<l ? p+s : l));
          var uintL lp = l-p;
          if ((s>lp) && minusp(n)) // s>l-p und n<0 ?
            { return logior(erg,cl_fullbyte(lp,s)); } // setze Bits l-p,...,s-1
            // (logisches Exklusiv-Oder oder Addition ginge auch)
            else
            return erg;
        }
}

}  // namespace cln
