// cl_atanh_recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cln/integer.h"
#include "cln/lfloat.h"
#include "cl_LF.h"
#include "cl_LF_tran.h"
#include "cl_alloca.h"

#undef floor
#include <cmath>
#define floor cln_floor

namespace cln {

// Method:
// See examples/atanh_recip.cc for a comparison of the algorithms.
// Here we take algorithm 1d. It's the fastest throughout the range.

const cl_LF cl_atanh_recip (cl_I m, uintC len)
{
	var uintC actuallen = len + 1;
	var cl_I m2 = m*m;
	var uintL N = (uintL)(0.69314718*intDsize/2*actuallen/::log(double_approx(m))) + 1;
	CL_ALLOCA_STACK;
	var cl_I* bv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* qv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var uintL n;
	for (n = 0; n < N; n++) {
		new (&bv[n]) cl_I ((cl_I)(2*n+1));
		new (&qv[n]) cl_I (n==0 ? m : m2);
	}
	var cl_qb_series series;
	series.bv = bv;
	series.qv = qv; series.qsv = NULL;
	var cl_LF result = eval_rational_series(N,series,actuallen);
	for (n = 0; n < N; n++) {
		bv[n].~cl_I();
		qv[n].~cl_I();
	}
	return shorten(result,len);
}
// Bit complexity (N = len): O(log(N)^2*M(N)).

}  // namespace cln
