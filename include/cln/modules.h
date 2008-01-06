// Macros for correct module ordering.

#ifndef _CL_MODULES_H
#define _CL_MODULES_H

// global constructor/destructor naming.
#include "cln/config.h"

// The order of initialization of different compilation units is not
// specified in C++. AIX 4 has a linker which apparently does order
// the modules according to dependencies, so that low-level modules
// will be initialized earlier than the high-level modules which depend
// on them. I (Bruno) have a patch for GNU ld that does the same thing.
//
// But for now, I take a half-automatic approach to the correct module
// ordering problem: PROVIDE/REQUIRE, as in Common Lisp.
//
// CL_PROVIDE(module) must be the first code-generating entity in a module.
// Inline function definitions can precede it, but global variable/function/
// class definitions may not precede it.
// Afterwards, any number of CL_REQUIRE(othermodule) is allowed.
// At the end of the module, there must be a corresponding
// CL_PROVIDE_END(module). (Sorry for this, it's really needed.)
//
// These macros work only with g++, and only in optimizing mode. But who
// wants to use CLN with other C++ compilers anyway...

// How to apply these macros:
// 1. Find out about variables which need to be initialized.
//    On Linux/ELF, you can use a command like
//    $ nm -o libcln.a | grep -v ' [UTtRrW] ' | sort +1
//    A symbol of type "D" or "d" lies in the preinitialized DATA section,
//    a symbol of type "B" or "b" lies in the uninitialized BSS section.
//    All of them have to be checked.
//  - Those which contain POD (= plain old data, i.e. scalar values or
//    class instances without nontrivial constructors) are already fully
//    initialized by the linker and can be discarded from these considerations.
//  - Those which are static variables inside a function (you recognize
//    them: g++ appends a dot and a number to their name) are initialized
//    the first time the function is entered. They can be discarded from
//    our considerations as well.
// 2. Find out which of these variables are publically exposed (to the user of
//    the library) through the library's include files, either directly or
//    through inline functions, or indirectly through normal function calls.
//    These variables can be referenced from any user module U, hence any
//    such module must CL_REQUIRE(M) the variable's definition module M.
//    Since there is no CL_REQUIRE_IF_NEEDED(M) macro (which is equivalent
//    to CL_REQUIRE(M) if the required module will be part of the executable
//    but does nothing if M is not used), we must preventively put the
//    CL_REQUIRE(M) into the header file. Hopefully M is either used anyway
//    or does not bring in too much code into the executable.
// 3. Variables which are not publicly exposed but used internally by the
//    library can be handled by adding a CL_REQUIRE in all the library's
//    modules which directly or indirectly use the variable.
// 4. Variables and functions which can be reasonably assumed to not be
//    accessed or executed during initialization need not be treated.
//    For example, I/O to external streams, exception handling facilities,
//    number theory stuff, etc.

// OK, stop reading here, because it's getting obscene.

#if defined(PIC)
  #define CL_GLOBAL_CONSTRUCTOR_SUFFIX CL_GLOBAL_CONSTRUCTOR_SUFFIX_PIC
#else
  #define CL_GLOBAL_CONSTRUCTOR_SUFFIX CL_GLOBAL_CONSTRUCTOR_SUFFIX_NOPIC
#endif

