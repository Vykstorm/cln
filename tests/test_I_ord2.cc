#include "test_I.h"

int test_I_ord2 (int iterations)
{
	int error = 0;
	int i;
	// Check against ash and oddp.
	for (i = iterations; i > 0; i--) {
		cl_I a = testrandom_I();
		if (a != 0) {
			uintL n = ord2(a);
			cl_I b = ash(a,-(sintL)n);
			ASSERT1(oddp(b), a);
			ASSERT1(a == ash(b,(sintL)n), a);
		}
	}
	return error;
}
