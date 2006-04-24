// cl_make_heap_GV_I().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_GV_I)

// Specification.
#include "cln/GV_integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cln/abort.h"
#include "cl_offsetof.h"

namespace cln {

// Memory-efficient integer vectors: If all entries are known in advance to
// be >= 0 and < 2^m, we reserve only m bits for each entry. (m=1,2,4,8,16,32).
// Thus we end up with 6 kinds of bit/byte vectors, and the general integer
// vectors.
// For enquiring purposes, we store m in the vectorops table. Because of this,
// treating a cl_GV_RA as cl_GV_I is wrong. In particular, we cannot use the
// cl_null_GV_N to initialize a cl_GV_I; need a special cl_null_GV_I.


static void cl_gvector_integer_destructor (cl_heap* pointer)
{
#if (defined(__mips__) || defined(__mips64__)) && !defined(__GNUC__) // workaround SGI CC bug
	(*(cl_heap_GV_I*)pointer).~cl_heap_GV();
#else
	(*(cl_heap_GV_I*)pointer).~cl_heap_GV_I();
#endif
}

cl_class cl_class_gvector_integer = {
	cl_gvector_integer_destructor,
	0
};


static inline cl_heap_GV_I * outcast (cl_GV_inner<cl_I>* vec)
{
	return (cl_heap_GV_I *)((char *) vec - offsetof(cl_heap_GV_I,v));
}
static inline const cl_heap_GV_I * outcast (const cl_GV_inner<cl_I>* vec)
{
	return (const cl_heap_GV_I *)((const char *) vec - offsetof(cl_heap_GV_I,v));
}


// Add more info to the vectorops tables.

struct cl_GV_I_vectorops {
	cl_GV_vectorops<cl_I> ops;
	sintC m; // for maxbits
};

static inline cl_GV_I_vectorops* outcast (cl_GV_vectorops<cl_I>* vectorops)
{
	return (cl_GV_I_vectorops*)((char *) vectorops - offsetof(cl_GV_I_vectorops,ops));
}


// Vectors of general integers.

struct cl_heap_GV_I_general : public cl_heap_GV_I {
	cl_I data[1];
	// Standard allocation disabled.
	void* operator new (size_t size) { unused size; cl_abort(); return (void*)1; }
	// Standard deallocation disabled.
	void operator delete (void* ptr) { unused ptr; cl_abort(); }
	// No default constructor.
	cl_heap_GV_I_general ();
};

static const cl_I general_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	return ((const cl_heap_GV_I_general *) outcast(vec))->data[index];
}

static void general_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	((cl_heap_GV_I_general *) outcast(vec))->data[index] = x;
}

static void general_do_delete (cl_GV_inner<cl_I>* vec)
{
	var cl_heap_GV_I_general* hv = (cl_heap_GV_I_general *) outcast(vec);
	var uintC len = hv->v.length();
	for (var uintC i = 0; i < len; i++)
		hv->data[i].~cl_I();
}

static void general_copy_elements (const cl_GV_inner<cl_I>* srcvec, uintC srcindex, cl_GV_inner<cl_I>* destvec, uintC destindex, uintC count)
{
	if (count > 0) {
		var const cl_heap_GV_I_general* srcv =
		  (const cl_heap_GV_I_general *) outcast(srcvec);
		var cl_heap_GV_I_general* destv =
		  (cl_heap_GV_I_general *) outcast(destvec);
		var uintC srclen = srcv->v.length();
		var uintC destlen = destv->v.length();
		if (!(srcindex <= srcindex+count && srcindex+count <= srclen))
			cl_abort();
		if (!(destindex <= destindex+count && destindex+count <= destlen))
			cl_abort();
		do {
			destv->data[destindex++] = srcv->data[srcindex++];
		} while (--count > 0);
	}
}

static cl_GV_I_vectorops general_vectorops = {{
	general_element,
	general_set_element,
	general_do_delete,
	general_copy_elements },
	-1
};

cl_heap_GV_I* cl_make_heap_GV_I (uintC len)
{
	var cl_heap_GV_I_general* hv = (cl_heap_GV_I_general*) malloc_hook(offsetofa(cl_heap_GV_I_general,data)+sizeof(cl_I)*len);
	hv->refcount = 1;
	hv->type = &cl_class_gvector_integer;
	new (&hv->v) cl_GV_inner<cl_I> (len,&general_vectorops.ops);
	for (var uintC i = 0; i < len; i++)
		init1(cl_I, hv->data[i]) ();
	return hv;
}


// Vectors of integers requiring only few bits.

