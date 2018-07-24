#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "utils.h"
#include "omp.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void matrix_vector(int ** A, int*x, int* y,int m,int n,int thread_count){
int i,j;

#pragma omp parallel for num_threads(thread_count) default(none) private(i, j) shared(A, x, y, m, n)
	for (i = 0; i < m; i++) {
		y[i] = 0.0;
		for (j = 0; j < n; j++)
			y[i] += A[i][j]*x[j];
	}
}


int main(int argv, char ** argc){
	if(argv != 4){
		printf("Faltan Argumentos <numThreads> <tamMatrixFil> <tamMatrixCol>\n");
		return 0;
	}
	int numThreads = atoi(argc[1]);
	int tamMatrixFil = atoi(argc[2]);
	int tamMatrixCol = atoi(argc[3]);
	int ** matrix = getRandomMatrix(tamMatrixFil, tamMatrixCol);
	int * vectory= getRandomVector(tamMatrixFil);
	int * vector = getRandomVector(tamMatrixCol);
	//printVector(vector,tamMatrixCol);
	//printMatrix(matrix,tamMatrixFil,tamMatrixCol);
	double start_time = omp_get_wtime();
	matrix_vector(matrix,vector,vectory,tamMatrixFil,tamMatrixCol,numThreads);
	double seconds = omp_get_wtime() - start_time;	
	printf("%lf\n", seconds);
	//	ssprintVector(vectory,tamMatrixFil);
}
