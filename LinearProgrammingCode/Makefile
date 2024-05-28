# Copyright 2020, Gurobi Optimization, LLC

PLATFORM = linux64
GUROBIPATH = /apps/cent7/gurobi/9.0.1
KEEPTU   = ../..
INC      = $(GUROBIPATH)/include/
CPP      = g++
CARGS    = -std=c++11 -m64 -g 
CLIB     = -L$(GUROBIPATH)/lib -lgurobi90
CPPLIB   = -L$(GUROBIPATH)/lib -lgurobi_c++ -lgurobi90
OBJS     = main.o myfunctions.o



all: main

run: run_main

main: $(OBJS)
	$(CPP) $(CARGS) -o $@ $^ -I$(INC) $(CPPLIB) -lm

%.o: %.cpp
	$(CPP) $(CARGS) -c -o $@ $< -I$(INC) $(CPPLIB) -lm

run_main: main
	./main

clean:
	rm -rf $(OBJS) main