#define DEFINE_cl_heap_GV_I_bits(m,uint_t)  \
struct cl_heap_GV_I_bits##m : public cl_heap_GV_I {			\
	uint_t data[1];							\
	/* Standard allocation disabled. */				\
	void* operator new (size_t size) { unused size; cl_abort(); return (void*)1; } \
	/* Standard deallocation disabled. */				\
	void operator delete (void* ptr) { unused ptr; cl_abort(); }	\
	/* No default constructor. */					\
	cl_heap_GV_I_bits##m ();					\
};									\
static const cl_I bits##m##_element (const cl_GV_inner<cl_I>* vec, uintC index); \
static void bits##m##_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x); \
static void bits##m##_copy_elements (const cl_GV_inner<cl_I>* srcvec, uintC srcindex, cl_GV_inner<cl_I>* destvec, uintC destindex, uintC count) \
{										\
	if (count > 0) {							\
		var const cl_heap_GV_I_bits##m * srcv =				\
		  (const cl_heap_GV_I_bits##m *) outcast(srcvec);		\
		var cl_heap_GV_I_bits##m * destv =				\
		  (cl_heap_GV_I_bits##m *) outcast(destvec);			\
		var uintC srclen = srcv->v.length();				\
		var uintC destlen = destv->v.length();				\
		if (!(srcindex <= srcindex+count && srcindex+count <= srclen))	\
			cl_abort();						\
		if (!(destindex <= destindex+count && destindex+count <= destlen)) \
			cl_abort();						\
		if (m == intDsize) {						\
			var const uintD* srcptr = &srcv->data[srcindex];	\
			var uintD* destptr = &destv->data[destindex];		\
			do {							\
				*destptr++ = *srcptr++;				\
			} while (--count > 0);					\
		} else								\
			bits_copy(srcv->data,m*srcindex,destv->data,m*destindex,m*count); \
	}									\
}									\
static cl_GV_I_vectorops bits##m##_vectorops = {{			\
	bits##m##_element,						\
	bits##m##_set_element,						\
	bits_do_delete,							\
	bits##m##_copy_elements },					\
	m								\
};

static void bits_do_delete (cl_GV_inner<cl_I>* vec)
{
	unused vec;
}

// Copy bits srcptr.bits[srcindex..srcindex+count-1] into destptr.bits[destindex..destindex+count-1].
// Assumes that all range checks have already been performed.
static void bits_copy (const uintD* srcptr, uintC srcindex, uintD* destptr, uintC destindex, uintC count)
{
	srcptr += floor(srcindex,intDsize);
	destptr += floor(destindex,intDsize);
	srcindex = srcindex%intDsize;
	destindex = destindex%intDsize;
	// Now 0 <= srcindex < intDsize and 0 <= destindex < intDsize.
	if (srcindex == destindex) {
		// src and dest are aligned with respect to each other.
		if (srcindex > 0) {
			if (count <= intDsize-srcindex) {
				*destptr ^= (*destptr ^ *srcptr) & ((uintD)(bit(count)-1) << srcindex);
				return;
			}
			*destptr ^= (*destptr ^ *srcptr) & (uintD)minus_bit(srcindex);
			srcptr++;
			destptr++;
			count -= intDsize-srcindex;
		}
		// Now srcindex and destindex can be assumed to be 0.
		var uintC count1 = count%intDsize;
		count = floor(count,intDsize);
		if (count > 0) {
			do {
				*destptr++ = *srcptr++;
			} while (--count > 0);
		}
		if (count1 > 0) {
			*destptr ^= (*destptr ^ *srcptr) & (uintD)(bit(count1)-1);
		}
	} else {
		var uintC i = destindex - srcindex;
		var uintD tmp;
		if (destindex >= srcindex) { // i > 0
			if (count <= intDsize-destindex) {
				*destptr ^= (*destptr ^ (*srcptr << i)) & ((uintD)(bit(count)-1) << destindex);
				return;
			}
			*destptr ^= (*destptr ^ (*srcptr << i)) & (uintD)minus_bit(destindex);
			destptr++;
			tmp = *srcptr >> (intDsize-i);
			count -= intDsize-destindex;
		} else { // i < 0
			if (count <= intDsize-srcindex) {
				*destptr ^= (*destptr ^ (*srcptr >> -i)) & ((uintD)(bit(count)-1) << destindex);
				return;
			}
			tmp = (*destptr & (uintD)(bit(destindex)-1)) | ((*srcptr >> srcindex) << destindex);
			count += destindex;
			i += intDsize;
		}
		srcptr++;
		// tmp now contains the low i bits to be put into *destptr.
		var uintC count1 = count%intDsize;
		count = floor(count,intDsize);
		var uintD lastdest;
		if (count == 0)
			lastdest = tmp;
		else {
			lastdest = shiftleftcopy_loop_up(srcptr,destptr,count,i);
			*destptr |= tmp;
		}
		// lastdest now contains the i bits shifted out of the top of the source.
		if (count1 > 0) {
			destptr += count;
			if (count1 > i)
				lastdest |= *(srcptr += count) << i;
			*destptr ^= (*destptr ^ lastdest) & (uintD)(bit(count1)-1);
		}
	}
}	


// It would be most natural to use the following type for uint_t:
// m = 1: uint_t = uint8
// m = 2: uint_t = uint8
// m = 4: uint_t = uint8
// m = 8: uint_t = uint8
// m = 16: uint_t = uint16
// m = 32: uint_t = uint32
// But we want to have a fast copy_elements routine. And for m=1,
// we also want to use the fast shiftxor_loop_up() function for addition.
// Hence we use the uint_t = uintD in all cases. (NB: intDsize>=32.)

// The last ceiling(len*m/intDsize)*intDsize-len*m unused bits in the last word
// are always 0. This provides some simplification for routines which work on
// entire words: They don't need to special-case the last word.


DEFINE_cl_heap_GV_I_bits(1,uintD)

static const cl_I bits1_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	return (unsigned int)((((const cl_heap_GV_I_bits1 *) outcast(vec))->data[index/intDsize] >> (index%intDsize)) & 0x1);
}
static void bits1_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uintV xval;
	if (fixnump(x)) {
		xval = FN_to_UV(x);
		if (xval <= 0x1) {
			var uintD* ptr = &((cl_heap_GV_I_bits1 *) outcast(vec))->data[index/intDsize];
			index = index%intDsize;
			*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0x1 << index));
			return;
		}
	}
	cl_abort();
}


