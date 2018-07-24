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
	string cromosomas[2];
	int genotipo[2];
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
   bool operator()(tuple<string,int,string,int,Num>& s1, tuple<string,int,string,int,Num>& s2)
   {
       return get<4>(s1) < get<4>(s2);
   }
}; ////

struct Comp2
{
   bool operator()(tuple<int,Num>& s1, tuple<int,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////




class genetico{
public:
	
	genetico(int poblacion,int cromosomas,int iteraciones,Num cross, Num mutacion, int punto1,int punto2,int participantes);
	void run();
	void mostrar_poblacion();
	void mostrar_poblacion_e();
	void mostrar_hijos_e();
	void reproducir();
	bool Mutar(tuple<string,string>&,Num);
	void new_generation();
	tuple<bool,tuple<string,int,string,int,Num>> crear_hijo(tuple<string,string>,Num);
	void save();

	vector<tuple<string,string>> CrossOver(int,int);

	void generar_mask();
	int buscar_ganador();


	vector<Individuo> I;

	Num mutacion=0.5;
	int iteraciones=10;
	int cromosomas=5;
	int participantes=5;
	int poblacion;
	Num prob_cross=0.9; 
	string mask="";
	vector<tuple<string,int,string,int,Num>> hijos;

};

void genetico::run(){
	cout<<"Tamanho de la poblacion: "<<this->poblacion<<endl;
	cout<<"Tamanho de los cromosomas: "<<this->cromosomas<<endl;
	cout<<"Cantidad de iteraciones: "<<this->iteraciones<<endl;
	cout<<"Probabilidad de mutacion: "<<this->mutacion<<endl<<"Mutacion Simple"<<endl<<endl;
	cout<<"Probabilidad de Cruzamiento: "<<this->prob_cross<<endl;
	//buscar_ganador();
	generar_mask();
	cout<<"Mascara de Mutacion: "<<this->mask<<endl;
	for (int i = 0; i < this->iteraciones; ++i)
   	{
   		if(i==0){
   			cout<<endl<<"Generando Poblacion Inicial"<<endl;
   		}
   		mostrar_poblacion();
   		cout<<endl<<"Iteracion: "<<i<<endl;
   		cout<<endl<<"Evaluando individuos "<<endl;
   		mostrar_poblacion_e();
   		cout<<endl<<"Selecion de individuos - Metodo de Enfrentamiento "<<endl;
   		

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
   	mostrar_poblacion_e();
}


genetico::genetico(int poblacion,int cromosomas,int iteraciones,Num cross, Num mutacion,int punto1, int punto2,int participantes){
	this->poblacion=poblacion;
	this->iteraciones=iteraciones;
	this->mutacion=mutacion;
	this->cromosomas=cromosomas;
	this->participantes=participantes;
	this->prob_cross=cross;
	if(this->participantes>this->poblacion){
		this->participantes=poblacion-1;
	}
	Individuo I1;
	string tam="";
	for (int i = 0; i < this->cromosomas; ++i)
	{
		tam+="1";
	}
	
	for(unsigned i=0;i<poblacion;++i){

		I1.genotipo[0]=rand() % RANDOM_RANGE;
		I1.cromosomas[0]=convert_to_binary(I1.genotipo[0],cromosomas);
		I1.genotipo[1]=rand() % RANDOM_RANGE;
		I1.cromosomas[1]=convert_to_binary(I1.genotipo[1],cromosomas);
		
		I1.aptitud=function(I1.genotipo[0],I1.genotipo[1]);
		I.push_back(I1);
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

vector<tuple<string,string>> genetico::CrossOver(int pos1,int pos2){
	vector<tuple<string,string>> CromosomasXY(2);
	string X1="", X2="", Y1="", Y2="";
	for(unsigned i=0; i<I[pos1].cromosomas[0].length(); ++i){
		if(this->mask[i]=='0'){
			X1+=((I[pos2]).cromosomas[0])[i];
			X2+=((I[pos1]).cromosomas[0])[i];
			Y1+=((I[pos2]).cromosomas[1])[i];
			Y2+=((I[pos1]).cromosomas[1])[i];
		}else{
			X1+=((I[pos1]).cromosomas[0])[i];
			X2+=((I[pos2]).cromosomas[0])[i];
			Y1+=((I[pos1]).cromosomas[1])[i];
			Y2+=((I[pos2]).cromosomas[1])[i];
		}
		
	}
	CromosomasXY[0]=make_tuple(X1,Y1);
	CromosomasXY[1]=make_tuple(X2,Y2);
	
	return CromosomasXY;
}
tuple<bool,tuple<string,int,string,int,Num>> genetico::crear_hijo(tuple<string,string> CromosomasXY,Num randomc){
	bool muto=Mutar(CromosomasXY,randomc);
	int CromosomaX=convert_to_decimal( get<0>(CromosomasXY) );
	int CromosomaY=convert_to_decimal( get<1>(CromosomasXY) );
	Num fit=function(CromosomaX,CromosomaY);
	auto hijo=make_tuple( get<0>(CromosomasXY), CromosomaX,get<1>(CromosomasXY), CromosomaY, fit );
	hijos.push_back(hijo); //push_heap ( hijos.begin(), hijos.end(), Comp());
	//std::sort (hijos.begin(), hijos.end(), Comp());
	return make_tuple(muto,hijo);
}

bool genetico::Mutar(tuple<string,string> &cromosoma, Num alpha1){
	
	int randomp1,randomp2;
	if(this->mutacion>=alpha1){
		randomp1=rand()%(get<0>(cromosoma)).length();
		if(get<0>(cromosoma)[randomp1]=='1'){
			get<0>(cromosoma)[randomp1]='0';
		}else{
			get<0>(cromosoma)[randomp1]='1';
		}
		randomp2=rand()%(get<1>(cromosoma)).length();
		if(get<1>(cromosoma)[randomp2]=='1'){
			get<1>(cromosoma)[randomp2]='0';
		}else{
			get<1>(cromosoma)[randomp2]='1';
		}

		return true;
	}
	return false;
	
}

void genetico::new_generation(){
	bool t=true;
	unsigned j=0,l=hijos.size()-1;
	
	if(hijos.size()!=0){
		
	while(j<I.size() and l>0 ){
		cout<<l<<endl;	
		if(I[j].aptitud<get<4>(hijos[l])){
			I[j].genotipo[0]=get<1>(hijos[l]);
			I[j].cromosomas[0]=get<0>(hijos[l]);
			I[j].genotipo[1]=get<3>(hijos[l]);
			I[j].cromosomas[1]=get<2>(hijos[l]);
			I[j].aptitud=get<4>(hijos[l]);
			l--;
			j++;
		}else{
			break;
		}
	}
	}
	hijos.clear();
}

void genetico::mostrar_poblacion(){
	cout<<endl;
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")\t"<<I[i].cromosomas[0]<<"\t"<<I[i].cromosomas[1]<<"\t"<< I[i].aptitud<<endl;
	}
	
}

void genetico::mostrar_poblacion_e(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")\t"<<I[i].cromosomas[0]<<"\t"<< I[i].genotipo[0]<<"\t";
		cout<<I[i].cromosomas[1]<<"\t"<< I[i].genotipo[1]<<"\t"<<I[i].aptitud<<endl;
		
	}
	
}

void genetico::mostrar_hijos_e(){
	for(unsigned i=0;i<hijos.size();++i){
		cout<<poblacion+1+i<<")\t"<<get<0>(hijos[i])<<"\t"<< get<1>(hijos[i])<<"\t";
		cout<<get<2>(hijos[i])<<"\t"<< get<3>(hijos[i])<<"\t"<< get<4>(hijos[i])<<endl;
	}
}

void genetico::reproducir(){
	Num random1,random2,random_cross;
	int pos1,pos2;
	vector<tuple<string,string>> CromosomasXY;
	Num randomc;
	
	for (unsigned i = 0; i < poblacion/2; ++i)
	{
		cout<<endl<<"Particpantes Padre"<<endl;
		pos1=buscar_ganador();//retorna la pocision
		//cout<<"HOla"<<endl;
		cout<<endl<<"Particpantes Madre"<<endl;
		pos2=buscar_ganador();//retorna la pocision 
		while(pos2==pos1){
			cout<<endl<<"Particpantes Madre"<<endl;			
			pos2=buscar_ganador();//retorna la pocision 
		}
		random_cross=(Num)(rand()%100)/100.0;
		cout<<endl<<"Padre: "<<pos1+1<<endl<<"Madre: "<<pos2+1<<endl;
		
		cout<<endl<<"Cruzamiento Uniforme"	<<endl;
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
		}}
	}
	std::sort (hijos.begin(), hijos.end(), Comp1());
	std::sort (I.begin(), I.end(),Comp());
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();
	
}

void genetico::generar_mask(){
	srand (time(NULL));
	Num n;
	for (int i = 0; i < this->cromosomas; ++i)
	 {
	 	
		n =(Num)(rand()%101)/100.0;

		if(1-n>=0.5){
			mask+="1";
		}else{
			mask+="0";
		}
	 } 
}

int genetico::buscar_ganador(){
	std::vector<tuple<int,Num>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->poblacion);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->poblacion);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,(I[selec]).aptitud);
		seleccionados.push_back(s);
	}
	
	for (int i = 0; i < participantes; ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp2());
	

	return (get<0>(seleccionados[participantes-1]));
}


Num function(int x ){
	//return(pow(x,2));
	return((((-1)*pow(x,2))/10)+(3*x));
}

Num function(int x,int y ){
	//return(pow(x,2));
	return(x-y);
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
