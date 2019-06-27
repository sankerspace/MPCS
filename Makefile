
CC := g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-O2
CPPFLAGS := #-DHARDWARE=0
LDFLAGS := #-lboost_iostream
CUSTOM:=
CSRC := $(wildcard *.cpp)
CSRC := $(filter-out TestGraph_Main.cpp, $(CSRC))
OBJS := $(CSRC:%.c=hostobjs/%.o)
OBJS_2:= Graph.o  TestGraph_Main.o
HDRS := $(wildcard *.hpp)

.PHONY: all
all: checkMPCs

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUSTOM) -c -o $@ $<
	
TestGraph: $(OBJS_2)
	$(CC) $(CFLAGS) -o $@ $+
	
checkMPCs: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+

debug: $(OBJS)
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

.PHONY: clean
clean:
	rm -rf checkMPCs debug TestGraph *.o

