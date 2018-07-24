#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "genetico.h"

using namespace std;



int main(){

//genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes);
	genetico a(10,0.5,-100,100,100,0.5,3,0.9);
    a.run();
    return 0;
}
