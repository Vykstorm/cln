//
// LiDIA - a library for computational number theory
//   Copyright (c) 1996 by the LiDIA Group
//
// File        : bigint_def.h 
// Author      : Bruno Haible (HB)
// Last change : HB, 1996-11-17, initial version
//               HB, 1998-01-24, change  #include <cl_*>  to  #include "cl_*"
//                   because the files are in $(LIDIA_HOME)/include/LiDIA,
//                   and the only -I option is -I$(LIDIA_HOME)/include .
//

#ifndef LIDIA_BIGINT_DEF_H
#define LIDIA_BIGINT_DEF_H

/**
** The next include MUST remain in this file in THIS position.
**/

#include <LiDIA/lidia.h>

/**
** include here the include file of the C multiple precision integers
** and define integer_type_name to be the integer type we have. Define 
** base_digit to
**
** For example write something like
**
** #include "integer_include_file.h"
** #define integer_type_name  	your_integer_type_name 
**
**/

#include <LiDIA/kernel/cl_number.h>
#include <LiDIA/kernel/cl_integer.h>

#define integer_type_name       cl_I
#define base_digit       uintD

#endif
