// Author: Kongmeng Lim
// ID: 982928

#include "Deadlocksimulationsolver.h"

/**
 * This function is used to simulate the process of finding deadlock
 * 
 * @param headProcess the head of the process list
 * @param n The number of processes
 */
void deadlockSimulationSolver(Process* headProcess, int n){
	/* This is used to initialize the array and required variables. */
	int i = n - 1, k;
	int array[n][n][3];
	memset( array, -1, n*n*3*sizeof(int));
	int input[n][3];
	memset( input, -1, n*3*sizeof(int));
	/* This is used to initialize the array and the input. */
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

	/* This is used to find the deadlock. */
	for (int i = 0; i < n; i++) {
		input[i][0] = -1;
		input[i][1] = -1;
		input[i][2] = -1;
		int addAt = 1;
    	for (int k = 0; k < n; k++) {
			bool shouldAdd = true;
			for (int l = 0; l <= addAt && shouldAdd; l++) {
				if (array[i][l][1] == input[k][1] ||
					array[i][l][2] == input[k][1] ||
					array[i][l][1] == input[k][2] ||
					array[i][l][2] == input[k][2]) {
					shouldAdd = false;
				}
			}
			if (shouldAdd) {
				array[i][addAt][0] = input[k][0];
				array[i][addAt][1] = input[k][1];
				array[i][addAt][2] = input[k][2];
				input[k][0] = -1;
				input[k][1] = -1;
				input[k][2] = -1;
				array[k][0][0] = -1;
				array[k][0][1] = -1;
				array[k][0][2] = -1;
				addAt++;
			}
    	}
  	}
	
	/* This is used to print the result. */
	int t = 0;
	for (int i = 0; i < n; i++) {
		bool shouldAddTime = false;
		for (int j = 0; j < n; j++) {
			if(array[i][j][0] == -1){
				continue;
			} else {
				shouldAddTime = true;
				printf("%d %d %d,%d\n", t, array[i][j][0], array[i][j][1], array[i][j][2]);
			}
		}
		if(shouldAddTime){
			t += 1;
		}
	}
	printf("Simulation time %d\n", t);
}
