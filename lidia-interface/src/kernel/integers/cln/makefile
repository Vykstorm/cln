######################################################################
#
#  Name ............................... LiDIA/src/kernel/cln/makefile
#
#  Architecture : unix
#  Compiler     : gcc, g++ 
#  Flags        : -g -O2 -fno-exceptions
#  Program Flags: 
#  Author       : Markus Maurer, Bruno Haible
#  Release      : 1.0 
#  Last Change  : 1998-12-13
#  Copyright    : by the University of Saarland and Bruno Haible, 1998 
#

#
# include the configuration file
#

include ../../../../config/CONFIG

#
# Dependencies
#


default:	library

c:		library

sparc:		library

sparc7:		library

sparc8:		library

mips:		library

i386:		library

i486:		library

i586:		library

i686:		library

hppa1.1:	library




#
# library and application files
#

library: cln$(DIRSEP)include$(DIRSEP)cl_config.h cln$(DIRSEP)include$(DIRSEP)cl_intparam.h
	cd cln$(DIRSEP)gmp $(SEP) $(MAKE) mpn/libmpn.la mp_clz_tab.lo
	cd cln$(DIRSEP)src $(SEP) $(MAKE)
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_abort.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_complex_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_config.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_dfloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_dfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_ffloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_ffloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_float.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_float_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_floatformat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_floatparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_input.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_intparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_lfloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_lfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_malloc.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_modules.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_number.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_number_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_object.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_output.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_random.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_rational_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_real_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_sfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_string.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_types.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)src$(DIRSEP)base$(DIRSEP)cl_spushstring.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)src$(DIRSEP)base$(DIRSEP)cl_sstring.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)gmp.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)gmp-impl.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)longlong.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)mpn$(DIRSEP)gmp-mparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	$(SHELL) cln$(DIRSEP)libtool --mode=install cp cln$(DIRSEP)src$(DIRSEP)libcln.la `pwd`$(DIRSEP)libcln.la
	$(ARX) libcln.a
	$(AR) $(LIDIA_LIB)$(DIRSEP)$(libp)LiDIA.a *.o
	$(RM) *.o
	$(RM) libcln.a
	$(TOUCH) library


ranlib:
	$(RANLIB) $(LIDIA_LIB)$(DIRSEP)$(libp)LiDIA.a

appl:
#	cd cln $(SEP) $(MAKE) check



#
# Configuration command
#


configure:
	cd cln $(SEP) CC="$(CC)" CFLAGS="$(CFLAGS) -fno-exceptions" CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS) -fno-exceptions" .$(DIRSEP)configure --target=$(LIDIA_ARCH)



#
# Installation commands
#

install: installh

installh: 
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_abort.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_complex_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_config.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_dfloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_dfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_ffloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_ffloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_float.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_float_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_floatformat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_floatparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_input.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_integer_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_intparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_lfloat.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_lfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_malloc.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_modules.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_number.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_number_io.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_object.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_output.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_random.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_rational_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_real_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_sfloat_class.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_string.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)include$(DIRSEP)cl_types.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)src$(DIRSEP)base$(DIRSEP)cl_spushstring.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)src$(DIRSEP)base$(DIRSEP)cl_sstring.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)gmp.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)gmp-impl.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)longlong.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel
	-$(CP) cln$(DIRSEP)gmp$(DIRSEP)mpn$(DIRSEP)gmp-mparam.h $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)kernel


#
# Clean
#

clean:
	-cd cln $(SEP) make clean
	-$(RM) library


veryclean:	clean


