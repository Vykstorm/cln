#include "test_I.h"
#include "cl_GV_integer.h"

int test_I_GV (int iterations)
{
	int error = 0;
	int i;
	for (i = iterations; i > 0; i--) {
		uintL m = random32() % 70;
		uintL len = random32() % 64;
		cl_GV_I v = cl_GV_I(len,m);
		cl_I M = random_I((cl_I)1 << m) + 1; // 0 < M <= 2^m
		cl_I a = random_I(M);
		int j;
		for (j = 0; j < len; j++)
			v[j] = mod(a*(j*j),M);
		for (j = len-1; j >= 0; j--)
#if !(defined(__GNUC__) && (__GNUC_MINOR__ < 8))
			ASSERT4(v[j] == mod(a*(j*j),M), m,len,M,j);
#else // work around g++ 2.7.2 bug
			ASSERT4(v[j] == mod(a*(j*j),M), (cl_I)m,(cl_I)len,M,(cl_I)j);
#endif
	}
	return error;
}
