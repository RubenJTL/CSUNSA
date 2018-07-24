#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>


#define RANDOM_RANGE 31


using namespace std;

typedef double Num;
 
string convert_to_binary(int,int);
int convert_to_decimal(string);


Num function(int , int);
Num function(int);


typedef struct {
	Num x1;
	Num x2;
	Num deltha1;
	Num deltha2;	
	Num aptitud;
}Individuo;



struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////comparador para maxheap de hijos

struct Comp1
{
   bool operator()(tuple<string,int,Num>& s1, tuple<string,int,Num>& s2)
   {
       return get<2>(s1) < get<2>(s2);
   }
}; ////comparador para maxheap de hijos




class genetico{
public:
	
	genetico(int poblacion);
	genetico(int poblacion,int cromosomas,int iteraciones,Num cross, Num mutacion, int punto);
	void run();
	void mostrar_poblacion();
	void mostrar_poblacion_e();
	void mostrar_poblacion_e_r();
	void mostrar_hijos_e();
	void reproducir();
	bool Mutar(tuple<string>&,Num);
	void new_generation();
	tuple<bool,tuple<string,int,Num>> crear_hijo(tuple<string>,Num);
	void save();

	vector<tuple<string>> CrossOver(int,int);

	int buscar_rangos(Num);


	vector<Individuo> I;

	Num mutacion=0.5;
	int iteraciones=10;
	int cromosomas=5;
	int punto;
	int poblacion;
	Num prob_cross=0.9; 
	Num aptitud;
	Num * porcentaje;
	Num * rangos;
	vector<tuple<string,int,Num>> hijos;

};

void genetico::run(){
	cout<<"Tamanho de la poblacion: "<<this->poblacion<<endl;
	cout<<"Tamanho de los cromosomas: "<<this->cromosomas<<endl;
	cout<<"Cantidad de iteraciones: "<<this->iteraciones<<endl;
	cout<<"Cruzamiento de punto: Punto "<<this->punto<<endl;
	cout<<"Probabilidad de cruzamiento"<<this->prob_cross<<endl;
	cout<<"Probabilidad de mutacion: "<<this->mutacion<<endl<<"Mutacion Simple"<<endl<<endl;
	for (int i = 0; i < this->iteraciones; ++i)
   	{
   		if(i==0){
   			cout<<endl<<"Generando Poblacion Inicial"<<endl;
   		}
   		mostrar_poblacion();
   		cout<<endl<<"Iteracion: "<<i<<endl;
   		cout<<endl<<"Evaluando individuos "<<endl;
   		mostrar_poblacion_e();
   		cout<<endl<<"Selecion de individuos - Metodo de la Ruleta "<<endl;
   		mostrar_poblacion_e_r();
   		

	    reproducir();
	    cout<<endl<<"Seleccionando Siguiente Poblacion"<<endl;
	    mostrar_poblacion_e();
	    mostrar_hijos_e();
	    		    
	    new_generation();
	    
	    cout<<endl;
	    //a.save();
		//}	
   	}

   	cout<<endl<<"Ultima Poblacion"<<endl;
   	mostrar_poblacion();
}


genetico::genetico(int poblacion){
	this->poblacion=poblacion;
	aptitud=0;
	Individuo I1;
	//make_heap(hijos.begin(), hijos.end(), Comp());
	porcentaje=(Num *) malloc(sizeof(Num) * poblacion); 
	rangos=(Num *) malloc(sizeof(Num) * poblacion); 
	//I = (Individuo *) malloc(sizeof(Individuo) * (poblacion*2));
	for(unsigned i=0;i<poblacion;++i){
		

		I1.genotipo=rand() % RANDOM_RANGE;
		I1.cromosomas=convert_to_binary(I1.genotipo,cromosomas);
		I1.aptitud=function(I1.genotipo);
		aptitud+=I1.aptitud;
		I.push_back(I1);
	}
	for(unsigned i=0;i<poblacion;++i){
		porcentaje[i]=(I[i].aptitud)/aptitud;
		if(i==0){
			rangos[i]=0+porcentaje[i];
		}else{
			rangos[i]=rangos[i-1]+porcentaje[i];
		}
	}
	this->punto=(I[0].cromosomas.length())/2;
}


