// Abnormal program exit.

#ifndef _CL_ABORT_H
#define _CL_ABORT_H

namespace cln {

#ifdef _CL_MACROS_H
nonreturning_function(extern, cl_abort, (void));
#else
extern void cl_abort (void);
#endif

}  // namespace cln

#endif /* _CL_ABORT_H */
