#include <stdlib.h>
#include <string.h>
#include <cl_io.h>

extern int test_I (int iterations);
extern int test_MI (int iterations);
extern int test_nt (int iterations);

int test_all (int iterations)
{
	int error = 0;
	error |= test_I(iterations);
	error |= test_MI(iterations);
	error |= test_nt(iterations);
	return error;
}

int main (int argc, char* argv[])
{
	int iterations = 10000;
	if ((argc >= 3) && !strcmp(argv[1],"-i")) {
		iterations = atoi(argv[2]);
		argc -= 2; argv += 2;
	}
	if (argc < 1)
		exit(1);

	if (!test_all(iterations)) {
		fprint (cl_stdout, "Tests passed.\n");
		exit(0);
	} else {
		fprint (cl_stdout, "Tests failed.\n");
		exit(1);
	}
}
