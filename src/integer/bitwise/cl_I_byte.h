// cl_I internals for BYTE operations

#ifndef _CL_I_BYTE_H
#define _CL_I_BYTE_H

#include "cl_number.h"
#include "cl_integer_class.h"

// cl_fullbyte(p,q) liefert zu p,q die Zahl 2^q-2^p als Integer,
// wobei p und q uintL sind. Bei p<=q ist das Ergebnis also
// ein Integer >=0, bei dem genau die Bits p,...,q-1 gesetzt sind.
extern const cl_I cl_fullbyte (uintL p, uintL q);

// Extrahiere die Bits p,...,q-1 der Zahl x,
// wobei 0 <= p <= q <= l = (integer-length x).
// Ergebnis (wie bei LDB) ein Integer >=0.
extern const cl_I ldb_extract (const cl_I& x, uintL p, uintL q);

// Teste, ob eines der Bits p,...,q-1 der Zahl x /=0 ist,
// wobei 0 <= p <= q <= l = (integer-length x).
// Ergebnis (wie bei LDB-TEST) cl_false wenn nein, cl_true wenn ja.
extern cl_boolean ldb_extract_test (const cl_I& x, uintL p, uintL q);

// Extrahiere die Bits p,...,q-1 der Zahl x,
// wobei 0 <= p <= q <= l = (integer-length x).
// Ergebnis (wie bei MASK-FIELD) ein Integer >=0.
extern const cl_I mkf_extract (const cl_I& x, uintL p, uintL q);

#endif /* _CL_I_BYTE_H */
