// cl_I internals for combinatorial functions

#ifndef _CL_I_COMBIN_H
#define _CL_I_COMBIN_H

#include "cl_number.h"
#include "cl_integer_class.h"

// UP für Fakultät:
// Bilde das Produkt prod(a < i <= b, 2*i+1), wobei 0 <= a < b klein.
extern const cl_I cl_I_prod_ungerade (uintL a, uintL b);

#endif /* _CL_I_COMBIN_H */
