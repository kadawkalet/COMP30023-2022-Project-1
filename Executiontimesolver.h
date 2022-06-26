// Author: Kongmeng Lim
// ID: 982928

#ifndef EXECUTION_TIME_SOLVER
#define EXECUTION_TIME_SOLVER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "Linkedlistprocess.h"

void executionTimeSolver(Process* process, int numProcesses, int numFiles);
int findExecutionTimes(Process* process, int numProcesses);
int findModeFreq(int arr[], int size);
#endif // PROCESS_LIST
