// binary operator /

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

const cl_R operator/ (const cl_R& x, const cl_R& y)
{
	if (eq(x,0))
		// 0 / y = exakte 0, auﬂer wenn y=0
		{ if (zerop(y))
			{ cl_error_division_by_0(); }
		  else
			return 0;
		}
	else
#define div(a,b) a/b
	realcase6(x
	, /* I */	
			realcase6(y
			, /* I */	return div(x,y);
			, /* RT */	return div(x,y);
			, /* SF */	return div(cl_I_to_SF(x),y);
			, /* FF */	return div(cl_I_to_FF(x),y);
			, /* DF */	return div(cl_I_to_DF(x),y);
			, /* LF */	return div(cl_I_to_LF(x,LFlen0(y)),y); // cf. cl_I_LF_div
			);
	, /* RT */	
			realcase6(y
			, /* I */	return div(x,y);
			, /* RT */	return div(x,y);
			, /* SF */	return div(cl_RA_to_SF(x),y);
			, /* FF */	return div(cl_RA_to_FF(x),y);
			, /* DF */	return div(cl_RA_to_DF(x),y);
			, /* LF */	return cl_RA_LF_div(x,y);
			);
	, /* SF */	
			realcase6(y
			, /* I */	return div(x,cl_I_to_SF(y));
			, /* RT */	return div(x,cl_RA_to_SF(y));
			, /* SF */	return div(x,y);
			, /* FF */	return cl_FF_to_SF(div(cl_SF_to_FF(x),y));
			, /* DF */	return cl_DF_to_SF(div(cl_SF_to_DF(x),y));
			, /* LF */	return cl_LF_to_SF(div(cl_SF_to_LF(x,LFlen0(y)),y));
			);
	, /* FF */	
			realcase6(y
			, /* I */	return div(x,cl_I_to_FF(y));
			, /* RT */	return div(x,cl_RA_to_FF(y));
			, /* SF */	return cl_FF_to_SF(div(x,cl_SF_to_FF(y)));
			, /* FF */	return div(x,y);
			, /* DF */	return cl_DF_to_FF(div(cl_FF_to_DF(x),y));
			, /* LF */	return cl_LF_to_FF(div(cl_FF_to_LF(x,LFlen0(y)),y));
			);
	, /* DF */	
			realcase6(y
			, /* I */	return div(x,cl_I_to_DF(y));
			, /* RT */	return div(x,cl_RA_to_DF(y));
			, /* SF */	return cl_DF_to_SF(div(x,cl_SF_to_DF(y)));
			, /* FF */	return cl_DF_to_FF(div(x,cl_FF_to_DF(y)));
			, /* DF */	return div(x,y);
			, /* LF */	return cl_LF_to_DF(div(cl_DF_to_LF(x,LFlen0(y)),y));
			);
	, /* LF */	
			realcase6(y
			, /* I */	return cl_LF_I_div(x,y);
			, /* RT */	return cl_LF_RA_div(x,y);
			, /* SF */	return cl_LF_to_SF(div(x,cl_SF_to_LF(y,LFlen0(x))));
			, /* FF */	return cl_LF_to_FF(div(x,cl_FF_to_LF(y,LFlen0(x))));
			, /* DF */	return cl_LF_to_DF(div(x,cl_DF_to_LF(y,LFlen0(x))));
			, /* LF */	return div(x,y);
			);
	);
}
