// Abnormal program exit.

#ifndef _CL_ABORT_H
#define _CL_ABORT_H

#ifdef _CL_MACROS_H
nonreturning_function(extern, cl_abort, (void));
#else
extern void cl_abort (void);
#endif

#endif /* _CL_ABORT_H */
