// least_negative_float().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_F_leastneg)

// Specification.
#include "cln/float.h"

// Implementation.

#include "cl_F.h"
#include "cl_SF.h"
#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"

namespace cln {

// Exponent so klein wie möglich, Mantisse 10...0, Vorzeichen -.

static const cl_SF least_negative_SF =
	make_SF(-1,SF_exp_low,bit(SF_mant_len));

static const cl_FF least_negative_FF =
	encode_FF(-1,FF_exp_low-FF_exp_mid,bit(FF_mant_len));

static const cl_DF least_negative_DF =
	#if (cl_word_size==64)
	  encode_DF(-1,DF_exp_low-DF_exp_mid,bit(DF_mant_len));
	#else
	  encode_DF(-1,DF_exp_low-DF_exp_mid,bit(DF_mant_len-32),0);
	#endif

inline const cl_LF least_negative_LF (uintC len)
{
	var Lfloat erg = allocate_lfloat(len,LF_exp_low,-1);
	#if CL_DS_BIG_ENDIAN_P
	  TheLfloat(erg)->data[0] = bit(intDsize-1);
	  clear_loop_up(&TheLfloat(erg)->data[1],len-1);
	#else
	  var uintD* ptr = clear_loop_up(&TheLfloat(erg)->data[0],len-1);
	  *ptr = bit(intDsize-1);
	#endif
	return erg;
}

const cl_F least_negative_float (float_format_t f)
{
	floatformatcase((uintL)f
	,	return least_negative_SF;
	,	return least_negative_FF;
	,	return least_negative_DF;
	,	return least_negative_LF(len);
	);
}

}  // namespace cln

CL_PROVIDE_END(cl_F_leastneg)
