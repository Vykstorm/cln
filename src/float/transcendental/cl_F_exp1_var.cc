// cl_F_exp1.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_F_exp1_var)

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_DS.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_F.h"

// Mantisse von exp(1) :
  static const uintD exp1_mantisse [64/intDsize] =
    #include "cl_F_exp1_var.h"

cl_LF cl_LF_exp1 = encode_LF_array(0,2,exp1_mantisse,64/intDsize);

// Problem: If someone changes cl_free_hook, the destructor of this
// will call the new hook, passing it some pointer obtained by the old
// cl_malloc_hook. ??

const cl_SF cl_SF_exp1 = cl_LF_to_SF(cl_LF_exp1);
const cl_FF cl_FF_exp1 = cl_LF_to_FF(cl_LF_exp1);
const cl_DF cl_DF_exp1 = cl_LF_to_DF(cl_LF_exp1);

CL_PROVIDE_END(cl_F_exp1_var)
