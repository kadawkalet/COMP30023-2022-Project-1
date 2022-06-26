// Author: Kongmeng Lim
// ID: 982928

#include "Executiontimesolver.h"

/**
 * Given a number of processes, find the number of execution times
 * 
 * @param process the array of processes
 * @param numProcesses The number of processes that need to be scheduled.
 * @param numFiles the number of files that need to be processed
 */
void executionTimeSolver(Process* process, int numProcesses, int numFiles){
  int numExetimes = findExecutionTimes(process, numProcesses);
  printf("Processes %d\n", numProcesses);
  printf("Files %d\n", numFiles);
  printf("Execution time %d\n", numExetimes);
}

/**
 * Given a number of processes with a number of files, find the execution times
 * 
 * @param process the process to be executed
 * @param numProcesses The number of processes.
 * 
 * @return The number of excution times on all processes.
 */
int findExecutionTimes(Process* process, int numProcesses){
  int Reqfiles[numProcesses];
  int executionTimes = 0;
  int i = 0;

  if (process == NULL){
    return executionTimes;
  } else {
    while (process != NULL) {
      Reqfiles[i] = process->fidReq;
      i += 1;
      process = process->ptr;
    }
  }

  int modeFreq = findModeFreq(Reqfiles, numProcesses);

  if (modeFreq == 1){
    executionTimes += 2;
  } else {
    executionTimes += 1 + modeFreq;
  }

  return executionTimes;
}

/**
 * Find the mode in an array
 * 
 * @param arr the array to search
 * @param size the size of the array
 * 
 * @return The mode of the array.
 */
int findModeFreq(int array[], int n){
  int freq[n];
  int max = 0, mode;
  for (int i = 0; i < n; i++){
    mode = 0;
    for (int j = 0; j < n; j++) {
      if (array[i] == array[j]){
        mode += 1;
      }
    }
    freq[i] = mode;
  }
  for (int i = 0; i < n; i++) {
    if (freq[i] > max){
      max = freq[i];
    }
  }
  return max;
}
