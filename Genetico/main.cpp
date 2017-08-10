#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>

#include "genetico.h"

using namespace std;

int main(){
	string iterator;
    genetico a(50);
   // while(true){
    	cin>>iterator;
    	cout<<endl;
	    if(iterator=="run"){
	    for(unsigned i=0;i<20;++i){
		    a.mostrar_poblacion();
		    cout<<a.fitness<<endl;
		    a.reproducir();
		    a.mostrar_hijos();
		    a.Mutar();
		    cout<<endl;
			a.mostrar_hijos();		    
		    a.new_generation();
		    cout<<endl;
		    a.save();
		//}	
			a.mostrar_poblacion();
		    cout<<a.fitness<<endl;
			system("sh plot.sh");
		}
		}
		else if(iterator=="plot"){
			system("sh plot.sh");
	//	}
	}

    return 0;
}

