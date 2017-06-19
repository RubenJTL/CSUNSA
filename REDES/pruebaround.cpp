#include <iostream>
#include <math.h>
using namespace std;
 
int main()
{
    float n1, n2, n3, n4;
    cout << "Numero 1: ";
    cin >> n1;
    cout << endl << "Numero 2: ";
    cin >> n2;
    cout << endl << "Numero 3: ";
    cin >> n3;
    cout << endl << "Numero 4: ";
    cin >> n4;
    n1 = round(n1);
    n2 = round(n2);
    n3 = round(n3);
    n4 = round(n4);
    cout << endl << "Aproximados: " << endl << endl;
    cout << "Numero 1: " << n1;
    cout << endl << "Numero 2: " << n2;
    cout << endl << "Numero 3: " << n3;
    cout << endl << "Numero 4: " << n4 << endl << endl;
}
