// logbitp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_io.h"
#include "cl_integer_io.h"
#include "cl_abort.h"

cl_boolean logbitp (const cl_I& x, const cl_I& y)
{
    // Methode:
    // Falls x<0, Error.
    // Falls x>=0: Falls x>=intDsize*Länge(y), teste Vorzeichen von y.
    //             Sonst x=intDsize*k+i, Teste Bit i vom Worte Nr. k+1 (von oben herab).
      if (!minusp(x)) // x>=0 ?
        { if (fixnump(x))
            { var uintL x_ = FN_to_L(x);
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
        { fprint(cl_stderr, "logbitp: Index is negative: ");
          fprint(cl_stderr, x);
          fprint(cl_stderr, "\n");
          cl_abort();
        }
}
