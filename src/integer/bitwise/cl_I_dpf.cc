// deposit_field().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"

const cl_I deposit_field (const cl_I& newbyte, const cl_I& n, const cl_byte& b)
{
      // Methode:
      // (DEPOSIT-FIELD newbyte (byte s p) integer)
      //  = (logxor integer
      //            (ash (logxor (ldb (byte s p) newbyte) (ldb (byte s p) integer))
      //                 p
      //    )       )
      return logxor(n, ash(logxor(ldb(newbyte,b),ldb(n,b)), b.position));
}
