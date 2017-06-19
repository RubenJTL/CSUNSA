#include <iostream>
#include <vector>
#include <cstdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef float Num;
typedef vector<Num> Lista;

Lista IntercambioSort(Lista );
Lista InsertSort(Lista );
Lista BubbleSort(Lista);
Lista SelectSort(Lista);
Lista SelectSort2(Lista);
Lista merge(Lista,Lista);
Lista BrickSort(Lista);
Lista ShakerSort(Lista);

Lista llenar(int,int);
void print(Lista);

void ejer1();
void ejer2();
void ejer3();
void ejer4();
void ejer5();

int main(){
	
	srand (time(NULL));
	cout<<"EJERCICIO 1"<<endl;
	ejer1();
	cout<<"EJERCICIO 2"<<endl;
	ejer2();
	cout<<"EJERCICIO 3"<<endl;
	ejer3();
	cout<<"EJERCICIO 4"<<endl;
	ejer4();
	cout<<"EJERCICIO 5"<<endl;
	ejer5();
	return 0;
}

void print(Lista list){
	for(unsigned i=0;i<list.size();++i){
		cout<<list[i]<<" ";
	}
	cout<<endl;
}

Lista llenar(int tam, int entero){
	Lista list;
	if(entero==1)
		for(unsigned i=0;i<tam;++i){
			list.push_back(rand()%10+1);
		}
	else{
		
		for(unsigned i=0;i<tam;++i){
			list.push_back(0 + rand()*(10-0) / (float)0.1);
		}

	}

	return list;
}


Lista SelectSort(Lista list){
	int minimo=0;
	int n=list.size();
	unsigned i,j;
	for(i=0;i<n-1;++i){
		minimo=i;
		for(j=i+1;j<n;++j){
			if(list[minimo]>list[j]){
				minimo=j;
			}
		}
		swap(list[minimo],list[i]);
	}
	return list;
}

Lista BubbleSort(Lista list){
	unsigned interruptor=1,pasada=0,j;
	int n= list.size();
	for(pasada=0;pasada<n-1 && interruptor==1;pasada++){
		interruptor=0;
		for(j=0;j<n-pasada-1;j++){
			if(list[j]>list[j+1]){
				interruptor=1;
				swap(list[j],list[j+1]);
			}
		}
	}
	return list;
}

Lista InsertSort(Lista list){
	int n= list.size();
	unsigned i,j;
	int aux;
	for(i=1;i<n;++i){
		j=i;
		aux=list[i];
		while(j>0 && aux<list[j-1]){
			list[j]=list[j-1];
			--j;
		}
		list[j]=aux;
	}
	return list;
}

Lista IntercambioSort(Lista list){
	int n=list.size();
	for(unsigned i=0;i<n-1;++i){
		for(unsigned j=i+1;j<n;++j){
			if(list[i]>list[j]){
				swap(list[i],list[j]);
			}
		}		
	}
	return list;
}

Lista merge(Lista list1,Lista list2){
	int i=0,j=0,l=0;
	Lista list;
	if(list1[i]<list2[j]){list.push_back(list1[i]);i++;}
	else{list.push_back(list2[j]);j++;}
	while(i<list1.size() or j<list2.size() ){
		if(i<list1.size() and j<list2.size()){
			if(list1[i]<=list2[j]){
				if(list[l] != list1[i] ){
					list.push_back(list1[i]);l++;
				}i++;
			}
			else if(list1[i]>list2[j]){
				if(list[l] != list2[j] ){
					list.push_back(list2[j]);l++;
				}j++;
			}
			
		}
		else if(i<list1.size()){
			if(list1[i-1] != list1[i] and  list[l] != list1[i] ) {
				list.push_back(list1[i]);l++;
			}i++;
		}
		else if(j<list2.size()){
			if(list2[j-1] != list2[j]  and list[l] != list2[j] ){
				list.push_back(list2[j]);l++;
			}j++;
		}
	}
	return list;	
}

