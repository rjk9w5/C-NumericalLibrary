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
INCLUDE = -I./src/ \
          -I./src/containers/Matrices/Matrix/ \
          -I./src/containers/Matrices/SquareMatrix/ \
          -I./src/containers/Matrices/RectangleMatrix/ \
          -I./src/containers/Matrices/UpperMatrix/ \
          -I./src/containers/Matrices/LowerMatrix/ \
          -I./src/LinearSystems/ \
          -I./src/Non_LinearSystems/ \
          -I./src/Decompositions/ \
          -I./src/Functions/ \
          -I./src/RootFinding/ \
          -I./src/Optimization/ \
          -I./src/Norms/

# The following 2 lines only work with gnu make.
# It's much nicer than having to list them out,
# and less error prone.
SOURCES = 
#$(wildcard src/src/*.cpp)
HEADERS = $(wildcard ./src/*.h) \
          $(wildcard ./src/containers/Matrices/Matrix/*.h) \
          $(wildcard ./src/containers/Matrices/SquareMatrix/*.h) \
          $(wildcard ./src/containers/Matrices/RectangularMatrix/*.h) \
          $(wildcard ./src/containers/Matrices/UpperMatrix/*.h) \
          $(wildcard ./src/containers/Matrices/LowerMatrix/*.h) \
          $(wildcard ./src/LinearSystems/*.h) \
          $(wildcard ./src/Non_LinearSystems/*.h) \
          $(wildcard ./src/Decompositions/*.h) \
          $(wildcard ./src/Functions/*.h) \
          $(wildcard ./src/RootFinding/*.h) \
          $(wildcard ./src/Optimization/*.h)\
          $(wildcard ./src/Norms/*.h)
#          ${wildcard headers/containers/Matrices/DiagonalMatrix/*.h}\
#          ${wildcard headers/containers/Matrices/TriDiagonalMatrix/*.h}\
#          ${wildcard headers/containers/Matrices/SparseMatrix/*.h}
          
# Using subfolder organization
# SOURCES = ${wildcard src/*.cpp}
# HEADERS = ${wildcard include/*.hpp}

# Looks like it can be done like this, but won't work for gmake.
#SOURCES:sh = ls *.cpp
#HEADERS:sh = ls *.h

LIBRARY=lib/libcppnl.a
 
#$(SOURCES:src/src/%.cpp=bin/%.o)
TESTSRC=mat_test.cpp
SRC=$(TESTSRC)
#test2.cpp
TESTOBJ=test.o
OBJECTS=$(SRC:%.cpp=bin/%.o)


# Recipes
default: driver 

bin/%.o: %.cpp $(HEADERS)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

all: driver

#${LIBRARY}: $(OBJECTS) $(HEADERS)
#	@echo "Building $@"
#	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $@
#	@ar crf $@ ${OBJECTS}
#	@echo ""
#	@echo "Library Build Complete"
#	@echo ""

driver: $(OBJECTS) $(HEADERS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $@
	@echo ""
	@echo "Compilation Complete"
	@echo ""

#${TESTOBJ}: ${TESTSRC} $(HEADERS)
#	@echo "Compiling $<"
#	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f depend
	-@rm -f $(OBJECTS)
#	-@rm -f $(TESTOBJ)
# Automatically generate dependencies and include them in Makefile
depend: $(SRC) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) $(INCLUDE) -MM $(SRC) > $@


-include depend
# Put a dash in front of include when using gnu make.
# It stops gmake from warning us that the file
# doesn't exist yet, even though it will be properly
# made and included when all is said and done.
