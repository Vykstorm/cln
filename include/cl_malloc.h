// User modifiable memory allocator.

#ifndef _CL_MALLOC_H
#define _CL_MALLOC_H

#include <stdlib.h>

// Function like malloc() which returns aligned memory of size (> 0) bytes.
extern void* (*cl_malloc_hook) (size_t size);
// Function like free() which makes available for reuse such memory.
extern void (*cl_free_hook) (void* ptr);

#endif /* _CL_MALLOC_H */
