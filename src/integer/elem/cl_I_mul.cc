// binary operator *

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_low.h"

const cl_I operator* (const cl_I& x, const cl_I& y)
{
  // Methode:
  // x=0 oder y=0 -> Ergebnis 0
  // x und y beide Fixnums -> direkt multiplizieren
  // sonst: zu DS machen, multiplizieren.
      if (zerop(x))
        { return 0; }
      if (zerop(y))
        { return 0; }
      if (fixnump(x) && fixnump(y))
        { var sint32 x_ = FN_to_L(x);
          var sint32 y_ = FN_to_L(y);
          // Werte direkt multiplizieren:
          var uint32 hi;
          var uint32 lo;
          mulu32((uint32)x_,(uint32)y_,hi=,lo=); // erst unsigned multiplizieren
          if (x_ < 0) { hi -= (uint32)y_; } // dann Korrektur für Vorzeichen
          if (y_ < 0) { hi -= (uint32)x_; } // (vgl. DS_DS_mul_DS)
          return L2_to_I(hi,lo);
        }
      CL_ALLOCA_STACK;
      var const uintD* xMSDptr;
      var uintC xlen;
      var const uintD* xLSDptr;
      var const uintD* yMSDptr;
      var uintC ylen;
      var const uintD* yLSDptr;
      var uintD* ergMSDptr;
      var uintC erglen;
      I_to_NDS_nocopy(x, xMSDptr = , xlen = , xLSDptr = , cl_false,);
      I_to_NDS_nocopy(y, yMSDptr = , ylen = , yLSDptr = , cl_false,);
      DS_DS_mul_DS(xMSDptr,xlen,xLSDptr,yMSDptr,ylen,yLSDptr, ergMSDptr=,erglen=,);
      return DS_to_I(ergMSDptr,erglen);
}
// Bit complexity (x,y of length N): O(M(N)).

