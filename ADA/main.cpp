#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ordenacion.h"

using namespace std;

/* void IntercambioSort();
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
*/

int main(){

    int iteraciones=5;
    int tam=10;



    Lista List(tam);
    Lista listmp(0);
    clock_t t;
    float tiempo;
        cout<<"BubbleSort :"<<endl;   
       for(int i=0;i<iteraciones;i++)
       {
            listmp.copy(List);
            //listmp.print();
            t = clock();
           listmp.BubbleSort();
           t = clock() - t;
            cout<<endl;
        }
            
       //  double tiempo=(((double)t)/(double(total)*(double(CLOCKS_PER_SEC))));//tiempo en segundos
          //print(list1);
        tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
        cout<<"Tiempo promedio: "<<tiempo<<endl;

        cout<<"InsertSort :"<<endl;   
       for(int i=0;i<iteraciones;i++)
       {
            listmp.copy(List);
           // listmp.print();
            t = clock();
           listmp.InsertSort();
           t = clock() - t;
           cout<<endl;
        }
            
       //  double tiempo=(((double)t)/(double(total)*(double(CLOCKS_PER_SEC))));//tiempo en segundos
          //print(list1);
        tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
        cout<<"Tiempo promedio: "<<tiempo<<endl;

        cout<<"IntercambioSort :"<<endl;   
       for(int i=0;i<iteraciones;i++)
       {
            listmp.copy(List);
            //listmp.print();
            t = clock();
           listmp.IntercambioSort();
           t = clock() - t;
           cout<<endl;
        }
            
       //  double tiempo=(((double)t)/(double(total)*(double(CLOCKS_PER_SEC))));//tiempo en segundos
          //print(list1);
        tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
        cout<<"Tiempo promedio: "<<tiempo<<endl;

        cout<<"SelectSort :"<<endl;   
       for(int i=0;i<iteraciones;i++)
       {
            listmp.copy(List);
            //listmp.print();
            t = clock();
           listmp.SelectSort();
           t = clock() - t;
           cout<<endl;
        }
            
       //  double tiempo=(((double)t)/(double(total)*(double(CLOCKS_PER_SEC))));//tiempo en segundos
          //print(list1);
        tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
        cout<<"Tiempo promedio: "<<tiempo<<endl;

        cout<<"QuickSort :"<<endl;   
       for(int i=0;i<iteraciones;i++)
       {
            listmp.copy(List);
            //listmp.print();
            t = clock();
           listmp.QuickSort(0,listmp.ListSize-1);
           t = clock() - t;
           cout<<endl;
        }
            
       //  double tiempo=(((double)t)/(double(total)*(double(CLOCKS_PER_SEC))));//tiempo en segundos
          //print(list1);
        tiempo=(((float)t)/(float)CLOCKS_PER_SEC);
        cout<<"Tiempo promedio: "<<tiempo<<endl;



    //listmp.copy(List);
    //List.print();
    //listmp.BubbleSort();
    //listmp.print();
    //cout<<endl;
/*
    listmp.copy(List);
    List.print();
    listmp.IntercambioSort();
    listmp.print();
    cout<<endl;

    listmp.copy(List);
    List.print();
    listmp.InsertSort();
    listmp.print();
    cout<<endl;

    listmp.copy(List);
    List.print();
    listmp.SelectSort();
    listmp.print();
    cout<<endl;

    listmp.copy(List);
    List.print();
    listmp.QuickSort(0,listmp.ListSize-1);
    listmp.print();
    cout<<endl;
*/
}
