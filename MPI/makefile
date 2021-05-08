CC = mpic++
CFLAGS = -std=c++11

main: main.o textrankOperations.o
	$(CC) $(CFLAGS) -o textrank main.o textrankOperations.o
	
main.o: main.cpp textrank.hpp
	$(CC) $(CFLAGS) -c main.cpp
	
textrankOperations.o: textrank.hpp

clean: 
	$(RM) textrank
