// cl_I equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_N.h"
#include "cl_I.h"

namespace cln {

inline uint32 equal_hashcode (const cl_FN& x)
{
	var cl_signean sign;
	var uint32 x32 = FN_to_L(x); // x als 32-Bit-Zahl
	if (FN_L_minusp(x,(sint32)x32)) {
		x32 = -x32;
		sign = -1;
	} else {
		sign = 0;
		if (x32 == 0)
			return 0;
	}
	var uintL s;
	integerlength32(x32, s = 32 - );
	var uint32 msd = x32 << s;
	var sintL exp = 32-s;
	return equal_hashcode_low(msd,exp,sign);
}

inline uint32 equal_hashcode (const cl_BN& x)
{
	var const uintD* MSDptr;
	var uintC len;
	BN_to_NDS_nocopy(x, MSDptr = , len = ,);
	// Nicht alle führenden intDsize+1 Bits sind gleich.
#if (intDsize==64)
	var uint64 msd = mspref(MSDptr,0);
	var uint64 msd2 = (len >= 2 ? mspref(MSDptr,1) : 0);
	var cl_signean sign;
	if ((sint64)msd < 0) { // falls <0, negieren
		sign = -1;
		// msd|msd2 := - msd|msd2 - (1 falls noch weitere Bits /= 0)
		msd = ~msd; msd2 = ~msd2;
		if ((len <= 2)
		    || !test_loop_msp(MSDptr mspop 2, len - 2)
		   ) {
			msd2++;
			if (msd2 == 0)
				msd++;
		}
	} else {
		sign = 0;
	}
	var sintL exp = (uintL)len * intDsize;
	// Nicht alle führenden 65 Bits sind =0.
	if (msd==0) {
		msd = msd2;
		exp -= 64;
	} else {
		var uintL s;
		integerlength64(msd, s = 64 - );
		if (s > 0)
			msd = (msd << s) | (msd2 >> (64-s));
		exp -= s;
	}
	return equal_hashcode_low((uint32)(msd>>32),exp,sign);
#else // (intDsize<=32)
	var uint32 msd;
	var uint32 msd2;
	if (len >= 64/intDsize) {
		msd = get_32_Dptr(MSDptr);
		msd2 = get_32_Dptr(MSDptr mspop 32/intDsize);
	} elif (len > 32/intDsize) {
		msd = get_32_Dptr(MSDptr);
		msd2 = get_max32_Dptr(intDsize*len-32, MSDptr mspop 32/intDsize)
		       << (64-intDsize*len);
	} elif ((32/intDsize == 1) || (len == 32/intDsize)) {
		msd = get_32_Dptr(MSDptr);
		msd2 = 0;
	} else { // (len > 0) && (len < 32/intDsize)
		msd = get_max32_Dptr(intDsize*len,MSDptr) << (32-intDsize*len);
		msd2 = 0;
	}
	var cl_signean sign;
	if ((sint32)msd < 0) { // falls <0, negieren
		sign = -1;
		// msd|msd2 := - msd|msd2 - (1 falls noch weitere Bits /= 0)
		msd = ~msd; msd2 = ~msd2;
		if ((len <= 64/intDsize)
		    || !test_loop_msp(MSDptr mspop 64/intDsize, len - 64/intDsize)
		   ) {
			msd2++;
			if (msd2 == 0)
				msd++;
		}
	} else {
		sign = 0;
	}
	var sintL exp = (uintL)len * intDsize;
	// Nicht alle führenden intDsize+1 Bits sind =0.
	// Wegen intDsize<=32: Nicht alle führenden 33 Bits sind =0.
	if (msd==0) {
		msd = msd2;
		exp -= 32;
	}
	// Nicht alle führenden 32 Bits sind =0.
	// Führendes Bit auf 1 normalisieren:
	else {
		var uintL s;
		integerlength32(msd, s = 32 - );
		if (s > 0)
			msd = (msd << s) | (msd2 >> (32-s));
		exp -= s;
	}
	return equal_hashcode_low(msd,exp,sign);
#endif
}

MAYBE_INLINE
uint32 equal_hashcode (const cl_I& x)
{
	if (fixnump(x)) {
		DeclareType(cl_FN,x);
		return equal_hashcode(x);
	} else {
		DeclareType(cl_BN,x);
		return equal_hashcode(x);
	}
}

}  // namespace cln
