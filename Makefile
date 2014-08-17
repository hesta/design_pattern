CXX      := g++
CXXFLAGS := -g #-Wall -Wextra -Werror -pedantic-errors
CPPFLAGS := -std=c++0x

target   := main
# Uncomment this line if you are an undergraduate student
#sources  := UnitTest4D.cpp AQueue.cpp Array.cpp Queue.cpp getopt.cpp Options.cpp Visitor.cpp Print_Visitor.cpp Tree_Iterator_Impl.cpp Factories.cpp
# Uncomment this line if you are a graduate student
sources  := UnitTest4D.cpp Interpreter.cpp LQueue.cpp AQueue.cpp Array.cpp Queue.cpp getopt.cpp Options.cpp Visitor.cpp Print_Visitor.cpp Eval_Visitor.cpp
objects  := $(sources:.cpp=.o)
depends  := $(sources:.cpp=.dep)

$(target): $(objects) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

include $(depends)
include Makefile-gtest

.PHONY: view docs clean-docs clean-deps clean realclean

view:
	gedit Array.h Array.cpp ../*.txt &

docs: clean-docs
	doxygen doxygen.conf
	firefox docs/classArray.html

clean-docs:
	$(RM) -r docs

clean-deps:
	$(RM) $(depends)

clean: clean-deps clean-docs
	$(RM) $(objects) *~ *.tmp

realclean: clean clean-gtest
	$(RM) $(target)

%.dep: %.cpp
	@set -e; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.tmp; \
	(echo -n "$@ " | cat - $@.tmp) > $@; \
	$(RM) $@.tmp; \
	echo -n "Generating deps [$<]:\n ";\
	cat $@


%.h %.cpp: ;
