CC = gcc
AR = ar
FLAGS = -Wall -g
OBJ = frequency.o

all: frequency

frequency: frequency.o
	$(CC) $(FLAGS) -o frequency $(OBJ)

frequency.o: frequency.c
	$(CC) $(FLAGS) -c frequency.c

.PHONY: clean all
clean:
	rm -f *.o frequency