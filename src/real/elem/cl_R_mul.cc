// binary operator *

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_rational.h"
#include "cl_RA.h"
#include "cl_integer.h"
#include "cl_I.h"
#include "cl_F.h"
#include "cl_sfloat.h"
#include "cl_SF.h"
#include "cl_ffloat.h"
#include "cl_FF.h"
#include "cl_dfloat.h"
#include "cl_DF.h"
#include "cl_lfloat.h"
#include "cl_LF.h"
#include "cl_N.h"

ALL_cl_LF_OPERATIONS_SAME_PRECISION()

const cl_R operator* (const cl_R& x, const cl_R& y)
{
	if (eq(x,0)) { return 0; } // 0 * y = exakte 0
	elif (eq(y,0)) { return 0; } // x * 0 = exakte 0
	else
#define mul(a,b) a*b
	realcase6(x
	, /* I */	
			realcase6(y
			, /* I */	return mul(x,y);
			, /* RT */	return mul(x,y);
			, /* SF */	return mul(cl_I_to_SF(x),y);
			, /* FF */	return mul(cl_I_to_FF(x),y);
			, /* DF */	return mul(cl_I_to_DF(x),y);
			, /* LF */	return cl_LF_I_mul(y,x);
			);
	, /* RT */	
			realcase6(y
			, /* I */	return mul(x,y);
			, /* RT */	return mul(x,y);
			, /* SF */	return mul(cl_RA_to_SF(x),y);
			, /* FF */	return mul(cl_RA_to_FF(x),y);
			, /* DF */	return mul(cl_RA_to_DF(x),y);
			, /* LF */	return cl_LF_RA_mul(y,x);
			);
	, /* SF */	
			realcase6(y
			, /* I */	return mul(x,cl_I_to_SF(y));
			, /* RT */	return mul(x,cl_RA_to_SF(y));
			, /* SF */	return mul(x,y);
			, /* FF */	return cl_FF_to_SF(mul(cl_SF_to_FF(x),y));
			, /* DF */	return cl_DF_to_SF(mul(cl_SF_to_DF(x),y));
			, /* LF */	return cl_LF_to_SF(mul(cl_SF_to_LF(x,LFlen0(y)),y));
			);
	, /* FF */	
			realcase6(y
			, /* I */	return mul(x,cl_I_to_FF(y));
			, /* RT */	return mul(x,cl_RA_to_FF(y));
			, /* SF */	return cl_FF_to_SF(mul(x,cl_SF_to_FF(y)));
			, /* FF */	return mul(x,y);
			, /* DF */	return cl_DF_to_FF(mul(cl_FF_to_DF(x),y));
			, /* LF */	return cl_LF_to_FF(mul(cl_FF_to_LF(x,LFlen0(y)),y));
			);
	, /* DF */	
			realcase6(y
			, /* I */	return mul(x,cl_I_to_DF(y));
			, /* RT */	return mul(x,cl_RA_to_DF(y));
			, /* SF */	return cl_DF_to_SF(mul(x,cl_SF_to_DF(y)));
			, /* FF */	return cl_DF_to_FF(mul(x,cl_FF_to_DF(y)));
			, /* DF */	return mul(x,y);
			, /* LF */	return cl_LF_to_DF(mul(cl_DF_to_LF(x,LFlen0(y)),y));
			);
	, /* LF */	
			realcase6(y
			, /* I */	return cl_LF_I_mul(x,y);
			, /* RT */	return cl_LF_RA_mul(x,y);
			, /* SF */	return cl_LF_to_SF(mul(x,cl_SF_to_LF(y,LFlen0(x))));
			, /* FF */	return cl_LF_to_FF(mul(x,cl_FF_to_LF(y,LFlen0(x))));
			, /* DF */	return cl_LF_to_DF(mul(x,cl_DF_to_LF(y,LFlen0(x))));
			, /* LF */	return mul(x,y);
			);
	);
}
