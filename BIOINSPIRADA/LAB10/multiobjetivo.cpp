#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "multiobjetivo.h"

using namespace std;



int main(){
    srand(time(NULL));

//genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes);
    NSGAII a(10);
    a.run();
    return 0;
}
