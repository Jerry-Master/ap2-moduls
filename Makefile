# Defines the flags for compiling with C++.
CXXFLAGS = -Wall -std=c++11 -O2
INCLUDE = -DNO_FREETYPE -I $(HOME)/libs/include  
LIBS =  -L $(HOME)/libs/lib -l PNGwriter -l png

# Rule to compile everything (make all).
# Because it is the first rule, it is also the default rule (make).
all: main.exe image.x

check: main.exe
	./main.exe < test.in > program.out
	diff program.out test.out

# Rule to clean object and executable files (make clean).
clean:
	rm -rf main.exe *.o program.out
	
cleanPNG:
	rm -rf *.png image.x

# Rule to link the executable from then object files.
#
# The following default variables are used:
# 		$^ is the names of all the prerequisites
# 		$@ is the name of the target of the rule
# 		$(CXX) is the name of the C++ compiler
main.exe: main.o Point.o Rectangle.o Circle.o
	$(CXX) $^ -o $@

image.x: image.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ $(LIBS) -o $@ 
	./image.x
	display image.png &
	
image.cc: image.cc

## Dependencies between files
# (we don't need to precise how to produce them, Makefile already knows)

main.o: main.cc Point.hh Rectangle.hh Circle.hh

Point.o: Point.cc Point.hh

Rectangle.o: Rectangle.cc Rectangle.hh Point.hh

Circle.o: Circle.cc Circle.hh Point.hh

