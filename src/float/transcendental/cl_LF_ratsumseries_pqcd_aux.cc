// eval_pqcd_series_aux().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cl_integer.h"
#include "cl_abort.h"

void eval_pqcd_series_aux (uintL N, cl_pqcd_series_term* args, cl_pqcd_series_result& Z, cl_boolean rightmost)
{
	// N = N2-N1
	switch (N) {
	case 0:
		cl_abort(); break;
	case 1:
		if (!rightmost) { Z.P = args[0].p; }
		Z.Q = args[0].q;
		Z.T = args[0].p;
		if (!rightmost) { Z.C = args[0].c; }
		Z.D = args[0].d;
		Z.V = args[0].c * args[0].p;
		break;
	case 2: {
		var cl_I p01 = args[0].p * args[1].p;
		if (!rightmost) { Z.P = p01; }
		Z.Q = args[0].q * args[1].q;
		var cl_I p0q1 = args[0].p * args[1].q + p01;
		Z.T = p0q1;
		var cl_I c0d1 = args[0].c * args[1].d;
		var cl_I c1d0 = args[1].c * args[0].d;
		if (!rightmost) { Z.C = c0d1 + c1d0; }
		Z.D = args[0].d * args[1].d;
		Z.V = c0d1 * p0q1 + c1d0 * p01;
		break;
		}
	case 3: {
		var cl_I p01 = args[0].p * args[1].p;
		var cl_I p012 = p01 * args[2].p;
		if (!rightmost) { Z.P = p012; }
		Z.Q = args[0].q * args[1].q * args[2].q;
		var cl_I p0q1 = args[0].p * args[1].q + p01;
		Z.T = args[2].q * p0q1 + p012;
		var cl_I c0d1 = args[0].c * args[1].d;
		var cl_I c1d0 = args[1].c * args[0].d;
		var cl_I d01 = args[0].d * args[1].d;
		if (!rightmost) { Z.C = (c0d1 + c1d0) * args[2].d + args[2].c * d01; }
		Z.D = d01 * args[2].d;
		Z.V = args[2].d * (args[2].q * (c0d1 * p0q1 + c1d0 * p01) + (c0d1 + c1d0) * p012) + args[2].c * d01 * p012;
		break;
		}
	default: {
		var uintL Nm = N/2; // midpoint
		// Compute left part.
		var cl_pqcd_series_result L;
		eval_pqcd_series_aux(Nm,args+0,L,cl_false);
		// Compute right part.
		var cl_pqcd_series_result R;
		eval_pqcd_series_aux(N-Nm,args+Nm,R,rightmost);
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
