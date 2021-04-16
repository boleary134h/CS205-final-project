#include <stdio.h>
#include <math.h>

/*
This is a serial implementation of the pagerank algorithm
Input: 
    - N: number of rows/columns in matrix (nodes in graph)
    - similarity: matrix of sentence similarity scores. For pagerank,
      This is considered to be the equivalent to web page transition 
      probability
    - centrality: array to store the centrality results in
Output: 
    - no direct output. Centrality stores are saved in input centrality array
*/

double damping = 0.85; // pagerank damping parameter
int max_iterations = 50; // maximum number of iterations

void pagerank(int N, double similarity[N][N], double centrality[N]) {

	// make sure that the transition matrix has zeros for i=j
	double transition[N][N]; 
	for (int i = 0; i < N ; i++) { //row
        for (int j = 0; j < N; j++) {
        	if (i != j) {
        		transition[i][j] = similarity[i][j];
        	}
        	else {
        		transition[i][j] = 0.0;
        	}
        }
	}

	// make sure the each row in transition matrix sums to 1
	double rowsum = 0.0;
	for (int i = 0; i < N ; i++) { 
		rowsum = 0.0;
        for (int j = 0; j < N; j++) {
        	rowsum += transition[i][j];
        }
        if (rowsum > 0) {
            for (int j = 0; j < N; j++) {
        	    transition[i][j] = transition[i][j]/rowsum;
        	}
        } 
        // fix for the dangling node problem
        else {
        	for (int j = 0; j < N; j++) {
        		transition[i][j] = 1.0/N;
        	}

        }
	}

	// dampen transition matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			transition[i][j] = damping*transition[i][j]+(1.0-damping)/N;
		}
	}

    // used for debugging
    /*
    for (int i = 0; i < N ; i++) { //row
        printf("\n");
        for (int j = 0; j < N; j++) {
            printf("%f ",transition[i][j]);
        }
    }
    */

	// initialize centrality matrix
	for (int i = 0; i < N; i++) {
		centrality[i] = 1.0/N;
	}

    // iterate up to max iterations
	int iteration = 0;
	while (iteration < max_iterations) {

        // initialize temp centrality
        double temp_centrality[N]; 
        for (int i = 0; i < N; i++) {
            temp_centrality[i] = 0.0;
        }

        // do update
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				temp_centrality[i] += centrality[j]*transition[j][i];
			}
		}

		// compute the error for convergence
        double error = 0.0;
        for (int i = 0; i < N; i++) {
        	error += fabs(temp_centrality[i] - centrality[i]);
        }
        if (iteration % 5 == 0) {
            printf("error: %f \n",error);
        }
        
        // transfer centrality
        for (int i = 0; i < N; i++) {
        	centrality[i] = temp_centrality[i];
        }

        // break while loop if reach convergence
        iteration++;
        if (error < 0.001) {
        	printf("Reached convergence after %d iterations \n" , iteration);
        	break;
        }
	}
	if (iteration == max_iterations) {
		printf("Reached max number of iterations \n");
	}
    
}


// main used for testing
int main(void)
{
	int N = 3;
	double similarity[3][3] = {
		{0,0.5,0.5},
		{0.5,0,0},
        {0.5,0,0}
	};
    double centrality[N];

    pagerank(N, similarity, centrality);

    // output centrality scores
    for (int i = 0; i < N; i++) {
    	printf( " %1.4f \n ", centrality[i]);
    }
}
