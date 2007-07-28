// eval_pqd_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cln/lfloat.h"
#include "cln/integer.h"
#include "cl_LF.h"

namespace cln {

const cl_LF eval_pqd_series (uintC N, cl_pqd_series_term* args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_pqd_series_result sums;
	eval_pqd_series_aux(N,args,sums);
	// Instead of computing  fsum = T/Q  and  gsum = V/(D*Q)
	// and then dividing them, to compute  gsum/fsum, we save two
	// divisions by computing  V/(D*T).
	return
	  cl_I_to_LF(sums.V,len) / The(cl_LF)(sums.D * cl_I_to_LF(sums.T,len));
}

}  // namespace cln
