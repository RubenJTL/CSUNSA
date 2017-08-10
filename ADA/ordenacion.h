#ifndef ORDENACION_H
#define ORDENACION_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef double Num;

void swap(Num & a,Num & b){
	Num aux;
	aux=a;
	a=b;
	b=aux;
}
class Lista{
	public:
		Lista();
		Lista(Num dimension);
		
		///SORTS
		void IntercambioSort();
		void InsertSort();
		void BubbleSort();
		void SelectSort();
		void SelectSort2();
		void BrickSort();
		void ShakerSort();
		void ShellSort();
		void QuickSort(int, int);
		void QuickSort2(int, int);
		void QuickSortP(int, int);
		void QuickSortI(int, int);
		int partition(int,int,int);
		void Merge(int , int , int);
		void MergeSort(int ,int );
		void copy(const Lista &);

		///SEARCH
		int BinarySearch(Num); //return la posicion


		///DISPLAY
		void print();


		Num 	ListSize=0;
		Num * 	arreglo;
	/*	~Lista() { 
                delete arreglo;
        		cout<<"~B()"<<endl;
    	}*/
};



Lista::Lista(){}

Lista::Lista(Num dimension){
	srand(time(NULL));
	ListSize	=	dimension;
	arreglo		=	(Num *) malloc(sizeof(Num) * dimension);
	for(unsigned i=0;i<dimension;++i){
		arreglo[i]=rand()% (int)dimension+1;

	}
}

void Lista::copy( const Lista & other ) {
	  ListSize = other.ListSize;
      arreglo = (Num *) malloc(sizeof(Num) * other.ListSize);
      memcpy (arreglo, other.arreglo, ListSize *sizeof(Num*));
      //arreglo = new Num(*other.arreglo); 
      
     
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
		print();
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
		print();
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
		print();
	}	
}

void Lista::IntercambioSort(){
	
	for(unsigned i=0;i<ListSize-1;++i){
		for(unsigned j=i+1;j<ListSize;++j){
			if(arreglo[i]>arreglo[j]){
				swap(arreglo[i],arreglo[j]);
			}
		}	
		print();	
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
	//cout<<pos<<endl;
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
		if(pos%2==0){
			if(pos+1<fin)	pos++;
		}
		cout<<pos<<endl;
		piv = arreglo[ pos ];
		cout<< piv<<endl;
		while(true){
			while(arreglo[i]<piv and i<=j){
				i+=2;
			}
			while(arreglo[j]>piv and i<=j){
				j-=2;
			}
			if(i<j){
				swap(arreglo[i],arreglo[j]);
				i+=2;
				j-=2;
			}
			else{
				return j;
			}
		}
	}
}

void Lista::QuickSort(int ini,int fin){
	if(ini<fin){
		print();
		int p=partition(ini,fin,2);
		QuickSort(ini,p);
		QuickSort(p+1,fin);
	}
}

void Lista::QuickSort2(int ini,int fin){
		QuickSortI(ini,fin-1);
		//QuickSortP(ini+1,fin-1);
}


void Lista::QuickSortI(int ini,int fin){
	if(fin%2!=0)
		fin--;
	if(ini%2!=0)
		ini++;
	int i = ini, j = fin;
	int pos = ( ini + fin) / 2 ;
	//cout<<i<<j<<endl;
	Num piv = arreglo[ pos ];
	//cout<<piv<<endl;
	while( i < j ){
		while( arreglo[i] < piv ){
			i+=2;
			
		}
		cout<<"i"<<i<<endl;
		while( piv < arreglo[ j ] ){
			j-=2;
		}
		cout<<"j"<<j<<endl;
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

void Lista::QuickSortP(int ini,int fin){
	int i = ini, j = fin;
	Num piv = arreglo[ ( ini + fin) / 2 ];
	do{
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
	}while( i <= j );
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

///*SORTS*


#endif 
