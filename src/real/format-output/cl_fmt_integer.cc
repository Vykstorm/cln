// format_integer().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_format.h"


// Implementation.

#include "cl_integer_io.h"
#include <string.h>
#include "cl_I.h"

void format_integer (cl_ostream stream, const cl_I& arg,
	unsigned int base, sintL mincol, char padchar,
	char commachar, uintL commainterval, cl_boolean commaflag,
	cl_boolean positive_sign_flag)
{
	if ((mincol == 0) && !commaflag && !positive_sign_flag) {
		// Normale Ausgabe tut's.
		print_integer(stream,base,arg);
		return;
	}
	var char* oldstring = print_integer_to_string(base,arg);
	var uintL oldstring_length = strlen(oldstring);
	var uintL number_of_digits = (minusp(arg) ? oldstring_length-1 : oldstring_length);
	var uintL number_of_commas = (commaflag ? floor(number_of_digits-1,commainterval) : 0);
	var cl_boolean positive_sign = (cl_boolean) (positive_sign_flag && (arg > 0));
	var uintL newstring_length = (positive_sign ? 1 : 0) + oldstring_length + number_of_commas;
	var char* newstring = (char *) cl_malloc_hook(newstring_length+1);
	newstring[newstring_length] = '\0'; // newstring termination
	// newstring füllen:
	{
		// Erst Vorzeichen +:
		if (positive_sign)
			newstring[0] = '+';
		// Dann oldstring in newstring übertragen, dabei Kommata überspringen:
		var uintL oldpos = oldstring_length;
		var uintL oldpos_mod = 0; // = (oldstring_length - oldpos) % commainterval
		var uintL newpos = newstring_length;
		until (oldpos == 0) {
			newstring[--newpos] = oldstring[--oldpos];
			if (number_of_commas > 0) {
				// Check whether ((oldstring_length - oldpos) % commainterval) == 0
				if (++oldpos_mod == commainterval) {
					oldpos_mod = 0;
					// noch ein Komma einzufügen
					newstring[--newpos] = commachar;
					number_of_commas--;
				}
			}
		}
	}
#if 0
	format_padded_string(stream,mincol,1,0,padchar,cl_true,newstring);
#else // expand this special case of format_padded_string inline:
	if ((sintL)newstring_length < mincol)
		format_padding(stream,mincol-newstring_length,padchar);
	fprint(stream,newstring);
#endif
	cl_free_hook(newstring);
	cl_free_hook(oldstring);
}
