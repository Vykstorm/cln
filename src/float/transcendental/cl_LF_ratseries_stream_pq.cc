// eval_rational_series().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF_tran.h"


// Implementation.

#include "cl_lfloat.h"
#include "cl_integer.h"
#include "cl_abort.h"
#include "cl_LF.h"

static void eval_pq_series_aux (uintL N1, uintL N2,
                                cl_pq_series_stream& args,
                                cl_I* P, cl_I* Q, cl_I* T)
{
	switch (N2 - N1) {
	case 0:
		cl_abort(); break;
	case 1: {
		var cl_pq_series_term v0 = args.next(); // [N1]
		if (P) { *P = v0.p; }
		*Q = v0.q;
		*T = v0.p;
		break;
		}
	case 2: {
		var cl_pq_series_term v0 = args.next(); // [N1]
		var cl_pq_series_term v1 = args.next(); // [N1+1]
		var cl_I p01 = v0.p * v1.p;
		if (P) { *P = p01; }
		*Q = v0.q * v1.q;
		*T = v1.q * v0.p
		   + p01;
		break;
		}
	case 3: {
		var cl_pq_series_term v0 = args.next(); // [N1]
		var cl_pq_series_term v1 = args.next(); // [N1+1]
		var cl_pq_series_term v2 = args.next(); // [N1+2]
		var cl_I p01 = v0.p * v1.p;
		var cl_I p012 = p01 * v2.p;
		if (P) { *P = p012; }
		var cl_I q12 = v1.q * v2.q;
		*Q = v0.q * q12;
		*T = q12 * v0.p
		   + v2.q * p01
		   + p012;
		break;
		}
	case 4: {
		var cl_pq_series_term v0 = args.next(); // [N1]
		var cl_pq_series_term v1 = args.next(); // [N1+1]
		var cl_pq_series_term v2 = args.next(); // [N1+2]
		var cl_pq_series_term v3 = args.next(); // [N1+3]
		var cl_I p01 = v0.p * v1.p;
		var cl_I p012 = p01 * v2.p;
		var cl_I p0123 = p012 * v3.p;
		if (P) { *P = p0123; }
		var cl_I q23 = v2.q * v3.q;
		var cl_I q123 = v1.q * q23;
		*Q = v0.q * q123;
		*T = q123 * v0.p
		   + q23 * p01
		   + v3.q * p012
		   + p0123;
		break;
		}
	default: {
		var uintL Nm = (N1+N2)/2; // midpoint
		// Compute left part.
		var cl_I LP, LQ, LT;
		eval_pq_series_aux(N1,Nm,args,&LP,&LQ,&LT);
		// Compute right part.
		var cl_I RP, RQ, RT;
		eval_pq_series_aux(Nm,N2,args,(P?&RP:(cl_I*)0),&RQ,&RT);
		// Put together partial results.
		if (P) { *P = LP*RP; }
		*Q = LQ*RQ;
		// S = LS + LP/LQ * RS, so T = RQ*LT + LP*RT.
		*T = RQ*LT + LP*RT;
		break;
		}
	}
}

const cl_LF eval_rational_series (uintL N, cl_pq_series_stream& args, uintC len)
{
	if (N==0)
		return cl_I_to_LF(0,len);
	var cl_I Q, T;
	eval_pq_series_aux(0,N,args,NULL,&Q,&T);
	return cl_I_to_LF(T,len) / cl_I_to_LF(Q,len);
}
