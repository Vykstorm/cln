// cl_F_catalanconst.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_F_catalanconst_var)

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_DS.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_F.h"

// Mantisse der Catalanschen Konstante :
  static const uintD catalanconst_mantisse [64/intDsize] =
    #include "cl_F_catalanconst_var.h"

cl_LF cl_LF_catalanconst = encode_LF_array(0,0,catalanconst_mantisse,64/intDsize);

// Problem: If someone changes cl_free_hook, the destructor of this
// will call the new hook, passing it some pointer obtained by the old
// cl_malloc_hook. ??

const cl_SF cl_SF_catalanconst = cl_LF_to_SF(cl_LF_catalanconst);
const cl_FF cl_FF_catalanconst = cl_LF_to_FF(cl_LF_catalanconst);
const cl_DF cl_DF_catalanconst = cl_LF_to_DF(cl_LF_catalanconst);

CL_PROVIDE_END(cl_F_catalanconst_var)
