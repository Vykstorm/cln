// cl_SF_pi, cl_FF_pi, cl_DF_pi, cl_LF_pi.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_F_pi_var)

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_DS.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_F.h"

namespace cln {

// Mantisse von pi :
  static const uintD pi_mantisse [2048/intDsize] =
    #include "cl_F_pi_var.h"

cl_LF cl_LF_pi = encode_LF_array(0,2,pi_mantisse,2048/intDsize);

// Problem: If someone changes free_hook, the destructor of this
// will call the new hook, passing it some pointer obtained by the old
// malloc_hook. ??

const cl_SF cl_SF_pi = cl_LF_to_SF(cl_LF_pi);
const cl_FF cl_FF_pi = cl_LF_to_FF(cl_LF_pi);
const cl_DF cl_DF_pi = cl_LF_to_DF(cl_LF_pi);

}  // namespace cln

CL_PROVIDE_END(cl_F_pi_var)
