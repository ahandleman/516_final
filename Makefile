.PHONY: all
CC = gcc
CPP = g++
CFLAGS = -L/home/warehouse/ahandleman/cse516/glpk-4.35/lib/lib -I/home/warehouse/ahandleman/cse516/glpk-4.35/lib/include -lglpk -Wall -Werror -fpic -g -std=c++17 

assignment : assignment.cpp assignment.h problem_structs.cpp problem_structs.h linear.cpp linear.h
	$(CPP) $(CFLAGS) problem_structs.cpp  assignment.cpp linear.cpp -lglpk -o assignment

.PHONY: clean
clean :
	rm -f assignment *.o *.core