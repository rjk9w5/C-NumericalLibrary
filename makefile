###############################################################################
# -->Makefile<--
###############################################################################

###############################################################################
#
# Programmer :  Rob Wiehage
# Modified by:  Billy Rhoades
# Modified by:  Ryan Krattiger (1 February 2016)
# Assignment :  Program 4
#
# Instructor :  Dr. Michael Hilgers
# Course     :  CS236 Winter 2001
# Semester   :  Fall 2001
#
###############################################################################

###############################################################################
# This makefile will build an executable for the assignment.
###############################################################################

.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -W -pedantic-errors -std=c++11
INCLUDE = -I./headers/ -I./headers/containers/
# The following 2 lines only work with gnu make.
# It's much nicer than having to list them out,
# and less error prone.
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard headers/*.hpp) ${wildcard headers/containers/*.hpp}
# Using subfolder organization
# SOURCES = ${wildcard src/*.cpp}
# HEADERS = ${wildcard include/*.hpp}

# With Sun's make it has to be done like this, instead of
# using wildcards.
# Well, I haven't figured out another way yet.
#SOURCES = signal.cpp tokentype.cpp token.cpp tokenlist.cpp driver.cpp
#HEADERS = signal.h tokentype.h token.h tokenlist.h

# Looks like it can be done like this, but won't work for gmake.
#SOURCES:sh = ls *.cpp
#HEADERS:sh = ls *.h

LIBRARY=lib/libcppnl.a

OBJECTS = $(SOURCES:src/%.cpp=bin/%.o)
TESTSRC=test2.cpp
TESTOBJ=test.o

default: ${LIBRARY}

bin/%.o: src/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

all: ${LIBRARY} driver

${LIBRARY}: $(OBJECTS)
	@echo "Building $@"
#	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $@
	@ar crf $@ ${OBJECTS}
	@echo ""
	@echo "Library Build Complete"
	@echo ""

driver: $(OBJECTS) ${TESTOBJ}
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) ${TESTOBJ} -o $@
	@echo ""
	@echo "Compilation Complete"
	@echo ""

${TESTOBJ}: ${TESTSRC}
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f depend
	-@rm -f $(OBJECTS)
	-@rm -f $(TESTOBJ)
# Automatically generate dependencies and include them in Makefile
depend: $(SOURCES) ${TESTSRC} $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) $(INCLUDE) -MM src/*.cpp > $@


-include depend
# Put a dash in front of include when using gnu make.
# It stops gmake from warning us that the file
# doesn't exist yet, even though it will be properly
# made and included when all is said and done.
