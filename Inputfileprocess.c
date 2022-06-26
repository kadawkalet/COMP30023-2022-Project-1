// Author: Kongmeng Lim (982928)
#include "Inputfileprocess.h"

Process *loadInputFile(char *filename, int *numProcesses){

  // Open file
  FILE* file = fopen(filename, "r");

  if (file == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // Read into memory
  int pid, fidLck, fidReq;
  Process *process = NULL;
  while(fscanf(file, "%d %d %d", &pid, &fidLck, &fidReq) == 3){
    numProcesses += 1;
    insert(&process,pid,fidLck,fidReq);
  }

  return process;
}
