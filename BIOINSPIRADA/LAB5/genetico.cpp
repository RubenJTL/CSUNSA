#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "genetico.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	cout.precision(30);
	/*vector<vector<int>> matrix={	{0,2,2,1,4},//A
									{2,0,3,2,3},	//B
									{2,3,0,2,2},//C
									{1,2,2,0,4},//D
									{4,3,2,4,0}//E
										};

*/
	vector<double> entradas={0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
	vector<double> salidas={0,0.005,0.02,0.045,0.08,0.125,0.18,0.245,0.32,0.405};
	vector<string> operadores={"+","-","*","%","/"};
	//vector<string> operadores={"*","/"};
//genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes);
	//genetico(int poblacion,vector<double> &entradas,vector<double> &salidas,vector<string> &operadores)
	genetico a(100,entradas,salidas,operadores);
	a.run();
    return 0;
}

