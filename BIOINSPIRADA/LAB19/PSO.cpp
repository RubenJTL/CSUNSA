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
	//printf("HOLA\n");
	vector<vector<Num>> matrix={{0,12,3,23,1,5,23,56,12,11},//A
{12,0,9,18,3,41,45,5,41,27},
{3,9,0,89,56,21,12,48,14,29},
{23,18,89,0,87,46,75,17,50,42},
{4,4,5,0,2},
{4,4,5,0,2},
{4,4,5,0,2},
{4,4,5,0,2},
{4,4,5,0,2},
{5,8,1,2,0}};		
		PSO a(100);

	   //	 a.run();
	    return 0;
	}
