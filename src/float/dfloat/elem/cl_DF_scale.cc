// scale_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"
#include "cl_F.h"

namespace cln {

const cl_DF scale_float (const cl_DF& x, sintL delta)
{
  // Methode:
  // x=0.0 -> x als Ergebnis
  // delta muß betragsmäßig <= DF_exp_high-DF_exp_low sein.
  // Neues DF mit um delta vergrößertem Exponenten bilden.
      // x entpacken:
      var cl_signean sign;
      var sintL exp;
#if (cl_word_size==64)
      var uint64 mant;
      DF_decode(x, { return x; }, sign=,exp=,mant=);
#else
      var uint32 manthi;
      var uint32 mantlo;
      DF_decode2(x, { return x; }, sign=,exp=,manthi=,mantlo=);
#endif
      if (delta >= 0)
        // delta>=0
        { var uintL udelta = delta;
          if (udelta <= (uintL)(DF_exp_high-DF_exp_low))
            { exp = exp+udelta;
#if (cl_word_size==64)
              return encode_DF(sign,exp,mant);
#else
              return encode_DF(sign,exp,manthi,mantlo);
#endif
            }
            else
            { cl_error_floating_point_overflow(); }
        }
        else
        // delta<0
        { var uintL udelta = -delta;
          if (udelta <= (uintL)(DF_exp_high-DF_exp_low))
            { exp = exp-udelta;
#if (cl_word_size==64)
              return encode_DF(sign,exp,mant);
#else
              return encode_DF(sign,exp,manthi,mantlo);
#endif
            }
            else
            if (underflow_allowed())
              { cl_error_floating_point_underflow(); }
              else
              { return cl_DF_0; }
        }
}

}  // namespace cln
