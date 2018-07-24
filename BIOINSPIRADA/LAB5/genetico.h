#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef double Num;
typedef int terminales; 
/*typedef struct {
	vector<int> datos;
	int aptitud;
}Individuo;

*/

class Nodo{
	
public:
	Nodo();
	Nodo(Nodo* nodito);
	string tipo;
	Nodo* hijos[2];
	terminales valor;
	string operador;
};

Nodo::Nodo(){
	tipo="";
	hijos[0]=NULL;
	hijos[1]=NULL;
	operador="";
}


Nodo::Nodo(Nodo* nodito){
	tipo=nodito->tipo;
	if(tipo=="Operador"){
		operador=nodito->operador;
		hijos[0]=new Nodo(nodito->hijos[0]);
		hijos[1]=new Nodo(nodito->hijos[1]);
	}
	else if(tipo=="Constante"){
		valor=nodito->valor;
		hijos[0]=NULL;
		hijos[1]=NULL;
	}else if(tipo=="Variable"){
		hijos[0]=NULL;
		hijos[1]=NULL;
	}	
}


/*
struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud > s2.aptitud;
   }
}; ////comparador para maxheap de hijos

struct Comp1
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////*/
struct Comp
{
   bool operator()(tuple<Nodo*,Num>& s1, tuple<Nodo*,Num>& s2)
   {
       return get<1>(s1) > get<1>(s2);
   }
}; ////

