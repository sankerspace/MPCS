
CC := g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-O2
CPPFLAGS := #-DHARDWARE=0
LDFLAGS := #-lboost_iostream
CUSTOM:=
CSRC := $(wildcard *.cpp)
OBJS := $(CSRC:%.c=hostobjs/%.o)
HDRS := $(wildcard *.hpp)

.PHONY: all
all: generateMPCs

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUSTOM) -c -o $@ $<
	
generateMPCs: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $+

debug: $(OBJS)
	$(CC) $(HWFLAGS) $(CFLAGS) -g -o $@ $+

.PHONY: clean
clean:
	rm -rf generateMPCs *.txt debug *.o

