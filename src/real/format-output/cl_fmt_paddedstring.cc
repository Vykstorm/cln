// format_padded_string().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_format.h"


// Implementation.

#include <string.h>

void format_padded_string (cl_ostream stream, sintL mincol, sintL colinc, sintL minpad, char padchar, cl_boolean padleftflag, const char * str)
{
	var sintL need = strlen(str) + minpad; // so viele Zeichen mindestens
	var uintL auxpad = (need < mincol
			    ? ceiling((uintL)(mincol - need), colinc) * colinc
			    : 0
			   );
	if (!padleftflag)
		fprint(stream,str);
	format_padding(stream,minpad+auxpad,padchar);
	if (padleftflag)
		fprint(stream,str);
}
