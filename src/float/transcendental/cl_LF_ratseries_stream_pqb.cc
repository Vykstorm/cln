// eval_rational_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cln/lfloat.h"
#include "cln/integer.h"
#include "cln/exception.h"
#include "cl_LF.h"

namespace cln {

static void eval_pqb_series_aux (uintC N1, uintC N2,
                                 cl_pqb_series_stream& args,
                                 cl_I* P, cl_I* Q, cl_I* B, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		throw runtime_exception(); break;
	case 1: {
		var cl_pqb_series_term v0 = args.next(); // [N1]
		if (P) { *P = v0.p; }
		*Q = v0.q;
		*B = v0.b;
		*T = v0.p;
		break;
		}
	case 2: {
		var cl_pqb_series_term v0 = args.next(); // [N1]
		var cl_pqb_series_term v1 = args.next(); // [N1+1]
		var cl_I p01 = v0.p * v1.p;
		if (P) { *P = p01; }
		*Q = v0.q * v1.q;
		*B = v0.b * v1.b;
		*T = v1.b * v1.q * v0.p
		   + v0.b * p01;
		break;
		}
	case 3: {
		var cl_pqb_series_term v0 = args.next(); // [N1]
		var cl_pqb_series_term v1 = args.next(); // [N1+1]
		var cl_pqb_series_term v2 = args.next(); // [N1+2]
		var cl_I p01 = v0.p * v1.p;
		var cl_I p012 = p01 * v2.p;
		if (P) { *P = p012; }
		var cl_I q12 = v1.q * v2.q;
		*Q = v0.q * q12;
		var cl_I b12 = v1.b * v2.b;
		*B = v0.b * b12;
		*T = b12 * q12 * v0.p
		   + v0.b * (v2.b * v2.q * p01
		             + v1.b * p012);
		break;
		}
	case 4: {
		var cl_pqb_series_term v0 = args.next(); // [N1]
		var cl_pqb_series_term v1 = args.next(); // [N1+1]
		var cl_pqb_series_term v2 = args.next(); // [N1+2]
		var cl_pqb_series_term v3 = args.next(); // [N1+3]
		var cl_I p01 = v0.p * v1.p;
		var cl_I p012 = p01 * v2.p;
		var cl_I p0123 = p012 * v3.p;
		if (P) { *P = p0123; }
		var cl_I q23 = v2.q * v3.q;
		var cl_I q123 = v1.q * q23;
		*Q = v0.q * q123;
		var cl_I b01 = v0.b * v1.b;
		var cl_I b23 = v2.b * v3.b;
		*B = b01 * b23;
		*T = b23 * (v1.b * q123 * v0.p
		            + v0.b * q23 * p01)
		   + b01 * (v3.b * v3.q * p012
		            + v2.b * p0123);
		break;
		}
	default: {
		var uintC Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LB, LT;
		eval_pqb_series_aux(N1,Nm,args,&LP,&LQ,&LB,&LT);
		// Compute right part.
		var cl_I RP, RQ, RB, RT;
		eval_pqb_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RB,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		*B = LB*RB;
		// S = LS + LP/LQ * RS, so T = RB*RQ*LT + LB*LP*RT.
		*T = RB*RQ*LT + LB*LP*RT;
		break;
		}
	}
}

const cl_LF eval_rational_series (uintC N, cl_pqb_series_stream& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, B, T;
	eval_pqb_series_aux(0,N,args,NULL,&Q,&B,&T);
	return cl_I_to_LF(T,len) / cl_I_to_LF(B*Q,len);
}

}  // namespace cln
