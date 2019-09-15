CC := g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-O2
CPPFLAGS := #-DHARDWARE=0
LDFLAGS := #-lboost_iostream
CUSTOM:=
SUBDIR:=./Graph
SUBFILE:=Graph.cpp Graph.hpp BoostGraph.cpp BoostGraph.hpp
CSRC := $(wildcard *.cpp)
$CSRC2 := $(SUBDIR)/$(wildcard *.cpp)
$CSRC2 := $(filter-out TestGraph_Main.cpp, $(CSRC2))
$CSRC2 := $(filter-out TestBoostGraph_Main.cpp, $(CSRC2))
$CSRC2 := $(filter-out BoostGraph.cpp, $(CSRC2))

HDRS := $(wildcard *.hpp)

#CSRC := $(filter-out TestGraph_Main.cpp, $(CSRC))
OBJS := $(CSRC:%.c=hostobjs/%.o)
OBJS_2:= Graph/Graph.o  #Graph/BoostGraph.o 
HDRS2 := $(SUBDIR)/$(wildcard *.hpp)
HDRS2 := $(SUBDIR)/$(filter out BoostGraph.cpp,$(HDRS2)) 

.PHONY: all
all: Graph checkMPCs 

%.o: %.c $(HDRS) $(CSRC2) $(HDRS2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUSTOM) -c -o $@ $<
	
Graph: $(CSRC2) 
	cd Graph && $(MAKE)

checkMPCs: $(OBJS)  $(OBJS_2) 
	$(CC) $(CFLAGS) -o $@ $+

debug_checkMPCs: $(OBJS) $(OBJS_2) 
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

.PHONY: clean
clean:
	rm -rf checkMPCs debug_checkMPCs *.o $(SUBDIR)/*.o 



