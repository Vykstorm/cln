// cl_F_eulerconst.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_F_eulerconst_var)

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_DS.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_F.h"

namespace cln {

// Mantisse der Eulerschen Konstante :
  static const uintD eulerconst_mantisse [64/intDsize] =
    #include "cl_F_eulerconst_var.h"

cl_LF cl_LF_eulerconst = encode_LF_array(0,0,eulerconst_mantisse,64/intDsize);

// Problem: If someone changes free_hook, the destructor of this
// will call the new hook, passing it some pointer obtained by the old
// malloc_hook. ??

const cl_SF cl_SF_eulerconst = cl_LF_to_SF(cl_LF_eulerconst);
const cl_FF cl_FF_eulerconst = cl_LF_to_FF(cl_LF_eulerconst);
const cl_DF cl_DF_eulerconst = cl_LF_to_DF(cl_LF_eulerconst);

}  // namespace cln

CL_PROVIDE_END(cl_F_eulerconst_var)
