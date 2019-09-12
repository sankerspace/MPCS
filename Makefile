
CC := g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-O2
CPPFLAGS := #-DHARDWARE=0
LDFLAGS := #-lboost_iostream
CUSTOM:=
SUBDIR:=./Graph
CSRC := $(wildcard *.cpp)
CSRC := $(filter-out TestGraph_Main.cpp, $(CSRC))
OBJS := $(CSRC:%.c=hostobjs/%.o)
OBJS_2:= Graph.o  TestGraph_Main.o
OBJS_3:=BoostGraph.o  TestBoostGraph_Main.o
HDRS := $(wildcard *.hpp)

.PHONY: all
all: Graph checkMPCs 

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUSTOM) -c -o $@ $<
	
Graph:
	cd Graph && $(MAKE)

checkMPCs: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $+

debug_checkMPCs: $(OBJS) Graph
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

.PHONY: clean
clean:
	rm -rf checkMPCs debug TestGraph *.o  TestBoostGraph



