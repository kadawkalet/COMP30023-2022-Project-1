// Author: Kongmeng Lim
// ID: 982928

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "Linkedlistprocess.h"
#include "Executiontimesolver.h"
#include "Deadlocksimulationsolver.h"
#include "Deadlockbreakingsolver.h"
#define USAGE "./detect -f [filename] -c [optional/Mutually Exclusive with -e] -e [optional/Mutually Exclusive with -c]"

int get_arguments(int argc, char **argv, int *eflag, int *cflag, char **filename);

int main(int argc, char **argv) {

  /* This is to store the command line arguments. */
  int cflag, eflag;
  char *filename;

  filename = NULL;
  eflag = 0;
  cflag = 0;

  // Read CommandLine Arguments
  if (!get_arguments(argc, argv, &eflag, &cflag, &filename)){
    return 1;
  }

  /* This is opening the file and storing the file pointer in the variable `file`. */
  FILE* file = fopen(filename, "r");

  /* This is checking if the file is opened successfully. If not, it will print out the error message and
  exit the program. */
  if (file == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  /* This is reading the input file and storing the data into a linked list. */
  int pid, fidLck, fidReq;
  int numProcesses = 0;
  Process *headProcess = NULL;
  while(fscanf(file, "%d %d %d", &pid, &fidLck, &fidReq) == 3){
    numProcesses += 1;
    insert(&headProcess,pid,fidLck,fidReq);
  }
  // closing file
  fclose(file);

  // Compute Number of Files
  int numFiles = getNumFiles(headProcess, numProcesses);

  if (eflag == 1 && cflag == 1){
    // Disallowed: Return a usage instruction and exit program if cflag and eflag are flaged
    printf(USAGE);
    exit(EXIT_FAILURE);
  } else if (cflag == 1) {
    // CommandLine Flage for solving deadlock and computing shortest simulation times
    deadlockSimulationSolver(headProcess, numProcesses);
  } else if (eflag == 1) {
    // CommandLine Flage for finding execution times
    executionTimeSolver(headProcess, numProcesses, numFiles);
  } else {
    // CommandLine Flage for finding and breaking deadlocks
    deadlockbreaker(headProcess, numProcesses, numFiles);
  }

  // free memory on the linkedlist
  while (headProcess != NULL)
  {
    Process *next = headProcess->ptr;
    free(headProcess);
    headProcess = next;
  }
  
  return 0;
}

/**
 * This function takes in the command line arguments and parses them
 * 
 * @param argc The number of arguments in the command line.
 * @param argv The argument vector.
 * @param eflag if -e given, the program will flage eflag to true.
 * @param cflag if -c given, the program will flage cflag to true.
 * @param filename the name of the file to be read
 * 
 * @return The return value is 1 if the command line arguments are valid, and 0 otherwise.
 */
int get_arguments(int argc, char **argv, int *eflag, int *cflag, char **filename){
	int c;
	while ((c = getopt (argc, argv, "ecf:")) != -1){
    switch (c) {
      case 'e':
        *eflag = 1;
        break;
      case 'c':
        *cflag = 1;
        break;
      case 'f':
        *filename = optarg;
        break;
      default:
				printf(USAGE);
        return 0;
      }
	}
  if (*filename == NULL){
    printf(USAGE);
    return 0;
  }
	return 1;
}
