#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "colonia.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	cout.precision(5);
	vector<vector<double>> matrix={{0,12,6,4},//A
{12,0,6,8},
{6,6,0,7},
{4,8,7,0}};
	vector<vector<double>> matrix1={{0,3,8,3},//A
{3,0,2,4},
{8,2,0,5},
{3,4,5,0}};
	/*vector<vector<double>> matrix={{0.0,12.0,3.0,23.0,1.0},//A
{12.0,0.0,9.0,18.0,3.0},
{3.0,9.0,0.0,89.0,56.0},
{23.0,18.0,89.0,0.0,87.0},
{1.0,3.0,56.0,87.0,0.0}};
*/
/*	vector<vector<Num>> matrix={{0,12,3,23,1,5,23,56,12,11},//A
{12,0,9,18,3,41,45,5,41,27},
{3,9,0,89,56,21,12,48,14,29},
{23,18,89,0,87,46,75,17,50,42},
{1,3,56,87,0,55,22,86,14,33},
{5,41,21,46,55,0,21,76,54,81},
{23,45,12,75,22,21,0,11,57,48},
{56,5,48,17,86,76,11,0,63,24},
{12,41,14,50,14,54,57,63,0,9},
{11,27,29,42,33,81,48,24,9,0}};*/
//genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes);
    Colonia a(matrix,matrix1);
    a.run();
    return 0;
}
