#include <iostream>
#include <vector>

typedef double Num;



      /*  ofstream aRes0("MergeSort.dat",std::ios_base::app);
        aRes0<<"numero de datos \t tiempo\n";
        for(int j=ini;j<=fin;j+=iter)
        {
            if(j==0){
                j++;
            }
            Lista list(j);
            Lista listmp(0);
            double tiempo;
            cout<<"MergeSort iteracion con "<<j<<" elementos"<<endl; 

            clock_t t;
            for(int i=0;i<500;i++){
                listmp.copy(list);
                t = clock();
                listmp.MergeSort(0,(int)listmp.ListSize);
                t = clock() - t;
            }
            tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
            aRes0<<j<<"\t"<<tiempo<<"\n";
            if(j==1){
                j--;
            }
        }
        aRes0.close();

        ofstream aRes1("QuickSort.dat",std::ios_base::app);
        aRes1<<"numero de datos \t tiempo\n";
        for(int j=ini;j<=fin;j+=iter)
        {
            if(j==0){
                j++;
            }
            Lista list(j);
            Lista listmp(0);
            double tiempo;
            cout<<"QuickSort iteracion con "<<j<<" elementos"<<endl; 

            clock_t t;
            for(int i=0;i<500;i++){
                listmp.copy(list);
                t = clock();
                listmp.QuickSort(0,(int)listmp.ListSize-1);
                t = clock() - t;
            }
            tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
            aRes1<<j<<"\t"<<tiempo<<"\n";
            if(j==1){
                j--;
            }
        \\}
        aRes1.close();
    */


using namespace std;

Num C(Num,Num);
Num Factorial(Num);
Num Fibonacci(Num);
Num Catalan(Num);
Num Catalan2(Num);
Num Hanoi(Num);
Num Ackermann(Num,Num);


int main(){

	cout<<Fibonacci(7)<<endl;
	cout<<Factorial(5)<<endl;
	cout<<Catalan(7)<<endl;
	cout<<Catalan2(7)<<endl;
	cout<<Hanoi(2)<<endl;
	cout<<Ackermann(3,4)<<endl;

}


Num C(Num n,Num k){
	return Factorial(n)/(Factorial(k)*Factorial(n-k));
}

Num Factorial(Num n){
	if(n==1 or n==0){
		return n;
	}
	return n*Factorial(n-1);
}

Num Fibonacci(Num n){
	if(n==1 or n==0){
		return n;
	}


	return Fibonacci(n-1)+Fibonacci(n-2);
}

Num Catalan(Num n){
	if(n==0){
		return 1;
	}
	return  2*(2*n-1)*Catalan(n-1) /(n+1);
}
Num Catalan2(Num n){
	return C(2*n,n)-C(2*n,n-1);
}


Num Hanoi(Num n){
	if(n==1){
		return 1;
	}
	return 2 * Hanoi(n-1) + 1;
}

Num Ackermann(Num m,Num n){
	if(m==0){
		return n+1;
	}
	if(m>0 and n==0){
		return Ackermann(m-1,1);
	}
	if(m>0 and n>0){
		return Ackermann(m-1,Ackermann(m,n-1));
	}
}