#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>

#include "genetico.h"

using namespace std;

int main(){
	string iterator;
	//poblacion, cromosomas. iteraciones, mutacion,punto1 .punto2,participantes
    genetico a(4,5,2,0.9,0.5,1,3,2);
   // while(true){
   	cout<<endl;
   	a.run();
   	
		    


    return 0;
}
