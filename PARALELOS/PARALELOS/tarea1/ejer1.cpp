#include <iostream>
#include <ctime> 



using namespace std;

int main(){
	unsigned t0, t1;
	int MAX=1000;
	double A[MAX][MAX],x[MAX],y[MAX];

	for (int i = 0; i < MAX; ++i){
		for (int j = 0; j < MAX; ++j){
			A[i][j]=i+j;
		}		
	}

	for (int i = 0; i < MAX; ++i){
		x[i]=i;		
	}

	for (int i = 0; i < MAX; ++i){
		y[i]=0;		
	}

	t0=clock();
	for(int j=0;j<MAX;j++){
		for(int i=0;i<MAX;i++){
			y[i] += A[i][j]*x[j]; 
		}
	}	
	t1 = clock();

	
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
	

	for (int i = 0; i < MAX; ++i){
		y[i]=0;		
	}

	t0=clock();
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){
			y[i] += A[i][j]*x[j];
		}
	}
	t1 = clock();
 

	
 
	time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
	return 0;
}