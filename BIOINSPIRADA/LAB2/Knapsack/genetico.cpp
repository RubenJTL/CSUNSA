#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>

#include "genetico.h"

using namespace std;

int main(){
	
	int p[] = {6, 5, 8, 9, 6, 7, 3};
	int w[] = {2, 3, 6, 7, 5, 9, 4};
	Num W=9;

	vector<int> profit(p, p + sizeof(p) / sizeof (*p) );
	vector<int> weight(w, w + sizeof(w) / sizeof (*w) );
	int n=profit.size();


	//genetico(poblacion,cromosomas,iteraciones,participantes,cross,mutacion,profit,weight,W_)
    genetico a(100,n,2,3,0.9,0.5,profit,weight,W);
   // while(true){
   	//cout<<endl;
   	a.run();
   	
		    


    return 0;
}
