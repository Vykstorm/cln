// print_complex().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex_io.h"


// Implementation.

#include "cl_output.h"
#include "cl_complex.h"
#include "cl_C.h"
#include "cl_real_io.h"

void print_complex (cl_ostream stream, const cl_print_number_flags& flags, const cl_N& z)
{
	if (realp(z)) {
		DeclareType(cl_R,z);
		print_real(stream,flags,z);
	} else {
		DeclareType(cl_C,z);
		var cl_R re = realpart(z);
		var cl_R im = imagpart(z);
		if (flags.complex_readably) {
			// Common Lisp #C(re im) syntax
			fprintchar(stream,'#');
			fprintchar(stream,'C');
			fprintchar(stream,'(');
			print_real(stream,flags,re);
			fprintchar(stream,' ');
			print_real(stream,flags,im);
			fprintchar(stream,')');
		} else {
			// Standard mathematical notation: re + im i
			if (!eq(im,0)) {
				if (!eq(re,0)) {
					// Example: 3-7i
					print_real(stream,flags,re);
					if (minusp(im)) {
						fprintchar(stream,'-');
						print_real(stream,flags,-im);
					} else {
						fprintchar(stream,'+');
						print_real(stream,flags,im);
					}
					fprintchar(stream,'i');
				} else {
					// Example: 6i
					print_real(stream,flags,im);
					fprintchar(stream,'i');
				}
			} else {
				// Example: 8
				print_real(stream,flags,re);
			}
		}
	}
}
