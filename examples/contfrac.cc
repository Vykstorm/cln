// Print the continued fraction of a real number.

// We work with real numbers and integers.
#include <cl_real.h>
#include <cl_integer.h>

// We do I/O.
#include <cl_io.h>
#include <cl_integer_io.h>

// Our private error handling: return to the main program.
#include <setjmp.h>
jmp_buf restartpoint;
void cl_abort (void) { longjmp(restartpoint,1); }

int main (int argc, char* argv[])
{
	for (int i = 1; i < argc; i++) {
		const char * arg = argv[i];
		if (setjmp(restartpoint))
			continue;
		// Convert argument to its internal representation:
		cl_R x = arg;
		// Check sign.
		if (minusp(x)) {
			fprint(cl_stdout, "-");
			x = -x;
		}
		fprint(cl_stdout, "[");
		const char* separator = "; ";
		for (;;) {
			// Split x into integral and fractional part.
			cl_R_div_t x_split = floor2(x);
			fprint(cl_stdout, x_split.quotient);
			x = x_split.remainder;
			if (zerop(x))
				break;
			fprint(cl_stdout, separator);
			separator = ", ";
			// Invert x.
			x = recip(x);
		}
		fprint(cl_stdout, "]\n");
	}
}