genetico::genetico(int poblacion,int cromosomas,int iteraciones,Num cross ,Num mutacion,int punto){
	this->poblacion=poblacion;
	this->iteraciones=iteraciones;
	this->mutacion=mutacion;
	this->cromosomas=cromosomas;
	this->punto=punto;
	this->prob_cross=cross;
	aptitud=0;
	Individuo I1;
	string tam="";
	for (int i = 0; i < this->cromosomas; ++i)
	{
		tam+="1";
	}

	//make_heap(hijos.begin(), hijos.end(), Comp());
	
	porcentaje=(Num *) malloc(sizeof(Num) * poblacion); 
	rangos=(Num *) malloc(sizeof(Num) * poblacion); 
	//I = (Individuo *) malloc(sizeof(Individuo) * (poblacion*2));
	for(unsigned i=0;i<poblacion;++i){
		

		I1.genotipo=rand() % convert_to_decimal(tam);
		I1.cromosomas=convert_to_binary(I1.genotipo,cromosomas);
		I1.aptitud=function(I1.genotipo);
		aptitud+=I1.aptitud;
		I.push_back(I1);
	}
	for(unsigned i=0;i<poblacion;++i){
		porcentaje[i]=(I[i].aptitud)/aptitud;
		if(i==0){
			rangos[i]=0+porcentaje[i];
		}else{
			rangos[i]=rangos[i-1]+porcentaje[i];
		}
	}
}
/*
void genetico::save(){
	char* stri=(char*)"puntos.dat";
	
	ofstream myfile (stri);//, std::ios_base::app
    for(unsigned i=0;i<poblacion;++i){
		myfile <<(I[i]).genotipo[0] <<"\t";
		myfile <<(I[i]).genotipo[1] <<"\t";    		
		myfile <<setprecision(20) <<(I[i]).aptitud<<"\t";
    	myfile <<"\n";
    }   
    myfile.close();
}*/

vector<tuple<string>> genetico::CrossOver(int pos1,int pos2){
	vector<tuple<string>> CromosomasXY(2);
	int pos=punto;
	string X1="", X2="", Y1="", Y2="";
	for(unsigned i=0; i<pos; ++i){
		X1+=((I[pos2]).cromosomas)[i];
		X2+=((I[pos1]).cromosomas)[i];
	}
	for(unsigned i=pos; i<I[pos1].cromosomas.length(); ++i){
		X1+=((I[pos1]).cromosomas)[i];
		X2+=((I[pos2]).cromosomas)[i];
	}
	CromosomasXY[0]=make_tuple(X1);
	CromosomasXY[1]=make_tuple(X2);
	
	return CromosomasXY;
}
tuple<bool,tuple<string,int,Num>> genetico::crear_hijo(tuple<string> CromosomasXY,Num randomc){
	bool muto=Mutar(CromosomasXY,randomc);
	int CromosomaX=convert_to_decimal( get<0>(CromosomasXY) );
	Num fit=function(CromosomaX);
	auto hijo=make_tuple( get<0>(CromosomasXY), CromosomaX, fit );
	hijos.push_back(hijo); //push_heap ( hijos.begin(), hijos.end(), Comp());
	//std::sort (hijos.begin(), hijos.end(), Comp());
	return make_tuple(muto,hijo);
}

bool genetico::Mutar(tuple<string> &cromosoma, Num alpha1){
	
	int randomp1;
	if(this->mutacion>=alpha1){
		randomp1=rand()%(get<0>(cromosoma)).length();
		if(get<0>(cromosoma)[randomp1]=='1'){
			get<0>(cromosoma)[randomp1]='0';
		}else{
			get<0>(cromosoma)[randomp1]='1';
		}
		return true;
	}
	return false;
	
}

