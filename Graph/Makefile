CC := g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-O2
CPPFLAGS := #-DHARDWARE=0
#LDFLAGS := -lboost_iostream -lboost_filesystem
BOOST:= -lboost_filesystem
CUSTOM:=
CSRC:= $(wildcard *.cpp)
CSRC2:=Graph.cpp TestGraph_Main.cpp
CSRC3:=BoostGraph.cpp TestBoostGraph_Main.cpp
CSRC4:=Graph.cpp TestGraph_Auto.cpp
#CSRC := $(filter-out TestGraph_Main.cpp, $(CSRC))
OBJS := $(CSRC:%.c=hostobjs/%.o)
OBJS_2:= Graph.o  TestGraph_Main.o
OBJS_3:=BoostGraph.o  TestBoostGraph_Main.o
OBJS_4:=Graph.o  TestGraph_Auto.o
HDRS := $(wildcard *.hpp)

.PHONY: all
all: Graph.o  BoostGraph.o 

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUSTOM) -c -o $@ $<

Graph.o: Graph.cpp Graph.hpp
	$(CC) -c Graph.cpp 

BoostGraph.o: BoostGraph.cpp BoostGraph.hpp
	$(CC) -c BoostGraph.cpp 
	
TestGraph: $(OBJS_2)
	$(CC) $(CFLAGS) -o $@ $+
	
debug_TestGraph: $(CSRC2)
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

TestBoostGraph: $(OBJS_3)
	$(CC) $(CFLAGS) -o $@ $+
	
debug_TestBoostGraph:$(CSRC3)
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

TestAutoGraph: $(OBJS_4)
	$(CC) $(CFLAGS) -o $@ $+ $(BOOST)
	
debug_TestAutoGraph:$(CSRC4)
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+ $(BOOST)

.PHONY: clean
clean:
	rm -rf  TestGraph *.o  TestBoostGraph TestAutoGraph  debug_TestGraph  debug_TestBoostGraph debug_TestAutoGraph




