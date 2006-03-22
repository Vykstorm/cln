// logbitp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cln/io.h"
#include "cln/integer_io.h"
#include "cln/abort.h"

namespace cln {

cl_boolean logbitp (const cl_I& x, const cl_I& y)
{
    // Methode:
    // Falls x<0, Error.
    // Falls x>=0: Falls x>=intDsize*Länge(y), teste Vorzeichen von y.
    //             Sonst x=intDsize*k+i, Teste Bit i vom Worte Nr. k+1 (von oben herab).
      if (!minusp(x)) // x>=0 ?
        { if (fixnump(x))
            { var uintV x_ = FN_to_V(x);
              var uintC ylen;
              var const uintD* yLSDptr;
              I_to_NDS_nocopy(y, ,ylen=,yLSDptr=,cl_true, { return cl_false; } ); // DS zu y
              if (x_ < intDsize*(uintL)ylen)
                // x ist ein Fixnum >=0, < intDsize*ylen
                { if (lspref(yLSDptr,floor(x_,intDsize)) & bit(x_%intDsize))
                    return cl_true;
                    else
                    return cl_false;
            }   }
          // Vorzeichen von y testen
          if (minusp(y))
            return cl_true;
            else
            return cl_false;
        }
        else
        // x<0
        { fprint(std::cerr, "logbitp: Index is negative: ");
          fprint(std::cerr, x);
          fprint(std::cerr, "\n");
          cl_abort();
        }
}

}  // namespace cln
