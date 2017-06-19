#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
int main () 
{
    ofstream myfile ("example.txt");

    if (myfile.is_open())
    {
        double value       = 11.23444556;

        myfile << setprecision(10) << value<<"\n";
        myfile << setprecision(10) << value<<"\n";
        myfile.close();
    }   

    return 0;
}