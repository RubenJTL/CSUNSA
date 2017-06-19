#ifndef ORDENACION_H
#define ORDENACION_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 	///memcpy
#include <algorithm>    ///min

using namespace std;

typedef int Num;

void swap(Num & a,Num & b){
	Num aux;
	aux=a;
	a=b;
	b=aux;
}

class Lista{
	public:
		Lista();
		Lista(int dimension);
		
		///SORTS
		void IntercambioSort();
		void InsertSort();
		void BubbleSort();
		void SelectSort();
		void SelectSort2();
		void BrickSort();
		void ShakerSort();
		void ShellSort();
		void QuickSort(int, int,int);
		void QuickSort2(int, int);
		void QuickSortP(int, int);
		void QuickSortI(int, int);
		int partition(int,int,int);
		void Merge(int , int , int);
		void MergeSort(int ,int );

		///ITERATIVE SORTS
		void Iterative_QuickSort(int, int);
		void Iterative_MergeSort();

		///SEARCH
		int BinarySearch(Num); //return la posicion
		int SQuickSort(Num, int, int);


		///DISPLAY
		void print();


		int 	ListSize;
		Num * 	arreglo;
};



Lista::Lista(){ ListSize=0;
}

Lista::Lista(int dimension){
	srand(time(NULL));
	ListSize	=	dimension;
	arreglo		=	(Num *) malloc(sizeof(Num) * dimension);
	for(unsigned i=0;i<dimension;++i){
		arreglo[i]=rand()%dimension+1;
	}
}

void Lista::print(){
	for (unsigned i = 0; i < ListSize; ++i)
	{
		cout<<arreglo[i]<<" ";
	}
	cout<<endl;	
}


////SEARCH
int Lista::BinarySearch(Num clave){
	int central, bajo, alto;
	Num valorCentral;
	bajo = 0; alto = ListSize-1;
	while( bajo <= alto ){
		central = ( bajo + alto )/2;
		valorCentral = arreglo[ central ];
		if( clave == valorCentral ){
			return central;
		}
		else if (clave < valorCentral )
		{
			alto = central -1 ;
		}
		else bajo = central +1 ;
	}
	return -1;
}

int Lista::SQuickSort(Num clave,int ini ,int fin){
	int i = ini, j = fin;
	int pos = ( ini + fin) / 2 ;
	Num piv = arreglo[ pos ];
	while( i < j ){
		while( arreglo[i] < piv ){
			i++;			
		}
		while( piv < arreglo[ j ] ){
			j--;
		}
		if( i <= j ){
			if( i != j ){
				swap(arreglo[ i ] , arreglo[ j ]);
				
			} 
			i++;
			j--;
			
		}
	}
	if( ini < j  and ini<=clave-1 and clave-1<=j){
		SQuickSort(clave,ini,j);
	}
	if( i < fin and i<=clave-1 and clave-1<=fin){
		SQuickSort(clave,i,fin);
	}
	return arreglo[clave-1];
}


///*SEARCH*


////SORTS
void Lista::SelectSort(){
	int minimo=0;
	unsigned i,j;
	for(i=0;i<ListSize-1;++i){
		minimo=i;
		for(j=i+1;j<ListSize;++j){
			if(arreglo[minimo]>arreglo[j]){
				minimo=j;
			}
		}
		swap(arreglo[minimo],arreglo[i]);
	}
}

void Lista::BubbleSort(){
	unsigned interruptor=1,pasada=0,j;
	for(pasada=0;pasada<ListSize-1 && interruptor==1;pasada++){
		interruptor=0;
		for(j=0;j<ListSize-pasada-1;j++){
			if(arreglo[j]>arreglo[j+1]){
				interruptor=1;
				swap(arreglo[j],arreglo[j+1]);
			}
		}
	}
}

void Lista::InsertSort(){
	unsigned i,j;
	int aux;
	for(i=1;i<ListSize;++i){
		j=i;
		aux=arreglo[i];
		while(j>0 && aux<arreglo[j-1]){
			arreglo[j]=arreglo[j-1];
			--j;
		}
		arreglo[j]=aux;
	}	
}

