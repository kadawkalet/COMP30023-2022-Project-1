# Author: Kongmeng Lim
# ID: 982928

CC = gcc
CFLAGS = -Wall

SRC = detect.c Linkedlistprocess.c Executiontimesolver.c Deadlocksimulationsolver.c Deadlockbreakingsolver.c
OBJ = detect.o Linkedlistprocess.o Executiontimesolver.o Deadlocksimulationsolver.o Deadlockbreakingsolver.o
EXE = detect

$(EXE): $(OBJ)
				 $(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm

clean:
				 rm -f *.o $(EXE)

format:
			clang-format -i *.c *.h

# Dependencies
detect.o: Makefile detect.c Linkedlistprocess.h Executiontimesolver.h Deadlocksimulationsolver.h Deadlockbreakingsolver.h
LinkedListprocess.o: Makefile Linkedlistprocess.c Linkedlistprocess.h
