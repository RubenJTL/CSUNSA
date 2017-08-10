#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>


#define RANDOM_RANGE 8192


using namespace std;

typedef double Num;
 
string convert_to_binary(int);
int convert_to_decimal(string);


Num function(int , int);


struct Comp
{
   bool operator()(tuple<string,string,int,int,Num>& s1, tuple<string,string,int,int,Num>& s2)
   {
       return get<4>(s1) < get<4>(s2);
   }
}; ////comparador para maxheap de hijos


typedef struct {
	string cromosomas[2];
	int fenotipo[2];
	Num fitness;
}Individuo;


class genetico{
public:
	genetico(int poblacion);
	void mostrar_poblacion();
	void mostrar_hijos();
	void reproducir();
	void Mutar();
	void new_generation();
	void crear_hijo(tuple<string,string>);
	void save();

	vector<tuple<string,string>> CrossOver(int,int);

	int buscar_rangos(Num);


	Individuo *I;


	int poblacion; 
	Num fitness;
	Num * porcentaje;
	Num * rangos;
	vector<tuple<string,string,int,int,Num>> hijos;

};

genetico::genetico(int poblacion){
	this->poblacion=poblacion;
	fitness=0;
	//make_heap(hijos.begin(), hijos.end(), Comp());
	srand(time(NULL));
	porcentaje=(Num *) malloc(sizeof(Num) * poblacion); 
	rangos=(Num *) malloc(sizeof(Num) * poblacion); 
	I = (Individuo *) malloc(sizeof(Individuo) * poblacion);
	for(unsigned i=0;i<poblacion;++i){
		I[i].fenotipo[0]=rand() % RANDOM_RANGE;
		I[i].cromosomas[0]=convert_to_binary(I[i].fenotipo[0]);
		I[i].fenotipo[1]=rand() % RANDOM_RANGE;
		I[i].cromosomas[1]=convert_to_binary(I[i].fenotipo[1]);
		I[i].fitness=function(I[i].fenotipo[0],I[i].fenotipo[1]);
		fitness+=I[i].fitness;
	}
	for(unsigned i=0;i<poblacion;++i){
		porcentaje[i]=(I[i].fitness)/fitness;
		if(i==0){
			rangos[i]=0+porcentaje[i];
		}else{
			rangos[i]=rangos[i-1]+porcentaje[i];
		}
	}
}

void genetico::save(){
	char* stri=(char*)"puntos.dat";
	
	ofstream myfile (stri);//, std::ios_base::app
    for(unsigned i=0;i<poblacion;++i){
		myfile <<(I[i]).fenotipo[0] <<"\t";
		myfile <<(I[i]).fenotipo[1] <<"\t";    		
		myfile <<setprecision(20) <<(I[i]).fitness<<"\t";
    	myfile <<"\n";
    }   
    myfile.close();
}

vector<tuple<string,string>> genetico::CrossOver(int pos1,int pos2){
	vector<tuple<string,string>> CromosomasXY(2);
	int pos=(I[pos1].cromosomas[0].length())/2;
	string X1="", X2="", Y1="", Y2="";
	for(unsigned i=0; i<pos; ++i){
		X1+=((I[pos2]).cromosomas[0])[i];
		X2+=((I[pos1]).cromosomas[0])[i];
		Y1+=((I[pos2]).cromosomas[1])[i];
		Y2+=((I[pos1]).cromosomas[1])[i];
	}
	for(unsigned i=pos; i<I[pos1].cromosomas[0].length(); ++i){
		X1+=((I[pos1]).cromosomas[0])[i];
		X2+=((I[pos2]).cromosomas[0])[i];
		Y1+=((I[pos1]).cromosomas[1])[i];
		Y2+=((I[pos2]).cromosomas[1])[i];
	}

	
	CromosomasXY[0]=make_tuple(X1,Y1);
	CromosomasXY[1]=make_tuple(X2,Y2);
	
	return CromosomasXY;
}

void genetico::crear_hijo(tuple<string,string> CromosomasXY){
	int CromosomaX=convert_to_decimal( get<0>(CromosomasXY) );
	int CromosomaY=convert_to_decimal( get<1>(CromosomasXY) );
	Num fit=function(CromosomaX,CromosomaY);
	auto hijo=make_tuple( get<0>(CromosomasXY) , get<1>(CromosomasXY) , CromosomaX , CromosomaY , fit );
	hijos.push_back(hijo); //push_heap ( hijos.begin(), hijos.end(), Comp());
	//std::sort (hijos.begin(), hijos.end(), Comp());
}