DEFINE_cl_heap_GV_I_bits(2,uintD)

static const cl_I bits2_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	return (unsigned int)((((const cl_heap_GV_I_bits2 *) outcast(vec))->data[index/(intDsize/2)] >> (2*(index%(intDsize/2)))) & 0x3);
}
static void bits2_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uintV xval;
	if (fixnump(x)) {
		xval = FN_to_UV(x);
		if (xval <= 0x3) {
			var uintD* ptr = &((cl_heap_GV_I_bits2 *) outcast(vec))->data[index/(intDsize/2)];
			index = 2*(index%(intDsize/2));
			*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0x3 << index));
			return;
		}
	}
	cl_abort();
}


DEFINE_cl_heap_GV_I_bits(4,uintD)

static const cl_I bits4_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	return (unsigned int)((((const cl_heap_GV_I_bits4 *) outcast(vec))->data[index/(intDsize/4)] >> (4*(index%(intDsize/4)))) & 0xF);
}
static void bits4_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uintV xval;
	if (fixnump(x)) {
		xval = FN_to_UV(x);
		if (xval <= 0xF) {
			var uintD* ptr = &((cl_heap_GV_I_bits4 *) outcast(vec))->data[index/(intDsize/4)];
			index = 4*(index%(intDsize/4));
			*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0xF << index));
			return;
		}
	}
	cl_abort();
}


DEFINE_cl_heap_GV_I_bits(8,uintD)

static const cl_I bits8_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	#if CL_CPU_BIG_ENDIAN_P
	return (unsigned int)((((const cl_heap_GV_I_bits8 *) outcast(vec))->data[index/(intDsize/8)] >> (8*(index%(intDsize/8)))) & 0xFF);
	#else
	// Optimization which assumes little-endian storage of uint8 in an uintD
	return (unsigned int)(((uint8*)(((const cl_heap_GV_I_bits8 *) outcast(vec))->data))[index]);
	#endif
}
static void bits8_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uintV xval;
	if (fixnump(x)) {
		xval = FN_to_UV(x);
		if (xval <= 0xFF) {
			#if CL_CPU_BIG_ENDIAN_P
			var uintD* ptr = &((cl_heap_GV_I_bits8 *) outcast(vec))->data[index/(intDsize/8)];
			index = 8*(index%(intDsize/8));
			*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0xFF << index));
			#else
			// Optimization which assumes little-endian storage of uint8 in an uintD
			((uint8*)(((cl_heap_GV_I_bits8 *) outcast(vec))->data))[index] = xval;
			#endif
			return;
		}
	}
	cl_abort();
}


DEFINE_cl_heap_GV_I_bits(16,uintD)

