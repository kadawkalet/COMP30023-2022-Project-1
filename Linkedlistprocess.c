// Author: Kongmeng Lim
// ID: 982928

#include "Linkedlistprocess.h"

// insertion function: adding process to a linked list of processes
void insert(Process** headProcess, int pid, int fidLck, int fidReq) {
  Process* newProcess = (Process*)malloc(sizeof(Process));
  newProcess->pid = pid;
  newProcess->fidLck = fidLck;
  newProcess->fidReq = fidReq;
  newProcess->ptr = (*headProcess);
  (*headProcess) = newProcess;
}

/**
 * This function returns the number of files that are in a process linked list
 * 
 * @param process the process that is requesting the lock
 * @param numProcesses the number of processes
 * 
 * @return The number of files that are currently being processed.
 */
int getNumFiles(Process* process, int numProcesses) {
  int unprocessedfilesNum = numProcesses*2;
  int unprocessedfiles[unprocessedfilesNum];
  int i = 0;

  if (process == NULL){
    return numProcesses;
  } else {
    while (process != NULL) {
      unprocessedfiles[i] = process->fidLck;
      unprocessedfiles[i+1] = process->fidReq;
      i += 2;
      process = process->ptr;
    }
  }
  int numFiles = remove_duplicate(unprocessedfiles, unprocessedfilesNum);
  return numFiles;
}

/**
 * Prints the list of processes from linked list
 * 
 * @param process the process that is requesting the lock
 */
void printList(Process* process){
    while (process != NULL) {
        printf(" %d %d %d\n", process->pid, process->fidLck, process->fidReq);
        process = process->ptr;
    }
}

/* This function removes duplicate values in an array. */
int remove_duplicate(int array[], int n){
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if(array[i] == array[j]) {
        for(int k = j; k < n - 1; k++) {
          array[k] = array[k + 1];
        }
        n -= 1;
        j -= 1;
      }
    }
  }
  return n;
}
