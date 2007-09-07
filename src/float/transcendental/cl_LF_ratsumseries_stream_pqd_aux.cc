// eval_pqd_series_aux().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cln/integer.h"
#include "cln/exception.h"

namespace cln {

void eval_pqd_series_aux (uintC N, cl_pqd_series_stream& args, cl_pqd_series_result& Z, bool rightmost)
{
	// N = N2-N1
	switch (N) {
	case 0:
		throw runtime_exception(); break;
	case 1: {
		var cl_pqd_series_term v0 = args.next(); // [N1]
		if (!rightmost) { Z.P = v0.p; }
		Z.Q = v0.q;
		Z.T = v0.p;
		if (!rightmost) { Z.C = 1; }
		Z.D = v0.d;
		Z.V = v0.p;
		break;
		}
	case 2: {
		var cl_pqd_series_term v0 = args.next(); // [N1]
		var cl_pqd_series_term v1 = args.next(); // [N1+1]
		var cl_I p01 = v0.p * v1.p;
		if (!rightmost) { Z.P = p01; }
		Z.Q = v0.q * v1.q;
		var cl_I p0q1 = v0.p * v1.q + p01;
		Z.T = p0q1;
		if (!rightmost) { Z.C = v1.d + v0.d; }
		Z.D = v0.d * v1.d;
		Z.V = v1.d * p0q1 + v0.d * p01;
		break;
		}
	case 3: {
		var cl_pqd_series_term v0 = args.next(); // [N1]
		var cl_pqd_series_term v1 = args.next(); // [N1+1]
		var cl_pqd_series_term v2 = args.next(); // [N1+2]
		var cl_I p01 = v0.p * v1.p;
		var cl_I p012 = p01 * v2.p;
		if (!rightmost) { Z.P = p012; }
		Z.Q = v0.q * v1.q * v2.q;
		var cl_I p0q1 = v0.p * v1.q + p01;
		Z.T = v2.q * p0q1 + p012;
		var cl_I d01 = v0.d * v1.d;
		if (!rightmost) { Z.C = (v1.d + v0.d) * v2.d + d01; }
		Z.D = d01 * v2.d;
		Z.V = v2.d * (v2.q * (v1.d * p0q1 + v0.d * p01) + (v1.d + v0.d) * p012) + d01 * p012;
		break;
		}
	default: {
		var uintC Nm = N/2; // midpoint
		// Compute left part.
		var cl_pqd_series_result L;
		eval_pqd_series_aux(Nm,args,L,false);
		// Compute right part.
		var cl_pqd_series_result R;
		eval_pqd_series_aux(N-Nm,args,R,rightmost);
		// Put together partial results.
		if (!rightmost) { Z.P = L.P * R.P; }
		Z.Q = L.Q * R.Q;
		// Z.S = L.S + L.P/L.Q*R.S;
		var cl_I tmp = L.P * R.T;
		Z.T = R.Q * L.T + tmp;
		if (!rightmost) { Z.C = L.C * R.D + L.D * R.C; }
		Z.D = L.D * R.D;
		// Z.U = L.U + L.C/L.D * L.P/L.Q * R.S + L.P/L.Q * R.U;
		// Z.V = R.D * R.Q * L.V + R.D * L.C * L.P * R.T + L.D * L.P * R.V;
		Z.V = R.D * (R.Q * L.V + L.C * tmp) + L.D * L.P * R.V;
		break;
		}
	}
}

}  // namespace cln
