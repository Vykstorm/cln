#include "test_I.h"

int test_I_integer_length (int iterations)
{
	int error = 0;
	int i;
	// Check against ash.
	for (i = iterations; i > 0; i--) {
		cl_I a = testrandom_I();
		uintL l = integer_length(a);
		if (a >= 0) {
#if !(defined(__GNUC__) && (__GNUC_MINOR__ < 8))
			ASSERT1(a < ash(1,l) && (a == 0 ? l == 0 : l > 0 && a >= ash(1,l-1)), a);
#else // work around g++ 2.7.0 bug
			int b = 0;
			if (a < ash(1,l)) {
				if (a == 0)
					b = (l == 0);
				else
					b = (l > 0 && a >= ash(1,l-1));
			}
			ASSERT1(b, a);
#endif
		} else {
#if !(defined(__GNUC__) && (__GNUC_MINOR__ < 8))
			ASSERT1(a >= ash(-1,l) && (a == -1 ? l == 0 : l > 0 && a < ash(-1,l-1)), a);
#else // work around g++ 2.7.0 bug
			int b = 0;
			if (a >= ash(-1,l)) {
				if (a == -1)
					b = (l == 0);
				else
					b = (l > 0 && a < ash(-1,l-1));
			}
			ASSERT1(b, a);
#endif
		}
	}
	return error;
}
