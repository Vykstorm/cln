// dpb().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"

const cl_I dpb (const cl_I& newbyte, const cl_I& n, const cl_byte& b)
{
      // Methode:
      // (DPB newbyte (byte s p) integer)
      // = (DEPOSIT-FIELD (ASH newbyte p) (byte s p) integer)
      return deposit_field(ash(newbyte,b.position),n,b);
}
