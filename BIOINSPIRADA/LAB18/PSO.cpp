#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "PSO.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	vector<vector<Num>> matrix={{0,1,3,4,5},//A
{1,0,1,4,8},
{3,1,0,5,1},
{4,4,5,0,2},
{5,8,1,2,0}};
	//printf("HOLA\n");		
		PSO a(100,matrix);

	   //	 a.run();
	    return 0;
	}