static const cl_I bits16_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	#if CL_CPU_BIG_ENDIAN_P
	return (unsigned int)((((const cl_heap_GV_I_bits16 *) outcast(vec))->data[index/(intDsize/16)] >> (16*(index%(intDsize/16)))) & 0xFFFF);
	#else
	// Optimization which assumes little-endian storage of uint16 in an uintD
	return (unsigned int)(((uint16*)(((const cl_heap_GV_I_bits16 *) outcast(vec))->data))[index]);
	#endif
}
static void bits16_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uintV xval;
	if (fixnump(x)) {
		xval = FN_to_UV(x);
		if (xval <= 0xFFFF) {
			#if CL_CPU_BIG_ENDIAN_P
			var uintD* ptr = &((cl_heap_GV_I_bits16 *) outcast(vec))->data[index/(intDsize/16)];
			index = 16*(index%(intDsize/16));
			*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0xFFFF << index));
			#else
			// Optimization which assumes little-endian storage of uint16 in an uintD
			((uint16*)(((cl_heap_GV_I_bits16 *) outcast(vec))->data))[index] = xval;
			#endif
			return;
		}
	}
	cl_abort();
}


DEFINE_cl_heap_GV_I_bits(32,uintD)

static const cl_I bits32_element (const cl_GV_inner<cl_I>* vec, uintC index)
{
	#if (intDsize==32)
	return (unsigned long)(((const cl_heap_GV_I_bits32 *) outcast(vec))->data[index]);
	#elif CL_CPU_BIG_ENDIAN_P
	return (unsigned long)((((const cl_heap_GV_I_bits32 *) outcast(vec))->data[index/(intDsize/32)] >> (32*(index%(intDsize/32)))) & 0xFFFFFFFF);
	#else
	// Optimization which assumes little-endian storage of uint32 in an uintD
	return (unsigned long)(((uint32*)(((const cl_heap_GV_I_bits32 *) outcast(vec))->data))[index]);
	#endif
}
static void bits32_set_element (cl_GV_inner<cl_I>* vec, uintC index, const cl_I& x)
{
	var uint32 xval = cl_I_to_UL(x);
	#if (intDsize==32)
	((cl_heap_GV_I_bits32 *) outcast(vec))->data[index] = xval;
	#elif CL_CPU_BIG_ENDIAN_P
	var uintD* ptr = &((cl_heap_GV_I_bits32 *) outcast(vec))->data[index/(intDsize/32)];
	index = 32*(index%(intDsize/32));
	*ptr = *ptr ^ ((*ptr ^ ((uintD)xval << index)) & ((uintD)0xFFFFFFFF << index));
	#else
	// Optimization which assumes little-endian storage of uint32 in an uintD
	((uint32*)(((cl_heap_GV_I_bits32 *) outcast(vec))->data))[index] = xval;
	#endif
}


static cl_GV_I_vectorops* bits_vectorops[6] = {
	&bits1_vectorops,
	&bits2_vectorops,
	&bits4_vectorops,
	&bits8_vectorops,
	&bits16_vectorops,
	&bits32_vectorops
};

cl_heap_GV_I* cl_make_heap_GV_I (uintC len, sintC m)
{
	// Determine log2(bits).
	var uintL log2_bits;
	switch (m) {
		case 0: case 1:
			log2_bits = 0; break;
		case 2:
			log2_bits = 1; break;
		case 3: case 4:
			log2_bits = 2; break;
		case 5: case 6: case 7: case 8:
			log2_bits = 3; break;
		case 9: case 10: case 11: case 12:
		case 13: case 14: case 15: case 16:
			log2_bits = 4; break;
		case 17: case 18: case 19: case 20:
		case 21: case 22: case 23: case 24:
		case 25: case 26: case 27: case 28:
		case 29: case 30: case 31: case 32:
			log2_bits = 5; break;
		default:
			return cl_make_heap_GV_I(len);
	}
	// For room allocation purposes, be pessimistic: assume the uintD case (since intDsize>=32).
	var uintC words = // ceiling(len*2^log2_bits,intDsize)
	  (((sintC)len-1)>>(log2_intDsize-log2_bits))+1;
	var cl_heap_GV_I_bits32* hv = (cl_heap_GV_I_bits32*) malloc_hook(offsetofa(cl_heap_GV_I_bits32,data)+sizeof(uintD)*words);
	hv->refcount = 1;
	hv->type = &cl_class_gvector_integer;
	new (&hv->v) cl_GV_inner<cl_I> (len,&bits_vectorops[log2_bits]->ops);
	var uintD* ptr = (uintD*)(hv->data);
	for (var uintC i = 0; i < words; i++)
		ptr[i] = 0;
	return (cl_heap_GV_I*) hv;
}


sintC cl_heap_GV_I::maxbits () const
{
	return outcast(v.vectorops)->m;
}


// An empty vector.
const cl_GV_I cl_null_GV_I = cl_GV_I((uintC)0);

}  // namespace cln

CL_PROVIDE_END(cl_GV_I)
