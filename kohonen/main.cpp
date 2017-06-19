#include <iostream>
#include "Kohonen.h"

using namespace std;
int main(){
	NeuroMap nm("res20AA","res20BB","irisN.dat","testIrisN.dat");
    //nm.printClases();
    nm.runTests();
}