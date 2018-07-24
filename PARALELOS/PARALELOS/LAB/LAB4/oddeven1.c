#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>


#define MAX_NUM 200

int * getRandomVector(int size){
	srand(time(NULL));
	int * res = (int *) malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++){
		res[i] = rand() % MAX_NUM + 1;
	}
	return res;
}

void OddEvenSort (int *vector, int vectorSize, int thread_count){
int i,phase,tmp;
for(phase=0; phase<vectorSize;phase++){
		if(phase%2==0){
#pragma omp parallel for num_threads(thread_count) default(none) shared(vector,vectorSize) private(i,tmp)
			for(i=1;i<vectorSize;i+=2){
				if(vector[i-1]>vector[i]){
					tmp= vector[i-1];
					vector[i-1]=vector[i];
					vector[i]=tmp;				
				}
			}
		}else{
#pragma omp parallel for num_threads(thread_count) default(none) shared(vector,vectorSize) private(i,tmp)
			for(i=1;i<vectorSize-1;i+=2){
				if(vector[i]>vector[i+1]){
					tmp= vector[i+1];
					vector[i+1]=vector[i];
					vector[i]=tmp;				
				}	
			}
		}
	}
    
}

int main(int argv, char ** argc){
	if(argv != 3){
		printf("Argumentos Erroneos <vectorSize> <numThreads>\n");
		return 0;
	}
	int vectorSize = atoi(argc[1]);
	int thread_count = atoi(argc[2]);
	int * vector = getRandomVector(vectorSize);
	
	double start_time = omp_get_wtime();
	OddEvenSort(vector,vectorSize, thread_count);

	double seconds = omp_get_wtime() - start_time;	
	printf("%lf\n", seconds);
	
	return 0;
}
