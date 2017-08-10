#include <iostream>
#include <vector>
#include "ordenacion.h"


typedef vector<Num> List;


using namespace std;

List merge(Num *,Num*,int,int);
void print(List);
void printS(int);

//		void InsertSort();
//		void BubbleSort();
//		void SelectSort();
//		void SelectSort2();
//		void BrickSort();
//		void ShakerSort();


int main(){
	Lista list1(30);
	cout<<"LISTA A"<<endl;	
	list1.print();
	
	cout<<"LISTA A"<<endl;	
	list1.QuickSort2(0,list1.ListSize-1);	
	list1.print();	
	
	///ordena pares ascendente impares descendente
	
	//list2.QuickSort(0,list2.ListSize-1,2); ///forma recursiva de QS
	//list2.Iterative_QuickSort(0,list2.ListSize-1,2); ///forma iterativa de QS
	//list2.MergeSort(0,list2.ListSize); /// forma recursiva del merge
	//list2.Iterative_MergeSort();/// forma itertiva del merge
	//cout<<list2.SQuickSort(5,0,list2.ListSize-1)<<endl;///Imprime el numero en la posicion 5 no ordena completamente la lista;
	
	//printS(list2.BinarySearch(10));
	


}

void print(List list){
	for(unsigned i=0;i<list.size();++i){
		cout<<list[i]<<" ";
	}
	cout<<endl;
}

void printS(int S){
	if(S>=0){
		cout<<"El numero esta en la posicion "<<S+1<<endl;
	}
	else{
		cout<<"No existe el numero en el arreglo"<<endl;
	}
}

List merge(Num* list1,Num* list2,int size1,int size2){
	int i=0,j=0,l=0;
	List list;
	if(list1[i]<list2[j]){list.push_back(list1[i]);i++;}
	else{list.push_back(list2[j]);j++;}
	while(i<size1 or j<size2 ){
		if(i<size1 and j<size2){
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
		else if(i<size1){
			if(list1[i-1] != list1[i] and  list[l] != list1[i] ) {
				list.push_back(list1[i]);l++;
			}i++;
		}
		else if(j<size2){
			if(list2[j-1] != list2[j]  and list[l] != list2[j] ){
				list.push_back(list2[j]);l++;
			}j++;
		}
	}
	return list;	
}
