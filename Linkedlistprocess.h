// Author: Kongmeng Lim
// ID: 982928

#ifndef LINKED_LIST_PROCESS
#define LINKED_LIST_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Process {
  // processID
  int pid;
  // fileID
  int fidLck;
  int fidReq;
  struct Process *ptr;
} Process;

void insert(Process** headProcess, int pid, int fidLock, int fidReq);
void printList(Process* process);
int getNumFiles(Process* process, int numProcesses);
int remove_duplicate(int arr[], int size);
#endif // PROCESS_LIST
