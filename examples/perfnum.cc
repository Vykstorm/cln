// This program prints the largest now known perfect number.

#include <cl_integer.h>
#include <cl_integer_io.h>

int main ()
{
	int p = 1398269; // previous one was 1257787
	cl_I x = (((cl_I)1 << p) - 1) << (p-1);
	cout << x << endl;
}