void Lista::IntercambioSort(){
	
	for(unsigned i=0;i<ListSize-1;++i){
		for(unsigned j=i+1;j<ListSize;++j){
			if(arreglo[i]>arreglo[j]){
				swap(arreglo[i],arreglo[j]);
			}
		}		
	}
}

void Lista::SelectSort2(){
	int minimo=0,temp=0;
	
	unsigned i,j;
	for(i=0;i<ListSize-1;i++){
		minimo=i;
		for(j=i;j<ListSize;j+=2){
			if(i%2==0){
				if(arreglo[minimo]<arreglo[j]){
					minimo=j;
				}
			}else{
				if(arreglo[minimo]>arreglo[j]){
					minimo=j;
				}
			}
		}
		swap(arreglo[minimo],arreglo[i]);
	}	
}

void Lista::BrickSort(){	//O(n*m)
	int bol=0;	//O(1)
	unsigned i; 				//O(1)
	while(bol==0){							//O(m)	//	
		bol=1;								//O(1)	//
		for (i = 1; i < ListSize - 1; i += 2) {	//O(n)	////
            if (arreglo[ i ] > arreglo[ i + 1 ]){	//O(1)	////
                swap( arreglo[i],arreglo[i+1]);	//O(1)	//////
                bol = 0;					//O(1)	//////
            }										/////// O(n*m)
        }											//////								//////
        for (i = 0; i < ListSize - 1; i += 2) {	//O(n)	////
            if (arreglo[ i ] > arreglo[ i + 1 ]){	//O(1)	////
                swap( arreglo[i],arreglo[i+1]);	//O(1)	//
                bol = 0;					//O(1)	//
            } 	
        }  
	}	
}

void Lista::ShakerSort(){	//O(m^2)
	int n=0, m=ListSize-1;				//O(1)
	while(n<=m){							//O(m)	//
		for(unsigned i=n;i<m;++i){			//O(m)	//
			if(arreglo[i]>arreglo[i+1]){			//O(1)	////
				swap(arreglo[i],arreglo[i+1]);	//O(1)	////
			}										//////
		}											//////
		m--;										////////								///////// O(m^2)
		for(unsigned j=m;j>n;--j){			//O(m)	////////
			if(arreglo[j]<arreglo[j-1]){			//O(1)	//////
				swap(arreglo[j],arreglo[j-1]);	//O(1)	//////
			}										////
		}											////
		n++;										//								//
	}
}

void Lista::ShellSort(){
	unsigned i,j;
	int intervalo,tmp;
	intervalo=ListSize/2;
	while(intervalo>0){
		for(i=intervalo;i<ListSize;++i){
			j=i;
			tmp=arreglo[i];
			while(( j >= intervalo ) && ( arreglo[ j - intervalo ] ) >tmp){
				arreglo[ j ] = arreglo[ j - intervalo ];
				j = j - intervalo;
			}
			arreglo[ j ] = tmp ;
		}
		intervalo = intervalo/2 ;
	}
}

int Lista::partition(int ini, int fin ,int forma){
	int pos=(ini+fin)/2;
	int piv=arreglo[pos];
	int i=ini,j=fin;
	if(forma==1){
		while(true){
			while(arreglo[i]>piv and i<=j){
				i++;
			}
			while(arreglo[j]<piv and i<=j){
				j--;
			}
			if(i<j){
				swap(arreglo[i],arreglo[j]);
				i++;
				j--;
			}
			else{
				return j;
			}
		}
	}
	if(forma==2){
		while(true){
			while(arreglo[i]<piv ){
				i++;
			}
			while(arreglo[j]>piv and i<=j){
				j--;
			}
			if(i<j){
				swap(arreglo[i],arreglo[j]);
				i++;
				j--;
			}
			else{
				return j;
			}
		}
	}
	if(forma==3){
		int piv = arreglo[fin];
	    i = ini;
	    for (int j = ini; j < fin; j++)
	    {
	        if (arreglo[j] <= piv)
	        {
	            swap (arreglo[i], arreglo[j]);
	            i++;
	            
	        }
	    }
	    swap (arreglo[i], arreglo[fin]);
	    return (i);
	}

}

