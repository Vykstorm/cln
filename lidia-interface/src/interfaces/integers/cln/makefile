######################################################################
#
#  Name ................... LiDIA/src/interfaces/integers/cln/makefile
#
#  Architecture : unix
#  Compiler     : gcc, g++ 
#  Flags        : -g -O2
#  Program Flags: 
#  Author       : Thomas Papanikolaou & Bruno Haible
#  Release      : 1.0 
#  Last Change  : 1998-01-24
#  Copyright    : by the University of Saarland and Bruno Haible, 1996
#

#
# include the configuration file
#

include ../../../../config/CONFIG

#
# Object
#

OBJ=bigint.o

#
# Rules
#

all:	copyh $(libp)LiDIA.a

appl:	bigint_appl$(EXE)

#
# Dependencies
# 

copyh:
	$(CP) bigint_def.h $(LIDIA_HOME)$(DIRSEP)include$(DIRSEP)LiDIA

bigint.o:	bigint.c $(LIDIA_INC)$(DIRSEP)LiDIA$(DIRSEP)bigint.h
	$(CXX) -c $(CXXFLAGS) -I$(LIDIA_INC) -I$(LIDIA_HOME)$(DIRSEP)src$(DIRSEP)kernel$(DIRSEP)integers$(DIRSEP)cln$(DIRSEP)cln$(DIRSEP)include -I$(LIDIA_HOME)$(DIRSEP)src$(DIRSEP)kernel$(DIRSEP)integers$(DIRSEP)cln $*.c -o $(objp)$*.o
	$(NOOMV) $*.o $(objp)$*.o
	$(TOUCH) $*.o

$(libp)LiDIA.a:         $(OBJ)
	-$(AR) $(LIDIA_LIB)$(DIRSEP)$(libp)LiDIA.a $(objp)*.o

ranlib:
	$(RANLIB) $(LIDIA_LIB)$(DIRSEP)$(libp)LiDIA.a

bigint_appl$(EXE):	bigint_appl.c
	$(CXX) $(CXXFLAGS) bigint_appl.c $(CXX-off) -I$(LIDIA_INC) -L$(LIDIA_LIB) -o bigint_appl$(EXE) $(LIB)
	-$(MV) bigint_appl$(EXE) $(LIDIA_BIN)

#
# Clean
#

clean:
	-$(RM) *.o 

veryclean:	clean 
	-$(RM) bigint_appl$(EXE)

#
# End Of Makefile
#
