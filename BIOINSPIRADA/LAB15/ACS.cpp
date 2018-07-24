#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "ACS.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	cout.precision(5);
	vector<vector<Num>> matrix={{0,35,71,99,71,75,41},//A
{35,0,42,80,65,82,47},
{71,42,0,45,49,79,55},
{99,80,45,0,36,65,65},
{71,65,49,36,0,31,32},
{75,82,79,65,31,0,36},
{41,47,55,65,32,36,0}};
	vector<vector<Num>> matrix1={{0,2,0,0,0,0,2},//A
{2,0,3,0,0,1,0},
{0,3,0,0,0,1,0},
{0,0,0,0,3,0,1},
{0,0,0,3,0,0,0},
{0,1,1,0,0,0,0},
{2,0,0,1,0,0,0}};/*
	vector<vector<Num>> matrix={{0,50,50,94,50},//A
{50,0,22,50,36},
{50,22,0,44,14},
{94,50,44,0,50},
{50,36,14,50,0}};
	vector<vector<Num>> matrix1={{0,0,2,0,3},//A
{0,0,0,3,0},
{2,0,0,0,0},
{0,3,0,0,1},
{3,0,0,1,0}};

/*	vector<vector<double>> matrix={{0.0,12.0,3.0,23.0,1.0,5},//A
{12.0,0.0,9.0,18.0,3.0,41},
{3.0,9.0,0.0,89.0,56.0,21},
{23.0,18.0,89.0,0.0,87.0,46.5},
{1.0,3.0,56.0,87.0,0.0,55},
{5.0,41.0,21,46.5,55.0,0.0}};
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
