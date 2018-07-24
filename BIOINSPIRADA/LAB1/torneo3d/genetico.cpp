#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>

#include "genetico.h"

using namespace std;

int main(){
	string iterator;
	//poblacion, cromosomas. iteraciones,cruzamiento, mutacion,punto1 .punto2,participantes
    genetico a(20,5,2,0.9,0.01,1,3,5);
   // while(true){
   	cout<<endl;
   	a.run();
   	
		    


    return 0;
}
