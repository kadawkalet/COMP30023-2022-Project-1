// Author: Kongmeng Lim
// ID: 982928

#include "Deadlockbreakingsolver.h"

/**
 * Given a list of processes, detect deadlock and find the processes that are involved in a deadlock
 * 
 * @param headProcess the head of the linked list of processes
 * @param numProcesses The number of processes in the system.
 * @param numFiles the number of files in the system
 */
void deadlockbreaker(Process* headProcess, int numProcesses, int numFiles){
  /* This is initializing the array and input array. */
  int array[numProcesses][numProcesses][3];
  memset( array, -1, numProcesses*numProcesses*3*sizeof(int));
  int input[numProcesses][3];
  memset( input, -1, numProcesses*3*sizeof(int));
  int k, i = numProcesses - 1;
  /* This is populating process id and file id into the array and input array. */
  while (headProcess != NULL) {
    k = 0;
    array[i][0][k] = headProcess->pid;
    input[i][k] = headProcess->pid;
    array[i][0][k+1] = headProcess->fidLck;
    input[i][k+1] = headProcess->fidLck;
    array[i][0][k+2] = headProcess->fidReq;
    input[i][k+2] = headProcess->fidReq;
    headProcess = headProcess->ptr;
    i -= 1;
  }

  /* This is populating the process id and file id into the array when finding sequencial linked. */
  for (int i = 0; i < numProcesses; i++) {
    for (int j = 1; j < numProcesses; j++) {
      for (int k = 0; k < numProcesses; k++) {
        if (array[i][j-1][2] == input[k][1]) {
          array[i][j][0] = input[k][0];
          array[i][j][1] = input[k][1];
          array[i][j][2] = input[k][2];
        }
      }
    }
  }
  
  int terminates[numProcesses];
  memset( terminates, -1, numProcesses*sizeof(int));
  /* This is checking if there is a deadlock and find process ids to be terminated. */
  int fileReq, fileLock, terminatedProcess, deadlock = 0, t = 0;
  for (int i = 0; i < numProcesses; i++) {
    if (array[i][0][0] == -1){
      continue;
    }
    terminatedProcess = array[i][0][0];
    fileReq = array[i][0][1];
    fileLock = -1;
    for (int j = 1; j < numProcesses; j++) {
      if (array[i][j][0] == -1){
        break;
      }
      if (array[i][j][0] < terminatedProcess) {
        terminatedProcess = array[i][j][0];
      }
      fileLock = array[i][j][2];
      if (fileReq == fileLock){
        terminates[t] = terminatedProcess;
        deadlock = 1;
        t += 1;
        break;
      }
    }
		if (numProcesses == 2){
			break;
		}
  }
  int numProcessesTerminated = numProcesses;
  numProcessesTerminated = remove_duplicate(terminates, numProcessesTerminated);
  printf("Processes %d\n", numProcesses);
  printf("Files %d\n", numFiles);
  if (deadlock == 0){
    printf("No deadlocks\n");
  } else {
    printf("Deadlock detected\n");
    printf("Terminate");
    for (int i = 0; i < numProcessesTerminated; i++) {
      if (terminates[i] != -1){
        printf("% d", terminates[i]);
      }
    }
  }
}
