#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "multiobjetivo.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	vector<vector<int>> matrix={{0,12,3,23,1,5,23,56,12,11},//A
{12,0,9,18,3,41,45,5,41,27},
{3,9,0,89,56,21,12,48,14,29},
{23,18,89,0,87,46,75,17,50,42},
{1,3,56,87,0,55,22,86,14,33},
{5,41,21,46,55,0,21,76,54,81},
{23,45,12,75,22,21,0,11,57,48},
{56,5,48,17,86,76,11,0,63,24},
{12,41,14,50,14,54,57,63,0,9},
{11,27,29,42,33,81,48,24,9,0}};

	vector<vector<int>> matrix1={{0,22,47,15,63,21,23,16,11,9},//A
{22,0,18,62,41,52,13,11,26,43},
{47,18,0,32,57,44,62,20,8,36},
{15,62,32,0,62,45,75,63,14,12},
{63,41,57,62,0,9,99,42,56,23},
{21,52,44,45,9,0,77,58,22,14},
{23,13,62,75,99,77,0,30,25,60},
{16,11,20,63,42,58,30,0,66,85},
{11,26,8,14,56,22,25,66,0,54},
{9,43,36,12,23,14,60,85,54,0}};

//genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes);
	genetico a(matrix,matrix1,10);
    a.run();
    return 0;
}
