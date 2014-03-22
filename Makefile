#############################################################################
#
#  makefile for tree traversal
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#
#############################################################################

MAKEFILE	= Makefile
CC		= g++
CFILES		= main.cpp getopt.cpp Tree_Factory_Impl.cpp Traversal_Strategy_Impl.cpp Options.cpp Tree_Factory.cpp Traversal_Strategy.cpp
HFILES		= LQueue.h AQueue.h Array.h Queue.h getopt.h Queue.h Tree_Factory_Impl.h Traversal_Strategy_Impl.h Options.h Typedefs.h Tree_Factory.h Traversal_Strategy.h Tree.h Node.h Refcounter.h
OFILES		= main.o getopt.o Tree_Factory_Impl.o Traversal_Strategy_Impl.o Options.o Tree_Factory.o Traversal_Strategy.o

#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -ggdb
IFLAGS          = 
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		= -g
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS) $(CPPFLAGS)
CPPFLAGS := -std=c++0x

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .C .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: tree-traversal

tree-traversal: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf tree-traversal

depend:
	g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main.o: main.cpp Tree.h Node.h Node.cpp Typedefs.h Tree.cpp \
  Tree_Factory.h Traversal_Strategy.h Options.h Refcounter.h
getopt.o: getopt.cpp
Options.o: Options.cpp Options.h getopt.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