void genetico::Mutar(){
	srand(time(NULL));
	Num alpha=0.5;
	int randomp1,randomp2;
	Num randomc;
	for(unsigned i=0; i<poblacion*2; ++i){
		randomc=(Num)(rand()%101)/100.0;
		if(alpha>=randomc){
			randomp1=rand()%(get<0>(hijos[i])).length();
			cout<<randomp1<<"AQTUI"<<endl;
			randomp2=rand()%(get<1>(hijos[i])).length();
			if(get<0>(hijos[i])[randomp1]=='1'){
				get<0>(hijos[i])[randomp1]='0';
			}else{
				get<0>(hijos[i])[randomp1]='1';
			}
			if(get<1>(hijos[i])[randomp2]=='1'){
				get<1>(hijos[i])[randomp2]='0';
			}else{
				get<1>(hijos[i])[randomp2]='1';
			}
			auto s1=get<0>(hijos[i]);
			auto s2=get<1>(hijos[i]);
			auto s3=convert_to_decimal( s1 );
			auto s4=convert_to_decimal( s2 );
			auto s5=function( s3, s4 );
			//hijos.erase(hijos.begin()+(i));  
			auto hijo=make_tuple( s1 , s2 , s3 , s4 , s5 );
			hijos[i]=hijo;// push_heap ( hijos.begin(), hijos.end(), Comp());			
		}
	}
	std::sort (hijos.begin(), hijos.end(), Comp());
	
}

void genetico::new_generation(){
	fitness=0;
	for (unsigned i=0; i<poblacion; ++i) {
	    auto max = hijos.back();
	    hijos.pop_back();  
		I[i].fenotipo[0]=get<2>(max);
		I[i].cromosomas[0]=get<0>(max);
		I[i].fenotipo[1]=get<3>(max);
		I[i].cromosomas[1]=get<1>(max);
		I[i].fitness=get<4>(max);
		fitness+=I[i].fitness;
	}
	for(unsigned i=0;i<poblacion;++i){
		porcentaje[i]=(I[i].fitness)/fitness;
		if(i==0){
			rangos[i]=0+porcentaje[i];
		}else{
			rangos[i]=rangos[i-1]+porcentaje[i];
		}
	}
	hijos.clear();
}

void genetico::mostrar_poblacion(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<I[i].cromosomas[0]<<"\t"<< I[i].fenotipo[0]<<"\t";
		cout<<I[i].cromosomas[1]<<"\t"<< I[i].fenotipo[1]<<"\t";
		cout<<I[i].fitness<<"\t"<<porcentaje[i]<<"\t"<<rangos[i]<<endl;
	}
	
}

void genetico::mostrar_hijos(){
	for(unsigned i=0;i<hijos.size();++i){
		cout<<get<0>(hijos[i])<<"\t"<< get<2>(hijos[i])<<"\t";
		cout<<get<1>(hijos[i])<<"\t"<< get<3>(hijos[i])<<"\t";
		cout<<get<4>(hijos[i])<<endl;
	}
}

void genetico::reproducir(){
	srand(time(NULL));
	Num random1,random2;
	int pos1,pos2;
	vector<tuple<string,string>> CromosomasXY;
	for (unsigned i = 0; i < poblacion; ++i)
	{
		random1=(Num)(rand()%100)/100.0;
		pos1=buscar_rangos(random1);//retorna la pocision
		//cout<<"HOla"<<endl;
		random2=(Num)(rand()%100)/100.0;
		pos2=buscar_rangos(random2);//retorna la pocision 
		CromosomasXY=CrossOver(pos1,pos2);
		//CromosomasXY2=CrossOver(pos2,pos1);
		crear_hijo(CromosomasXY[0]);
		crear_hijo(CromosomasXY[1]);	
	}
	//std::sort (hijos.begin(), hijos.end(), Comp());
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();
	
}

int genetico::buscar_rangos(Num numero){
	for(int i = 0; i<poblacion; ++i){
		if(i==0){
			if(rangos[i]>=numero && numero>=0){
				return i;
			}
		}
		else if(rangos[i]>=numero && rangos[i-1]<numero){
			return i;
		}
	}
}

Num function(int x , int y){
	return((1/(sqrt(2*M_PI)*pow(1500,2) ))*exp(-((pow((x-4096),2) + pow((y-4096),2) ) / (2*pow(1500,2)))));
}

string convert_to_binary(int a){
	string bin="";
	unsigned int var = (unsigned int)a;
    unsigned int contador, inicio = pow(2,13); // 2^(8-1) = 128

    for(contador = inicio; contador > 0; contador >>= 1){ // El contador se desplaza un bit a la derecha cada ciclo
        if(contador & var) // Si contador AND var == 1
            bin+="1";
        else
            bin+="0";
    }
    return bin;
}

int convert_to_decimal(string str){
	int decimal=0;
	int a=str.length()-1;
	for(int i=0;i<str.length();i++){
		switch(str[i]){
			case '1':
				decimal+=1*pow(2,a);
				a--;
				break;
			case '0':
				a--;
				break;
		}
	}
	return decimal;
}




#endif
