// random_I().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_random_impl.h"
#include "cl_I.h"
#include "cl_DS.h"

const cl_I random_I (cl_random_state& randomstate, const cl_I& n)
{
	CL_ALLOCA_STACK;
	var const uintD* n_MSDptr;
	var uintC n_len;
	var const uintD* n_LSDptr;
	I_to_NDS_nocopy(n, n_MSDptr=,n_len=,n_LSDptr=,cl_false,); // Digit sequence >0 zu n
	var uintD* MSDptr;
	var uintC len = n_len + ceiling(16,intDsize); // 16 Bits mehr
	// neue UDS mit len Zufallsdigits bilden:
	num_stack_alloc(len,MSDptr=,);
	random_UDS(randomstate,MSDptr,len);
	// und durch n dividieren:
	var DS q;
	var DS r;
	UDS_divide(MSDptr,len,MSDptr mspop len, n_MSDptr,n_len,n_LSDptr, &q,&r);
	// Rest in Integer umwandeln:
	return NUDS_to_I(r.MSDptr,r.len);
}
