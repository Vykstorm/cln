// cl_atan_recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F_tran.h"


// Implementation.

#include "cl_integer.h"
#include "cl_lfloat.h"
#include "cl_LF.h"
#include "cl_LF_tran.h"
#include "cl_alloca.h"

#undef floor
#include <math.h>
#define floor cln_floor

// Method:
// See examples/atan_recip.cc for a comparison of the algorithms.
// Here we take algorithm 2d. It's the fastest throughout the range.

const cl_LF cl_atan_recip (cl_I m, uintC len)
{
	var uintC actuallen = len + 1;
	var cl_I m2 = m*m+1;
	var uintL N = (uintL)(0.69314718*intDsize*actuallen/log(cl_double_approx(m2))) + 1;
	CL_ALLOCA_STACK;
	var cl_I* pv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var cl_I* qv = (cl_I*) cl_alloca(N*sizeof(cl_I));
	var uintL n;
	new (&pv[0]) cl_I (m);
	new (&qv[0]) cl_I (m2);
	for (n = 1; n < N; n++) {
		new (&pv[n]) cl_I (2*n);
		new (&qv[n]) cl_I ((2*n+1)*m2);
	}
	var cl_pq_series series;
	series.pv = pv; series.qv = qv; series.qsv = NULL;
	var cl_LF result = eval_rational_series(N,series,actuallen);
	for (n = 0; n < N; n++) {
		pv[n].~cl_I();
		qv[n].~cl_I();
	}
	return shorten(result,len);
}
// Bit complexity (N = len): O(log(N)^2*M(N)).