struct Comp1
{
   bool operator()(tuple<int,Num>& s1, tuple<int,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////


struct Comp2
{
   bool operator()(tuple<Nodo*,Num>& s1, tuple<Nodo*,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////


class genetico{
public:

	genetico(int poblacion,vector<double> &entradas,vector<double> &salidas,vector<string> &operadores);
	Nodo* generar_individuos();
	void generar_individuos(Nodo* &nodito,int num);
	Nodo* generar_Nodos(int ver_que_sera);
	bool mutar(Nodo* nodo);
	void cruzamiento(int pos1, int pos2);
	void reproducir(Nodo* nodo);


	Num generar_aptitud(Nodo* tmp);
	Num generar_aptitud(Nodo* tmp,Num Variable);

	int buscar_ganador();

	void mostrar_arbol_funcion();
	void mostrar_arbol_funcion(Nodo*);

	void mostrar_arbolH_funcion();
	void mostrar_arbolH_funcion(Nodo*);
	//Num error(vector<double> Yout);

	void run();
	int poblacion;

	vector<tuple<Nodo*,Num>> Individuo;
	vector<tuple<Nodo*,Num>> hijos;

	vector<double> entradas;	
	vector<double> salidas;

	vector<string> operadores;
	int limite=5;
	int participantes=4;
	int iteraciones=100;
};

void genetico::run(){
	for (int i = 0; i < iteraciones; ++i)
	{
		cout<<"ITERACION "<<i<<endl;
		cout<<"poblacion inicial"<<endl;
		mostrar_arbol_funcion();
		
		while(hijos.size()<2*poblacion){
			cout<<endl<<"Participantes Padre"<<endl;
			int pos1=buscar_ganador();//retorna la pocision
			//cout<<"HOla"<<endl;
			Num random_type=(Num)(rand()%100)/100.0;
			if(random_type>=0 and random_type<0.05){
				Nodo* newNodito=new Nodo(get<0>(Individuo[pos1]));
				reproducir(newNodito);
			}else if(random_type>=0.05 and random_type<0.85){
				cout<<endl<<"Participantes Madre"<<endl;
				int pos2=buscar_ganador();//retorna la pocision 
				while(pos2==pos1){
					cout<<endl<<"Participantes Madre"<<endl;
					pos2=buscar_ganador();//retorna la pocision 
				}
				cruzamiento(pos1,pos2);

			}else{
			

			//cout<<pos1<<endl;
			//cout<<endl;
			//mostrar_arbol_funcion();
			//cout<<endl;
			//mostrar_arbol_funcion(get<0>(Individuo[pos1]));
			//for (int k = 0; k < poblacion/2; ++k)
			//{
				Nodo* newNodito=new Nodo(get<0>(Individuo[pos1]));
					
				//mostrar_arbolH_funcion(newNodito);
				//cout<<endl;
				mutar(newNodito);
				//cout<<endl<<"AQUI SUPER"<<endl;

				Num aptitud=generar_aptitud(newNodito);
				hijos.push_back(make_tuple(newNodito,aptitud));
			}	
		}
		
		std::sort (hijos.begin(), hijos.end(),Comp2());
		std::sort (Individuo.begin(), Individuo.end(),Comp());
		


		mostrar_arbol_funcion();
		mostrar_arbolH_funcion();
		for(int j=0;j<poblacion;j++){
			Individuo[j]=hijos[j];
		}
	/*	
	int j=0;
		bool t=true;
		while(j<hijos.size() and j<Individuo.size() and t==true ){
			if(get<1>(Individuo[j])>get<1>(hijos[j])){
				Individuo[j]=hijos[j];
				j++;
			}else{
				t=false;
			}
			
		}*/
		hijos.clear();

	}
	cout<<endl<<"ULTIMA ITERACION"<<endl;
	mostrar_arbol_funcion();
}

void genetico::cruzamiento(int pos1, int pos2){
	Nodo * nodo1= new Nodo(get<0>(Individuo[pos1]));
	Nodo * nodo2= new Nodo(get<0>(Individuo[pos2]));

	if(nodo1->hijos[1] and nodo2->hijos[0] ){
		Nodo* tmp= new Nodo(nodo1->hijos[1]);
		nodo1->hijos[1]=new Nodo(nodo2->hijos[0]);
		nodo2->hijos[0] =new Nodo(tmp);	
	}


		Num aptitud1=generar_aptitud(nodo1);
		Num aptitud2=generar_aptitud(nodo2);
	hijos.push_back(make_tuple(nodo1,aptitud1));
	hijos.push_back(make_tuple(nodo2,aptitud2));
}

void genetico::reproducir(Nodo* nodo){
	Num aptitud=generar_aptitud(nodo);
	hijos.push_back(make_tuple(nodo,aptitud));
}


bool genetico::mutar(Nodo* nodo){
	if(nodo){
	//	cout<<"AQUIIII"<<endl;
		Num random_muta;
		random_muta=(Num)(rand()%100)/100.0;
		if(random_muta>=0.5){
			if(nodo->tipo=="Operador"){
				int random_pos=(int)(rand())/((int)RAND_MAX/operadores.size());
				while(nodo->operador==operadores[random_pos]){
					random_pos=(int)(rand())/((int)RAND_MAX/operadores.size());
				}
				nodo->operador=operadores[random_pos];
			}else if(nodo->tipo=="Constante" ){
				string tipo="Constante";
				terminales valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
				Num random_signo=(Num)(rand()%100)/100.0;
				if(random_signo<0.5){
					valor=valor*(-1);
				}
				nodo->tipo=tipo;
				nodo->valor=valor;
			}else{
				string tipo="Variable";
				nodo->tipo=tipo;
				
			}
			return true;
		}else{
			bool prueba=false;
			if(nodo->hijos[0]){
				prueba=mutar(nodo->hijos[0]);
			}
			if(prueba==false){
				if(nodo->hijos[1])
					prueba=mutar(nodo->hijos[1]);
			}
			return prueba;
		}
	}
	return false;

}



void genetico::mostrar_arbolH_funcion(){
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<poblacion+i+1<<") ";
		mostrar_arbol_funcion(get<0>(hijos[i]));
		cout<<"\t\t\t\t"<<get<1>(hijos[i])<<endl;
	}
}


void genetico::mostrar_arbolH_funcion(Nodo* nodo){
	
	if(nodo and nodo->tipo=="Operador"){
		cout<<"(";
		cout<<nodo->operador<<" ";
		mostrar_arbol_funcion(nodo->hijos[0]);
		mostrar_arbol_funcion(nodo->hijos[1]);
		cout<<")";
	}else if(nodo and nodo->tipo=="Constante"){
		cout<<nodo->valor<<" ";
	}else if(nodo and nodo->tipo=="Variable"){
		cout<<"x ";
	}
	
}


void genetico::mostrar_arbol_funcion(Nodo* nodo){
	
	if(nodo and nodo->tipo=="Operador"){
		cout<<"(";
		cout<<nodo->operador<<" ";
		mostrar_arbol_funcion(nodo->hijos[0]);
		mostrar_arbol_funcion(nodo->hijos[1]);
		cout<<")";
	}else if(nodo and nodo->tipo=="Constante"){
		cout<<nodo->valor<<" ";
	}else if(nodo and nodo->tipo=="Variable"){
		cout<<"x ";
	}
	
}

Num genetico::generar_aptitud(Nodo* tmp){
	vector<double> Yout;
	Num sum=0;
	for (int i = 0; i < entradas.size(); ++i)
	{
		Yout.push_back(generar_aptitud(tmp,entradas[i]));
	}
	
	for (int i = 0; i < Yout.size(); ++i)
	{
		sum+= abs(salidas[i]-Yout[i]);
	}
/*
	for (int i = 0; i < Yout.size(); ++i)
	{
		sum+= pow(salidas[i]-Yout[i],2);
	}*/
	return sum;
}

Num genetico::generar_aptitud(Nodo* tmp,Num Variable){
	if(tmp->tipo=="Variable"){
		return Variable;
	}else if(tmp->tipo=="Constante"){
		return tmp->valor;
	}else if(tmp->tipo=="Operador"){
		//sNum primervalor=
		if(tmp->operador=="+"){
			return (generar_aptitud(tmp->hijos[0])+generar_aptitud(tmp->hijos[1]));
		}else if(tmp->operador=="-"){
			return (generar_aptitud(tmp->hijos[0])-generar_aptitud(tmp->hijos[1]));
		}else if(tmp->operador=="*"){
			return (generar_aptitud(tmp->hijos[0])*generar_aptitud(tmp->hijos[1]));
		}else if(tmp->operador=="/"){
			return (generar_aptitud(tmp->hijos[0])/generar_aptitud(tmp->hijos[1]));
		}else if(tmp->operador=="%"){
			return (fmod (generar_aptitud(tmp->hijos[0]) , generar_aptitud(tmp->hijos[1])));
		}
	}
}

void genetico::mostrar_arbol_funcion(){
	for (int i = 0; i < Individuo.size(); ++i)
	{
		cout<<i+1<<") ";
		mostrar_arbol_funcion(get<0>(Individuo[i]));
		cout<<"\t\t\t\t"<<get<1>(Individuo[i])<<endl;
	}
}

genetico::genetico(int poblacion,vector<double> &entradas,vector<double> &salidas,vector<string> &operadores){
	this->poblacion=poblacion;
	this->entradas=entradas;
	this->salidas=salidas;
	this->operadores=operadores;
	for (int i = 0; i < poblacion; ++i)
	{
		Nodo* tmp=generar_individuos();
		Num aptitud_tmp=generar_aptitud(tmp);
		Individuo.push_back(make_tuple(tmp,aptitud_tmp));
	}
	
}
Nodo* genetico::generar_individuos(){
	int nivel=0;
	Nodo* root;
	generar_individuos(root,nivel);
	return root;
}

void genetico::generar_individuos(Nodo* &nodito,int num){
	if(num==){
		nodito=generar_Nodos(0);
	}else{
		nodito=generar_Nodos(1);
		if(nodito->tipo=="Operador"){
			generar_individuos(nodito->hijos[0],num+1);
			generar_individuos(nodito->hijos[1],num+1);
		
		}
	}
}

Nodo* genetico::generar_Nodos(int ver_que_sera){
	Nodo* newNodo=new Nodo();
	string tipo;
	Num valor;
	string operador;
	if(ver_que_sera==0){
		Num random_tipo;
		random_tipo=(Num)(rand()%100)/100.0;
		if(random_tipo<0.5 and random_tipo>=0){
			tipo="Constante";
			terminales valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
			Num random_signo=(Num)(rand()%100)/100.0;
			if(random_signo<0.5){
				valor=valor*(-1);
			}
			newNodo->tipo=tipo;
			newNodo->valor=valor;
		}else{
			tipo="Variable";
			newNodo->tipo=tipo;
		}
	}else{
		Num random_tipo;
		random_tipo=(Num)(rand()%100)/100.0;
		if(random_tipo<0.77 and random_tipo>=0.34){
			tipo="Constante";
			terminales valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
			Num random_signo=(Num)(rand()%100)/100.0;
			if(random_signo<0.5){
				valor=valor*(-1);
			}
			newNodo->tipo=tipo;
			newNodo->valor=valor;
		}else if(random_tipo<0.34 and random_tipo>=0){
			tipo="Operador";
			int random_pos=(int)(rand())/((int)RAND_MAX/operadores.size());
			operador=operadores[random_pos];
			newNodo->tipo=tipo;
			newNodo->operador=operador;
		}else{
			tipo="Variable";
			newNodo->tipo=tipo;
		}
	}
	return newNodo;
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
		auto s=make_tuple(selec,get<1>(Individuo[selec]));
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp1());
	


	for (int i = 0; i < seleccionados.size(); ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}

	return (get<0>(seleccionados[0]));
}

#endif	
