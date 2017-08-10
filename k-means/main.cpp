#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>

#include "kmeansM.h"

using namespace std;


int main(){
	kmeans k("irisM.dat",3);
	for(unsigned i=0;i<30;++i){
    //while(true){
    
    	cout<<"centros"<<endl;
    	k.mostrar_centros();
    	cout<<"puntos y clasificador"<<endl;
    	k.mostrar();
    	k.save();
    	system("octave ploting3.m");
    	k.run();
    	k.cambiar_centros();
    	cout<<endl;
    }
    k.test();
    //k.mostrar_cluster();
    k.test("irisO.dat");
    //}

	/*auto p1=make_tuple(0.29,0.74);
	auto p2=make_tuple(0.48,0.87);
	cout<<distancia(p1,p2);
	*//*
    kmeans k("iris2d.dat",3);
    for(unsigned i=0;i<50;++i){
    //while(true){
    
    	cout<<"centros"<<endl;
    	k.mostrar_centros();
    	cout<<"puntos y clasificador"<<endl;
    	k.mostrar();
    	k.save();
    	system("sh ploting.sh");
    	k.run();
    	k.cambiar_centros();
    	cout<<endl;
    }
    //}
    /*
    k.mostrar();
    cout<<k.k<<endl;
    k.mostrar_centros();
    k.run();
   // k.mostrar_distancias();
    
  //  k.clasificar(); 
    k.mostrar();
    k.cambiar_centros();
    k.mostrar_centros();
*/
}

