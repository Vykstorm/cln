// cl_R_div_t and cl_R_fdiv_t constructors

#ifndef _CL_R_DIV_T_H
#define _CL_R_DIV_T_H

#include "cl_real.h"
#include "cl_RA.h"
#include "cl_float.h"

inline cl_R_div_t::cl_R_div_t (const cl_I_div_t& result)
	: quotient(result.quotient), remainder(result.remainder) {}

inline cl_R_div_t::cl_R_div_t (const cl_RA_div_t& result)
	: quotient(result.quotient), remainder(result.remainder) {}

inline cl_R_div_t::cl_R_div_t (const cl_F_div_t& result)
	: quotient(result.quotient), remainder(result.remainder) {}

inline cl_R_fdiv_t::cl_R_fdiv_t (const cl_F_fdiv_t& result)
	: quotient(result.quotient), remainder(result.remainder) {}

#endif /* _CL_R_DIV_T_H */
