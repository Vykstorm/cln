// offsetof() and friends

#ifndef _CL_OFFSETOF_H
#define _CL_OFFSETOF_H

#undef offsetof
#if defined(__GNUG__)
  #define offsetof(type,ident)  ((long)&(((type*)1)->ident)-1)
#else
  #define offsetof(type,ident)  ((long)&(((type*)0)->ident))
#endif
#define offsetofa(type,ident)  offsetof(type,ident[0])

#endif /* _CL_OFFSETOF_H */
