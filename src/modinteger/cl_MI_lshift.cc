// operator<< on cl_MI.

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_modinteger.h"


// Implementation.

#include "cl_integer.h"

const cl_MI operator<< (const cl_MI& x, sintL y) // assume 0 <= y < 2^31
{
	if (y == 0)
		return x;
	if (y == 1) // frequent case
		return x+x;
	var const cl_modint_ring& R = x.ring();
	// Method:
	// Algorithm 1: divide (x.rep << y) by m.
	//              asymptotical cost: O(y * log m).
	// Algorithm 2: x * expt(2 mod m,y) using modular integer operations.
	//              asymptotical cost: O(log y * (log m)^2).
	// Use algorithm 1 for small y, algorithm 2 for large y.
	if ((R->bits < 0) || (y <= 2*R->bits))
		return cl_MI(R, R->reduce_modulo(x.rep << y));
	else
		return x * expt_pos(R->canonhom(2), (cl_I)(long)y);
}
