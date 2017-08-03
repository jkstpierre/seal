#SEAL Makefile
#Author: Joseph St. Pierre
#Year: 2017

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

EXEC = seal

COMPILER_FLAGS =
LINKER_FLAGS = -lm -lsodium

CC = gcc

seal:
	$(CC) $(COMPILER_FLAGS) -c $(SRC)
	$(CC) $(COMPILER_FLAGS) -o $(EXEC) $(OBJ) $(LINKER_FLAGS)
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(EXEC)

