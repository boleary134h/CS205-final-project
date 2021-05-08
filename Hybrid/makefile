CC = mpic++
CFLAGS = -std=c++11
OPENMP = -fopenmp

main: main.o textrankOperations.o
	$(CC) $(CFLAGS) $(OPENMP) -o textrank main.o textrankOperations.o
	
main.o: main.cpp textrank.hpp
	$(CC) $(CFLAGS) $(OPENMP) -c main.cpp
	
textrankOperations.o: textrank.hpp

clean: 
	$(RM) textrank