Lista SelectSort2(Lista list){
	int minimo=0,temp=0;
	int n=list.size();
	unsigned i,j;
	for(i=0;i<n-1;i++){
		minimo=i;
		for(j=i;j<n;j+=2){
			if(i%2==0){
				if(list[minimo]<list[j]){
					minimo=j;
				}
			}else{
				if(list[minimo]>list[j]){
					minimo=j;
				}
			}
		}
		swap(list[minimo],list[i]);
	}
	return list;
}

Lista BrickSort(Lista list){	//O(n*m)
	int bol=0,n=list.size();	//O(1)
	unsigned i; 				//O(1)
	while(bol==0){							//O(m)	//	
		bol=1;								//O(1)	//
		for (i = 1; i < n - 1; i += 2) {	//O(n)	////
            if (list[ i ] > list[ i + 1 ]){	//O(1)	////
                swap( list[i],list[i+1]);	//O(1)	//////
                bol = 0;					//O(1)	//////
            }										/////// O(n*m)
        }											//////
        print(list);								//////
        for (i = 0; i < n - 1; i += 2) {	//O(n)	////
            if (list[ i ] > list[ i + 1 ]){	//O(1)	////
                swap( list[i],list[i+1]);	//O(1)	//
                bol = 0;					//O(1)	//
            } 	
        }
        print(list);  
	}
	return list;
}

Lista ShakerSort(Lista list){	//O(m^2)
	int n=0, m=list.size()-1;				//O(1)
	while(n<=m){							//O(m)	//
		for(unsigned i=n;i<m;++i){			//O(m)	//
			if(list[i]>list[i+1]){			//O(1)	////
				swap(list[i],list[i+1]);	//O(1)	////
			}										//////
		}											//////
		m--;										////////
		print(list);								///////// O(m^2)
		for(unsigned j=m;j>n;--j){			//O(m)	////////
			if(list[j]<list[j-1]){			//O(1)	//////
				swap(list[j],list[j-1]);	//O(1)	//////
			}										////
		}											////
		n++;										//
		print(list);								//
	}
	return list;
}

void ejer1(){
	Lista A,B;
	A=llenar(10,1);
	B=llenar(10,1);
	cout<<"INTERCAMBIO"<<endl;
	cout<<"A :";
	print(A);
	cout<<"A :";
	print(IntercambioSort(A));
	cout<<"B : ";
	print(B);
	cout<<"B : ";
	print(IntercambioSort(B));

	cout<<"INSERCION"<<endl;
	cout<<"A :";
	print(A);
	cout<<"A :";
	print(InsertSort(A));
	cout<<"B : ";
	print(B);
	cout<<"B : ";
	print(InsertSort(B));

	cout<<"BURBUJA"<<endl;
	cout<<"A :";
	print(A);
	cout<<"A :";
	print(BubbleSort(A));
	cout<<"B : ";
	print(B);
	cout<<"B : ";
	print(BubbleSort(B));

	cout<<"SELECCION"<<endl;
	cout<<"A :";
	print(A);
	cout<<"A :";
	print(SelectSort(A));
	cout<<"B : ";
	print(B);
	cout<<"B : ";
	print(SelectSort(B));
	cout<<endl;
	cout<<"A: ";
	A=BubbleSort(A);
	print(A);
	cout<<"B: ";
	B=BubbleSort(B);
	print(B);
	cout<<"C: ";
	print(merge(A,B));
}

void ejer2(){
	cout.unsetf ( std::ios::floatfield ); 
	cout.precision(3);
	printf("lista : ");
	Lista list;
	list=llenar(30,0);
	print(list);
	printf("SelectSort2 : \n");
	print(SelectSort2(list));
	printf("lista : ");
	list=llenar(30,1);
	print(list);
	printf("SelectSort2 : \n");
	print(SelectSort2(list));
}

void ejer3(){
	Lista list;
	list=llenar(10,1);
	printf("LISTA : ");
	print(list);
	printf("\n BrickSort \n");
	print(BrickSort(list));
}

void ejer4(){
	Lista list;
	list=llenar(10,1);
	printf("LISTA : ");
	print(list);
	printf("\n ShakerSort \n");
	print(ShakerSort(list));
}
void ejer5(){
	Lista list;
	list=llenar(10,1);
	printf("LISTA : ");
	print(list);
	printf("\n SelectSort \n");
	print(SelectSort(list));
}