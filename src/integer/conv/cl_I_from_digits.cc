// digits_to_I().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cl_DS.h"

namespace cln {

static const cl_I digits_to_I_base2 (const char * MSBptr, uintL len, uintD base)
{
	// base is a power of two: write the digits from least significant
	// to most significant into the result NUDS. Result needs
	// 1+ceiling(len*log(base)/(intDsize*log(2))) or some more digits
	CL_ALLOCA_STACK;
	var uintD* erg_MSDptr;
	var uintC erg_len;
	var uintD* erg_LSDptr;
	var int b = (base==2 ? 1 : base==4 ? 2 : base==8 ? 3 : base==16 ? 4 : /*base==32*/ 5);
	num_stack_alloc(1+(len*b)/intDsize,,erg_LSDptr=);
	erg_MSDptr = erg_LSDptr; erg_len = 0;
	var uintD d = 0;  // resulting digit
	var int ch_where = 0;  // position of ch inside d
	while (len > 0) {
		var uintB ch = *(const uintB *)(MSBptr+len-1); // next character
		if (ch!='.') { // skip decimal point
			// Compute value of ch ('0'-'9','A'-'Z','a'-'z'):
			ch = ch - '0';
			if (ch > '9'-'0') { // not a digit?
				ch = ch+'0'-'A'+10;
				if (ch > 'Z'-'A'+10) {// not an uppercase letter?
					ch = ch+'A'-'a'; // must be lowercase!
				}
			}
			d = d | (uintD)ch<<ch_where;
			ch_where = ch_where+b;
			if (ch_where >= intDsize) {
			    // d is ready to be written into the NUDS:
			    lsprefnext(erg_MSDptr) = d;
			    ch_where = ch_where-intDsize;
			    d = (uintD)ch >> b-ch_where;  // carry
			    erg_len++;
			}
		}
		len--;
	}
	if (d != 0) {  // is there anything left over?
		lsprefnext(erg_MSDptr) = d;
		++erg_len;
	}
	return NUDS_to_I(erg_MSDptr,erg_len);
}

// For each base b in [2..36], power_table[b-2] contains the largest exponent e
// such that b^e<2^intDsize, i.e. floor(log(2^intDsize-1,b)).
static const uintC power_table [36-2+1] = {
#if (intDsize==8)
	/* base  2..7  */           7,  5,  3,  3,  3,  2,
	/* base  8..15 */   2,  2,  2,  2,  2,  2,  2,  2,
	/* base 16..23 */   1,  1,  1,  1,  1,  1,  1,  1,
	/* base 24..31 */   1,  1,  1,  1,  1,  1,  1,  1,
	/* base 32..36 */   1,  1,  1,  1,  1
#endif
#if (intDsize==16)
	/* base  2..7  */          15, 10,  7,  6,  6,  5,
	/* base  8..15 */   5,  5,  4,  4,  4,  4,  4,  4,
	/* base 16..23 */   3,  3,  3,  3,  3,  3,  3,  3,
	/* base 24..31 */   3,  3,  3,  3,  3,  3,  3,  3,
	/* base 32..36 */   3,  3,  3,  3,  3
#endif
#if (intDsize==32)
	/* base  2..7  */          31, 20, 15, 13, 12, 11,
	/* base  8..15 */  10, 10,  9,  9,  8,  8,  8,  8,
	/* base 16..23 */   7,  7,  7,  7,  7,  7,  7,  7,
	/* base 24..31 */   6,  6,  6,  6,  6,  6,  6,  6,
	/* base 32..36 */   6,  6,  6,  6,  6
#endif
#if (intDsize==64)
	/* base  2..7  */          63, 40, 31, 27, 24, 22,
	/* base  8..15 */  21, 20, 19, 18, 17, 17, 16, 16,
	/* base 16..23 */  15, 15, 15, 15, 14, 14, 14, 14,
	/* base 24..31 */  13, 13, 13, 13, 13, 13, 13, 12,
	/* base 32..36 */  12, 12, 12, 12, 12
#endif
};

static const cl_I digits_to_I_baseN (const char * MSBptr, uintL len, uintD base)
{
	// base is not a power of two: Add digits one by one. Result nees
	// 1+ceiling(len*log(base)/(intDsize*log(2))) or some more digits.
	CL_ALLOCA_STACK;
	var uintD* erg_MSDptr;
	var uintC erg_len;
	var uintD* erg_LSDptr;
	var uintL need = 1+floor(len,intDsize*256); // > len/(intDsize*256) >=0
	switch (base) { // multiply need with ceiling(256*log(base)/log(2)):
		case 2: need = 256*need; break;
		case 3: need = 406*need; break;
		case 4: need = 512*need; break;
		case 5: need = 595*need; break;
		case 6: need = 662*need; break;
		case 7: need = 719*need; break;
		case 8: need = 768*need; break;
		case 9: need = 812*need; break;
		case 10: need = 851*need; break;
		case 11: need = 886*need; break;
		case 12: need = 918*need; break;
		case 13: need = 948*need; break;
		case 14: need = 975*need; break;
		case 15: need = 1001*need; break;
		case 16: need = 1024*need; break;
		case 17: need = 1047*need; break;
		case 18: need = 1068*need; break;
		case 19: need = 1088*need; break;
		case 20: need = 1107*need; break;
		case 21: need = 1125*need; break;
		case 22: need = 1142*need; break;
		case 23: need = 1159*need; break;
		case 24: need = 1174*need; break;
		case 25: need = 1189*need; break;
		case 26: need = 1204*need; break;
		case 27: need = 1218*need; break;
		case 28: need = 1231*need; break;
		case 29: need = 1244*need; break;
		case 30: need = 1257*need; break;
		case 31: need = 1269*need; break;
		case 32: need = 1280*need; break;
		case 33: need = 1292*need; break;
		case 34: need = 1303*need; break;
		case 35: need = 1314*need; break;
		case 36: need = 1324*need; break;
		default: NOTREACHED
	}
	// Now we have need >= len*log(base)/(intDsize*log(2)).
	need += 1;
	// Add digits one by one:
	num_stack_alloc(need,,erg_LSDptr=);
	// erg_MSDptr/erg_len/erg_LSDptr is a NUDS, erg_len < need.
	erg_MSDptr = erg_LSDptr; erg_len = 0;
	while (len > 0) {
		var uintD newdigit = 0;
		var uintC chx = 0;
		var uintD factor = 1;
		while (chx < power_table[base-2] && len > 0) {
			var uintB ch = *(const uintB *)MSBptr; MSBptr++; // next character
			if (ch!='.') { // skip decimal point
				// Compute value of ('0'-'9','A'-'Z','a'-'z'):
				ch = ch-'0';
				if (ch > '9'-'0') { // not a digit?
					ch = ch+'0'-'A'+10;
					if (ch > 'Z'-'A'+10) {// not an uppercase letter?
						ch = ch+'A'-'a';  // must be lowercase!
					}
				}
				factor = factor*base;
				newdigit = base*newdigit+ch;
				chx++;
			}
			len--;
		}
		var uintD carry = mulusmall_loop_lsp(factor,erg_LSDptr,erg_len,newdigit);
		if (carry!=0) {
			// need to extend NUDS:
			lsprefnext(erg_MSDptr) = carry;
			erg_len++;
		}
	}
	return NUDS_to_I(erg_MSDptr,erg_len);
}

const cl_I digits_to_I (const char * MSBptr, uintL len, uintD base)
{
	if ((base & (base-1)) == 0) {
		return digits_to_I_base2(MSBptr, len, base);
	} else {
		// This is quite insensitive to the breakeven point.
		// On a 1GHz Athlon I get approximately:
		//   base  3: breakeven == 15000
		//   base 10: breakeven ==  5000
		//   base 36: breakeven ==  2000
		if (len>50000/base)
			// Divide-and-conquer:
			return digits_to_I(MSBptr,len/2,base)*expt_pos(base,len-len/2)
			      +digits_to_I(MSBptr+len/2,len-len/2,base);
		else
			return digits_to_I_baseN(MSBptr, len, base);
	}
}

}  // namespace cln
