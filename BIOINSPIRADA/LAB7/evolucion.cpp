#include <iostream>
#include <stdlib.h>   //atoi
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include "ee.h"
#include <vector>
using namespace std;



int main(){
	srand(time(NULL));
	//cout.precision(10);
	/*vector<vector<int>> matrix={	{0,2,2,1,4},//A
									{2,0,3,2,3},	//B
									{2,3,0,2,2},//C
									{1,2,2,0,4},//D
									{4,3,2,4,0}//E
										};

*/
	/*string entradas="NS";
	string salidas="NS";*/
	P_evolutiva a(1,0.3,-10,10);
	a.run();
    return 0;
}