void genetico::new_generation(){
	aptitud=0;
	int t=1;
	unsigned j=0,l=hijos.size()-1;
	if(hijos.size()!=0){
	while(t==1 ){
		if(l<=0 or j>=I.size()){
			t=0;
		}		
			
		else if(I[j].aptitud<get<2>(hijos[l])){
			I[j].genotipo=get<1>(hijos[l]);
			I[j].cromosomas=get<0>(hijos[l]);
			I[j].aptitud=get<2>(hijos[l]);
		}
		l--;
		j++;	
		
	}
	}
	for (unsigned i=0; i<poblacion; ++i) {
	    aptitud+=I[i].aptitud;
	}
	for(unsigned i=0;i<poblacion;++i){
		porcentaje[i]=(I[i].aptitud)/aptitud;
		if(i==0){
			rangos[i]=0+porcentaje[i];
		}else{
			rangos[i]=rangos[i-1]+porcentaje[i];
		}
	}
	hijos.clear();
}

void genetico::mostrar_poblacion(){
	cout<<endl;
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")"<<I[i].cromosomas<<"\t"<< I[i].genotipo<<endl;
	}
	
}

void genetico::mostrar_poblacion_e(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")"<<I[i].cromosomas<<"\t"<< I[i].genotipo<<endl;;
	}
	
}

void genetico::mostrar_poblacion_e_r(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")"<<I[i].cromosomas<<"\t"<< I[i].genotipo<<"\t";
		cout<<porcentaje[i]<<endl;//"\t"<<rangos[i]<<endl;
	}
	
}

void genetico::mostrar_hijos_e(){
	for(unsigned i=0;i<hijos.size();++i){
		cout<<poblacion+1+i<<")"<<get<0>(hijos[i])<<"\t"<< get<1>(hijos[i])<<endl;
	}
}

void genetico::reproducir(){
	Num random1,random2,random_cross;
	int pos1,pos2;
	vector<tuple<string>> CromosomasXY;
	Num randomc;
	
	for (unsigned i = 0; i < poblacion/2; ++i)
	{
		random1=(Num)(rand()%100)/100.0;
		pos1=buscar_rangos(random1);//retorna la pocision
		//cout<<"HOla"<<endl;
		random2=(Num)(rand()%100)/100.0;
		pos2=buscar_rangos(random2);//retorna la pocision 
		while(pos2==pos1){
			random2=(Num)(rand()%100)/100.0;
			pos2=buscar_rangos(random2);//retorna la pocision 

		}
		random_cross=(Num)(rand()%100)/100.0;

		cout<<endl<<"Padre: "<<pos1<<endl<<"Madre: "<<pos2<<endl;
		
		cout<<endl<<"Cruzamiento"<<endl;
		if(prob_cross>=random_cross){	
			CromosomasXY=CrossOver(pos1,pos2);
			//CromosomasXY2=CrossOver(pos2,pos1);
			randomc=(Num)(rand()%100)/100.0;	
			auto muto=crear_hijo(CromosomasXY[0],randomc);
			if(get<0>(muto)==true){
				cout<<"muto hijo 1"<<endl;
				cout<<get<0>(get<1>(muto))<<endl;
			}else{
				cout<<get<0>(get<1>(muto))<<endl;
			}
			randomc=(Num)(rand()%100)/100.0;
			muto= crear_hijo(CromosomasXY[1],randomc);	
			if(get<0>(muto)==true){
				cout<<"muto hijo 2"<<endl;
				cout<<get<0>(get<1>(muto))<<endl;
			}else{
				cout<<get<0>(get<1>(muto))<<endl;
			}
		}
	}
	std::sort (hijos.begin(), hijos.end(), Comp1());
	std::sort (I.begin(), I.end(),Comp());
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();
	
}

int genetico::buscar_rangos(Num numero){
	for(int i = 0; i<poblacion; ++i){
		if(i==0){
			if(rangos[i]>numero && numero>=0){
				return i;
			}
		}
		else if(rangos[i]>numero && rangos[i-1]<=numero){
			return i;
		}
	}
}


Num function(int x ){
	return(pow(x,2));
	//return((((-1)*pow(x,2))/10)+(3*x));
}

string convert_to_binary(int a,int cromosomas){
	string bin="";
	unsigned int var = (unsigned int)a;
    unsigned int contador, inicio = pow(2,cromosomas-1); // 2^(8-1) = 128

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
