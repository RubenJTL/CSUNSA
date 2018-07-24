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

double ALPHA=1;

Num Error(vector<Num> deseado,vector<Num> obtenido);

class Individuo
{
public:
	Individuo* hijo[2];
	terminales valor;
	string tipo;
	char operador;

	Individuo();
	Individuo(Individuo*);
	~Individuo();
};
Individuo::Individuo(){
	hijo[0]=NULL;
	hijo[1]=NULL;
}
Individuo::Individuo(Individuo* nuevoI){
	this->tipo=nuevoI->tipo;
	hijo[0]=NULL;
	hijo[1]=NULL;
	if(this->tipo=="Operador"){
		this->operador=nuevoI->operador;
		hijo[0]=new Individuo(nuevoI->hijo[0]);
		hijo[1]=new Individuo(nuevoI->hijo[1]);	
	}else if(this->tipo=="Constante"){
		this->valor=nuevoI->valor;
	}
	
}


struct Comp
{
   bool operator()(tuple<Individuo*,Num>& s1, tuple<Individuo*,Num>& s2)
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
   bool operator()(tuple<Individuo*,Num>& s1, tuple<Individuo*,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////


class genetico
{
public:
	genetico(int cantidad,vector<Num> &entradas,vector<Num> &salidas,string operadores);
	//s~genetico();
	

	//genetico(int cantidad,vector<Num> &entradas,vector<Num>salidas,string operadores);
	Individuo* crear_arbol();
	void crear_arbol(Individuo* &root, int hojas);
	void crear_nodo(Individuo* &root, int hojas);
	Num generar_aptitud(Individuo*);
	Num generar_aptitud(Individuo* tmp,Num Variable);



	void reproducir(Individuo*);
	void mutar(Individuo*);
	void cruzamiento(int pos1,int pos2);



	int buscar_ganador();


	void mostrar_individuo(Individuo*);
	void mostrar_individuos();

	void run();

	int cantidad;
	int participantes=3;
	int limite=5;
	vector<Num> entradas;
	vector<Num>salidas;
	vector<tuple<Individuo*,Num>> individuos;
	vector<tuple<Individuo*,Num>> hijos;

	string operadores;
	int total_de_hojas=3;
	int iteraciones=500;

	
};

void genetico::reproducir(Individuo* root){
	Individuo* tmp=new Individuo(root);
	Num aptitud=generar_aptitud(tmp);
	if(aptitud<=ALPHA and aptitud>0 and hijos.size()<cantidad){
		hijos.push_back(make_tuple(tmp,aptitud));
	}
}

void genetico::mutar(Individuo* root){
	Individuo* tmp=new Individuo(root);
	Num random_muta;
	random_muta=(Num)(rand()%100)/100.0;
	if(random_muta>=0.5){
		if(tmp->tipo=="Operador"){
			int random_pos=(int)(rand())/((int)RAND_MAX/operadores.length());
			while(tmp->operador==operadores[random_pos]){
				random_pos=(int)(rand())/((int)RAND_MAX/operadores.length());
			}
			tmp->operador=operadores[random_pos];
		}else if(tmp->tipo=="Constante" ){
			tmp->valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
			Num random_signo=(Num)(rand()%100)/100.0;
			if(random_signo<0.5){
				tmp->valor=tmp->valor*(-1);
			}
		}else{
			tmp->tipo="Variable";
		}
	}
	Num aptitud=generar_aptitud(tmp);
	if(aptitud<=ALPHA and aptitud>0 and hijos.size()<cantidad){
		hijos.push_back(make_tuple(tmp,aptitud));
	}
}

void genetico::cruzamiento(int pos1,int pos2){
	Individuo * nodo1= new Individuo(get<0>(individuos[pos1]));
	Individuo * nodo2= new Individuo(get<0>(individuos[pos2]));

	if(nodo1->hijo[1] and nodo2->hijo[0] ){
		Individuo* tmp= new Individuo(nodo1->hijo[1]);
		nodo1->hijo[1]=new Individuo(nodo2->hijo[0]);
		nodo2->hijo[0] =new Individuo(tmp);	
	}


		Num aptitud1=generar_aptitud(nodo1);
		Num aptitud2=generar_aptitud(nodo2);
	if(aptitud1<=ALPHA and aptitud1>0 and hijos.size()<cantidad){
		hijos.push_back(make_tuple(nodo1,aptitud1));
	}	
	if(aptitud2<=ALPHA and aptitud2>0 and hijos.size()<cantidad){
		hijos.push_back(make_tuple(nodo2,aptitud2));
	}
	
}



void genetico::run(){
	mostrar_individuos();
	for (int i = 0; i < iteraciones; ++i)
	{
		cout<<"ITERACION "<<i<<endl;
		cout<<"poblacion inicial"<<endl;
		mostrar_individuos();
		
		while(hijos.size()<cantidad){
			cout<<endl<<"Participantes Padre"<<endl;
			int pos1=buscar_ganador();//retorna la pocision
			//cout<<"HOla"<<endl;
			Num random_type=(Num)(rand()%100)/100.0;
			if(random_type>=0 and random_type<0.05){
				cout<<"reproduccion"<<endl;
				reproducir(get<0>(individuos[pos1]));
			}else if(random_type>=0.05 and random_type<0.85){
				cout<<"cruzamiento"<<endl;

				cout<<endl<<"Participantes Madre"<<endl;
				int pos2=buscar_ganador();//retorna la pocision 
				while(pos2==pos1){
					cout<<endl<<"Participantes Madre"<<endl;
					pos2=buscar_ganador();//retorna la pocision 
				}
				cruzamiento(pos1,pos2);

			}else{
				cout<<"mutacion"<<endl;
				if(mutar(get<0>(individuos[pos1]));)
					cout<<"el indivio muto "
				
			}	
		}
		
		std::sort (hijos.begin(), hijos.end(),Comp2());
		std::sort (individuos.begin(), individuos.end(),Comp());
		
		for(int j=0;j<this->cantidad;j++){
			individuos[j]=hijos[j];
		}
		hijos.clear();
		ALPHA-=0.00005;
	}
	cout<<endl<<"ULTIMA ITERACION"<<endl;
	mostrar_individuos();

	cout<<"MEJOR RESULTADO"<<endl;
	mostrar_individuo(get<0>(individuos[0]));
}


genetico::genetico(int cantidad,vector<Num> &entradas,vector<Num>&salidas,string operadores){
	this->cantidad=cantidad;
	this->entradas=entradas;
	this->salidas=salidas;
	this->operadores=operadores;
	for (int i = 0; i < cantidad; ++i)
	{
		Individuo *tmp=crear_arbol();
		Num aptitud=generar_aptitud(tmp);
		individuos.push_back(make_tuple(tmp,aptitud));
	}
	
}

Individuo* genetico::crear_arbol(){
	int hojas=1;
	Individuo* root;
	crear_arbol(root,hojas);
	return root;
}

void genetico::crear_arbol(Individuo* &root, int hojas){
	if(hojas<=total_de_hojas){
		crear_nodo(root,hojas);
		if(root->tipo=="Operador"){
			crear_arbol(root->hijo[0],hojas+1);
			crear_arbol(root->hijo[1],hojas+1);
		}
	}
}

void genetico::crear_nodo(Individuo* &root, int hojas){
	root=new Individuo();
	string tipo;
	Num valor;
	string operador;
	if(hojas==1){
		root->tipo="Operador";
		int random_pos=(int)(rand())/((int)RAND_MAX/operadores.length());
		root->operador=operadores[random_pos];
	}else if(hojas==total_de_hojas){
		Num random_tipo;
		random_tipo=(Num)(rand()%100)/100.0;
		if(random_tipo<0.5 and random_tipo>=0){
			root->tipo="Constante";
			root->valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
			Num random_signo=(Num)(rand()%100)/100.0;
			if(random_signo<0.5){
				root->valor=root->valor*(-1);
			}
		}else{
			root->tipo="Variable";
		}
	}else{
		Num random_tipo;
		random_tipo=(Num)(rand()%100)/100.0;
		if(random_tipo<0.77 and random_tipo>=0.34){
			root->tipo="Constante";
			root->valor=(terminales)(rand())/((terminales)RAND_MAX/limite);
			Num random_signo=(Num)(rand()%100)/100.0;
			if(random_signo<0.5){
				root->valor=root->valor*(-1);
			}
		}else if(random_tipo<0.34 and random_tipo>=0){
			root->tipo="Operador";
			int random_pos=(int)(rand())/((int)RAND_MAX/operadores.length());
			root->operador=operadores[random_pos];
		}else{
			root->tipo="Variable";
		}

	}
}

void genetico:: mostrar_individuos(){
	for (int i = 0; i < cantidad; ++i)
	{
		cout<<i+1<<") ";
		mostrar_individuo(get<0>(individuos[i]));
		cout<<"\t\t\t\t\t"<<get<1>(individuos[i])<<endl;
	}
	cout<<endl;
}


void genetico:: mostrar_individuo(Individuo* root){
	if(root->tipo=="Operador"){
		cout<<"(";
		cout<<root->operador<<" ";
		mostrar_individuo(root->hijo[0]);
		mostrar_individuo(root->hijo[1]);
		cout<<")";
	}else if(root->tipo=="Constante"){
		cout<<root->valor<<" ";
	}else{
		cout<<"X ";
	}
}

Num genetico::generar_aptitud(Individuo* tmp){
	vector<double> Yout;
	Num sum=0;
	for (int i = 0; i < entradas.size(); ++i)
	{
		Yout.push_back(generar_aptitud(tmp,entradas[i]));
		
	}
	sum=Error(salidas,Yout);
	return sum;
}

Num genetico::generar_aptitud(Individuo* tmp,Num Variable){
	if(tmp->tipo=="Variable"){
		return Variable;
	}else if(tmp->tipo=="Constante"){
		return tmp->valor;
	}else if(tmp->tipo=="Operador"){
		//sNum primervalor=
		if(tmp->operador=='+'){
			return (generar_aptitud(tmp->hijo[0],Variable)+generar_aptitud(tmp->hijo[1],Variable));
		}else if(tmp->operador=='-'){
			return (generar_aptitud(tmp->hijo[0],Variable)-generar_aptitud(tmp->hijo[1],Variable));
		}else if(tmp->operador=='*'){
			return (generar_aptitud(tmp->hijo[0],Variable)*generar_aptitud(tmp->hijo[1],Variable));
		}else if(tmp->operador=='/'){
			return (generar_aptitud(tmp->hijo[0],Variable)/generar_aptitud(tmp->hijo[1],Variable));
		}else if(tmp->operador=='%'){
			return (fmod (generar_aptitud(tmp->hijo[0],Variable) , generar_aptitud(tmp->hijo[1],Variable)));
		}
	}
}

int genetico::buscar_ganador(){
	std::vector<tuple<int,Num>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->cantidad);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->cantidad);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,get<1>(individuos[selec]));
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp1());
	


	for (int i = 0; i < seleccionados.size(); ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}

	return (get<0>(seleccionados[0]));
}


Num Error(vector<Num> deseado,vector<Num> obtenido){
	Num sum=0;
	for (int i = 0; i < deseado.size(); ++i)
	{
		cout<<deseado[i]<<"\t"<<obtenido[i]<<"\t"<<pow(deseado[i]-obtenido[i],2)<<endl;
		sum+=pow(deseado[i]-obtenido[i],2);

	}
	sum=sum/deseado.size();
	return sum;	
}


#endif	