#if defined(__GNUC__) && defined(__OPTIMIZE__) && !(defined(__hppa__) && (__GNUC__ == 2) && (__GNUC_MINOR__ < 8)) && !defined(NO_PROVIDE_REQUIRE)
  #ifdef ASM_UNDERSCORE
    #define ASM_UNDERSCORE_PREFIX "_"
  #else
    #define ASM_UNDERSCORE_PREFIX ""
  #endif
  // Globalize a label defined in the same translation unit.
  // See macro ASM_GLOBALIZE_LABEL in the gcc sources.
  #if defined(__i386__) || defined(__m68k__) || defined(__mips__) || defined(__mipsel__) || defined(__mips64__) || defined(__alpha__) || defined(__rs6000__) || defined(__powerpc64__) || defined(__x86_64__) || defined(__s390__)
    // Some m68k systems use "xdef" or "global" or ".global"...
    #define CL_GLOBALIZE_LABEL(label)  __asm__("\t.globl " label);
  #endif
  #if defined(__sparc__) || defined(__sparc64__) || defined(__arm__) || defined(__ia64__)
    // Some arm systems use "EXPORT" or ".globl"...
    #define CL_GLOBALIZE_LABEL(label)  __asm__("\t.global " label);
  #endif
  #if defined(__hppa__)
    #define CL_GLOBALIZE_LABEL(label)  __asm__("\t.EXPORT " label ",ENTRY,PRIV_LEV=3");
  #endif
  #if defined(__m88k__)
    #define CL_GLOBALIZE_LABEL(label)  __asm__("\tglobal " label);
  #endif
  #if defined(__convex__)
    #define CL_GLOBALIZE_LABEL(label)  __asm__(".globl " label);
  #endif
  #ifndef CL_GLOBALIZE_LABEL
    #define CL_GLOBALIZE_LABEL(label)
  #endif
  #if defined(__rs6000__) || defined(_WIN32)
    #define CL_GLOBALIZE_JUMP_LABEL(label)  CL_GLOBALIZE_LABEL(ASM_UNDERSCORE_PREFIX #label)
  #else
    #define CL_GLOBALIZE_JUMP_LABEL(label)
  #endif
  #ifdef CL_NEED_GLOBALIZE_CTORDTOR
    #define CL_GLOBALIZE_CTORDTOR_LABEL(label)  CL_GLOBALIZE_LABEL(label)
  #else
    #define CL_GLOBALIZE_CTORDTOR_LABEL(label)
  #endif
  // Output a label inside a function.
  // See macro ASM_OUTPUT_LABEL in the gcc sources.
  #if defined(__ia64__)
    // g++-4.0 on IA64 likes to duplicate parts of basic blocks for no good
    // reason. To avoid an error when a label is defined twice, we can either
    // append "-Os" to the CXXFLAGS (then g++ does not create redundant
    // duplicates of basic blocks), or declare the label in a way that may
    // be redefined.
    // Why the "nop 0"? Apparently "." refers to the last instruction bundle.
    // Just ".set label,." would cause the branch to executed unwanted code.
    // And ".set label,.+16" might not work at the very beginning of a
    // function. So we spend a nop; it becomes the target of the jump.
    #define CL_OUTPUT_LABEL(label)  ASM_VOLATILE ("nop 0" "\n" ".set " label ", .")
  #elif defined(__m68k__)
    // C.f. IA64 case above.
    #define CL_OUTPUT_LABEL(label)  ASM_VOLATILE ("nop" "\n" ".set " label ", .")
  #else
    #define CL_OUTPUT_LABEL(label)  ASM_VOLATILE ("\n" label ":")
  #endif
  // ASM_VOLATILE(string) is for asms without arguments only!!
  #if ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 91)) || (__GNUC__ >= 3)
    // avoid warning caused by the volatile keyword
    #define ASM_VOLATILE  __asm__
  #else
    // need volatile to avoid reordering
    #define ASM_VOLATILE  __asm__ __volatile__
  #endif
  // CL_JUMP_TO(addr) jumps to an address, like  goto *(void*)(addr),
  // except that the latter inhibits inlining of the function containing it
  // in gcc-2.95. For new CPUs, look for "jump" and "indirect_jump" in gcc's
  // machine description.
  #if defined(__i386__)
    #if defined(__APPLE__) && defined(__MACH__)
      #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp " ASM_UNDERSCORE_PREFIX #addr)
    #else
      #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp %*%0" : : "rm" ((void*)(addr)))
    #endif
  #endif
  #if defined(__x86_64__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp " ASM_UNDERSCORE_PREFIX #addr)
  #endif
  #if defined(__m68k__)
    //#define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp %0@" : : "a" ((void*)(addr)))
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp (" ASM_UNDERSCORE_PREFIX #addr ",%pc)")
  #endif
  #if defined(__mips__) || defined(__mipsel__)
    //#define CL_JUMP_TO(addr)  ASM_VOLATILE("%*j %0" : : "d" ((void*)(addr)))
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("b " ASM_UNDERSCORE_PREFIX #addr)
  #endif
  #if defined(__sparc__) || defined(__sparc64__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp %0\n\tnop" : : "r" ((void*)(addr)))
  #endif
  #if defined(__alpha__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp $31,(%0),0" : : "r" ((void*)(addr)))
  #endif
  #if defined(__hppa__)
    //#define CL_JUMP_TO(addr)  ASM_VOLATILE("bv,n 0(%0)" : : "r" ((void*)(addr)))
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("b " ASM_UNDERSCORE_PREFIX #addr "\n\tnop")
  #endif
  #if defined(__arm__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("mov pc,%0" : : "r" ((void*)(addr)))
  #endif
  #if defined(__rs6000__) || defined(__powerpc__) || defined(__ppc__) || defined(__powerpc64__)
    //#define CL_JUMP_TO(addr)  ASM_VOLATILE("mtctr %0\n\tbctr" : : "r" ((void*)(addr)))
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("b " ASM_UNDERSCORE_PREFIX #addr)
  #endif
  #if defined(__m88k__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp %0" : : "r" ((void*)(addr)))
  #endif
  #if defined(__convex__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("jmp (%0)" : : "r" ((void*)(addr)))
  #endif
  #if defined(__ia64__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("br " ASM_UNDERSCORE_PREFIX #addr)
  #endif
  #if defined(__s390__)
    #define CL_JUMP_TO(addr)  ASM_VOLATILE("br %0" : : "a" ((void*)(addr)))
  #endif
  #ifdef CL_GLOBAL_DESTRUCTOR_PREFIX
    #define CL_PROVIDE(module)  \
      extern "C" void cl_module__##module##__firstglobalfun () {}	\
      extern "C" void cl_module__##module##__ctorend (void);		\
      extern "C" void cl_module__##module##__dtorend (void);		\
      CL_GLOBALIZE_JUMP_LABEL(cl_module__##module##__ctorend)		\
      CL_GLOBALIZE_JUMP_LABEL(cl_module__##module##__dtorend)		\
      CL_GLOBALIZE_CTORDTOR_LABEL(					\
                 ASM_UNDERSCORE_PREFIX CL_GLOBAL_CONSTRUCTOR_PREFIX	\
                 "cl_module__" #module "__firstglobalfun")		\
      CL_GLOBALIZE_CTORDTOR_LABEL(					\
                 ASM_UNDERSCORE_PREFIX CL_GLOBAL_DESTRUCTOR_PREFIX	\
                 "cl_module__" #module "__firstglobalfun")		\
      static int cl_module__##module##__counter;			\
      struct cl_module__##module##__controller {			\
        inline cl_module__##module##__controller ()			\
          { if (cl_module__##module##__counter++)			\
              { CL_JUMP_TO(cl_module__##module##__ctorend); }		\
          }								\
        inline ~cl_module__##module##__controller ()			\
          { CL_OUTPUT_LABEL (ASM_UNDERSCORE_PREFIX "cl_module__" #module "__dtorend"); } \
      };									\
      static cl_module__##module##__controller cl_module__##module##__ctordummy;
    #define CL_PROVIDE_END(module)  \
      struct cl_module__##module##__destroyer {				\
        inline cl_module__##module##__destroyer ()			\
          { CL_OUTPUT_LABEL (ASM_UNDERSCORE_PREFIX "cl_module__" #module "__ctorend"); } \
        inline ~cl_module__##module##__destroyer ()			\
          { if (--cl_module__##module##__counter)			\
              { CL_JUMP_TO(cl_module__##module##__dtorend); }		\
          }								\
      };								\
      static cl_module__##module##__destroyer cl_module__##module##__dtordummy;
    #define CL_REQUIRE(module)  \
      extern "C" void cl_module__##module##__ctor (void)		\
        __asm__ (ASM_UNDERSCORE_PREFIX CL_GLOBAL_CONSTRUCTOR_PREFIX	\
                 "cl_module__" #module "__firstglobalfun");		\
      extern "C" void cl_module__##module##__dtor (void)		\
        __asm__ (ASM_UNDERSCORE_PREFIX CL_GLOBAL_DESTRUCTOR_PREFIX	\
                 "cl_module__" #module "__firstglobalfun");		\
      struct _CL_REQUIRE_CLASSNAME(module,__LINE__) {			\
        inline _CL_REQUIRE_CLASSNAME(module,__LINE__) ()		\
          { cl_module__##module##__ctor (); }				\
        inline ~_CL_REQUIRE_CLASSNAME(module,__LINE__) ()		\
          { cl_module__##module##__dtor (); }				\
      };								\
      static _CL_REQUIRE_CLASSNAME(module,__LINE__)			\
        _CL_REQUIRE_CLASSNAME(module##_requirer,__LINE__);
  #else
    // gcc-3.0 -fuse-cxa-atexit doesn't have a single per-module destructor
    // function anymore. Instead, for each object's static constructor it
    // executes, it pushes the corresponding object's destructor onto a list.
    // Thus we need to hack the constructors only. gcc-4.3 uses different names
    // for global ctors in shared and static objects, so we cannot directly
    // call the ctors from CL_REQUIRE(M): the compiling function does not know
    // yet how it's going to be linked. Hence, we must hide the ctor call beind
    // an additional indirection.
    #define CL_PROVIDE(module)  \
      extern "C" void cl_module__##module##__firstglobalfun () {}	\
      extern "C" void cl_module__##module##__ctorend ();		\
      extern "C" void cl_module__##module##__docallctors ()		\
        __asm__ (ASM_UNDERSCORE_PREFIX CL_GLOBAL_CONSTRUCTOR_PREFIX	\
                     CL_GLOBAL_CONSTRUCTOR_SUFFIX(module));		\
      extern "C" void cl_module__##module##__globalctors ()		\
      { cl_module__##module##__docallctors(); }				\
      CL_GLOBALIZE_CTORDTOR_LABEL(					\
                 ASM_UNDERSCORE_PREFIX CL_GLOBAL_CONSTRUCTOR_PREFIX	\
                 CL_GLOBAL_CONSTRUCTOR_SUFFIX(module))			\
      static int cl_module__##module##__counter;			\
      struct cl_module__##module##__controller {			\
        inline cl_module__##module##__controller ()			\
          { if (cl_module__##module##__counter++)			\
              { CL_JUMP_TO(cl_module__##module##__ctorend); }		\
          }								\
      };								\
      static cl_module__##module##__controller cl_module__##module##__ctordummy;
    #define CL_PROVIDE_END(module)  \
      struct cl_module__##module##__destroyer {				\
        inline cl_module__##module##__destroyer ()			\
          { CL_OUTPUT_LABEL (ASM_UNDERSCORE_PREFIX "cl_module__" #module "__ctorend"); } \
      };								\
      static cl_module__##module##__destroyer cl_module__##module##__dtordummy;
    #define CL_REQUIRE(module)  \
      extern "C" void cl_module__##module##__ctor ()			\
        __asm__ (ASM_UNDERSCORE_PREFIX "cl_module__" #module "__globalctors"); \
      struct _CL_REQUIRE_CLASSNAME(module,__LINE__) {			\
        inline _CL_REQUIRE_CLASSNAME(module,__LINE__) ()		\
          { cl_module__##module##__ctor (); }				\
      };								\
      static _CL_REQUIRE_CLASSNAME(module,__LINE__)			\
        _CL_REQUIRE_CLASSNAME(module##_requirer,__LINE__);
  #endif
  #define _CL_REQUIRE_CLASSNAME(module,line) __CL_REQUIRE_CLASSNAME(module,line)
  #define __CL_REQUIRE_CLASSNAME(module,line) cl_module__##module##__##line
#else
  #define CL_PROVIDE(module)
  #define CL_PROVIDE_END(module)
  #define CL_REQUIRE(module)
#endif

// Concatenation of macroexpanded tokens.
// Equivalent to CL_CONCAT in src/base/cl_macros.h which we do not want
// to expose, however.
#define CL_CONCATENATE_(xxx,yyy)  xxx##yyy
#define CL_CONCATENATE(xxx,yyy)  CL_CONCATENATE_(xxx,yyy)

// Sometimes a link time dependency is needed, but without requirements
// on initialization order.
//
// CL_FORCE_LINK(dummy,external_variable)
// forces a link time reference to the external_variable.
#include <cstdlib>
#if 0
// This definition does not work.  It gets optimized away by g++ 3.1.
#define CL_FORCE_LINK(dummy,external_variable) \
  static const void* const dummy[] = { &dummy, &external_variable };
#else
#define CL_FORCE_LINK(dummy,external_variable) \
  static const								\
  struct dummy {							\
    inline dummy () {							\
      if ((void*) &external_variable == (void*) this)			\
        abort();							\
    }									\
  }									\
  CL_CONCATENATE(dummy,_instance);
#endif

#endif /* _CL_MODULES_H */