void Lista::QuickSort(int ini,int fin,int forma){
	if(ini<fin){
		int p=partition(ini,fin,forma);
		QuickSort(ini,p,forma);
		QuickSort(p+1,fin,forma);
	}
}

void Lista::QuickSort2(int ini,int fin){
		QuickSortI(ini,fin-1);
		QuickSortP(ini,fin-1);
}

void Lista::QuickSortI(int ini,int fin){
	if(fin%2!=0)
		fin--;
	if(ini%2!=0)
		ini++;
	int i = ini, j = fin;
	int pos = ( ini + fin) / 2 ;
	if(pos%2!=0){
		pos++;
	}
	Num piv = arreglo[ pos ];
	while( i < j ){
		while( arreglo[i] > piv ){
			i+=2;
			
		}
		while( piv > arreglo[ j ] ){
			j-=2;
		}
		if( i <= j ){
			if( i != j ){
				swap(arreglo[ i ] , arreglo[ j ]);
				
			} 
			i+=2;
			j-=2;		
		}
	}
	if( ini < j ){
		QuickSortI(ini,j);
	}
	if( i < fin ){
		QuickSortI(i,fin);
	}

}

void Lista::QuickSortP(int ini,int fin){
	if(fin%2==0)
		fin--;
	if(ini%2==0)
		ini++;
	int i = ini, j = fin;
	int pos = ( ini + fin) / 2 ;
	if(pos%2==0){
		pos++;
	}
	Num piv = arreglo[ pos ];
	while( i < j ){
		while( arreglo[i] < piv ){
			i+=2;			
		}
		while( piv < arreglo[ j ] ){
			j-=2;
		}
		if( i <= j ){
			if( i != j ){
				swap(arreglo[ i ] , arreglo[ j ]);
			} 
			i+=2;
			j-=2;
		}
	}
	if( ini < j ){
		QuickSortP(ini,j);
	}
	if( i < fin ){
		QuickSortP(i,fin);
	}
}

void Lista::Merge(int left , int medio , int right){ 
	Num *temp= (Num *) malloc(sizeof(Num) * ListSize);
	memcpy(temp,arreglo,ListSize*sizeof(Num));
	int left_ = left ;
	int right_ = medio + 1;
	int pos = left_;
	while (left_ <= medio || right_ <= right) {
          if (left_ <= medio && right_ <= right) {
               if (temp[ left_ ] <= temp[ right_ ]) {
                    arreglo[ pos ] = temp[ left_ ];
                    left_++;
               } else {
                    arreglo[ pos ] = temp[ right_ ];
                    right_++;
               }
          } else if (left_ <= medio) {
               arreglo[ pos ] = temp[ left_ ];
               left_++;
          } else if (right_ <= right) {
               arreglo[ pos ] = temp[ right_ ];
               right_++;
          }
          pos++;
     }
}

void Lista::MergeSort(int left,int right){
	if (left< right) {
          int medio = (left+ right) / 2;
          MergeSort(  left, medio );
          MergeSort(  medio + 1 , right );
          Merge(  left, medio , right );
    }
}
///*SORTS*


///ITERATIVE SORTS
void Lista::Iterative_QuickSort(int ini, int fin){
	Num *stack=(Num *) malloc(sizeof(Num) * (ListSize));
	int top=-1;
	stack[++top]=ini;
	stack[++top]=fin;
	while(top>=0){
		
		fin=stack[top--];
		ini=stack[top--];
		 
		int p=partition(ini,fin,3);
		if(p - 1 > ini){
			stack[++top] = ini;
			stack[++top] = p - 1;
		}
		if(p + 1 < fin){
			stack[++top] = p + 1;
			stack[++top] = fin;
		}
	}
}

void Lista::Iterative_MergeSort(){
    for (int i = 1; i <= ListSize-1 ; i *= 2)
    {
        for (int j = 0; j < ListSize-1; j += 2 * i)
        {
        	int medio = j + i -1;
        	int fin_ = min(j + 2 * i - 1 , ListSize - 1);
            Merge( j, medio , fin_);
        }
    }
}

///*ITERATIVE SORTS

#endif 
