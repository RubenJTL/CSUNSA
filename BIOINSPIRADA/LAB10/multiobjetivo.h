#ifndef MULTIOBJETIVO_H
#define MULTIOBJETIVO_H

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

typedef struct
{
	Num x;
	Num y;
	Num objetivo1;
	Num objetivo2;
	int Frontera;
}Individuo;

Num funcion1(Num, Num);
Num funcion2(Num, Num);


Num funcion3(Num,Num);
Num funcion4(Num,Num);

struct Comp1
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
   		if(s1.objetivo1==s2.objetivo1){
   			return s1.objetivo2<s2.objetivo2;
   		}
       	return s1.objetivo1<s2.objetivo1;
   }
}; ////

struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
   		if(s1.objetivo2==s2.objetivo2){
   			return s1.objetivo1<s2.objetivo1;
   		}
       	return s1.objetivo2<s2.objetivo2;
   }
}; ////



struct Comp2
{
   bool operator()(tuple<int,Num,Num> & s1, tuple<int,Num,Num> & s2)
   {
   		if(get<1>(s1)==get<1>(s2)){
   			return get<2>(s1)<get<2>(s2);
   		}
       	return get<1>(s1) < get<1>(s2);
   }
}; ////


class NSGAII
{
public:
	NSGAII(int);
	//~NSGAII();

	void mostrar_poblacion();
	void mostrar_hijos();
	void mostrar_fronteras();

	void cruzamiento();
	void mutacion(Individuo &);

	int buscar_ganador();

	void run();

	int participantes=3;
	int maximoX=5;

	int maximoY=3;
	Num alpha=0.5; 
	int cantidad_poblacion;
	int iteraciones=100;

	vector<Individuo> individuos;
	vector<Individuo> hijos;
	vector<vector<Individuo>> Frontera;
};




void NSGAII::run(){
	std::sort (individuos.begin(), individuos.end(),Comp1());
	cout<<"POBLACION INICIAL: "<<endl;
	mostrar_poblacion();
	for (int l = 0; l < iteraciones; ++l)
	{
	std::sort (individuos.begin(), individuos.end(),Comp1());
	cout<<"ITERACION: "<<l<<endl;
	
	for (int i = 0; i < individuos.size(); ++i)
	{
		hijos.push_back(individuos[i]);
	}
	cruzamiento();
	cout<<hijos.size()<<endl;
	
	cout<<"POBLACION"<<endl;
	cout<<hijos.size()<<endl;
	mostrar_hijos();
	cout<<endl<<endl;
	std::sort (hijos.begin(), hijos.end(),Comp1());
	vector<Individuo> part;
	hijos[0].Frontera=1;
	part.push_back(hijos[0]);
	std::sort (hijos.begin(), hijos.end(),Comp());
	hijos[0].Frontera=1;
	part.push_back(hijos[0]);
	
	std::sort (hijos.begin(), hijos.end(),Comp1());

	Frontera.push_back(part);
	
	///HIJOS
	for (int j = 0; j < Frontera.size(); ++j)
	{
		
		for (int k = 0; k < Frontera[j].size(); ++k)
		{
			/*cout<<j<<" ";
			cout<<Frontera[j].size()<<endl;*/
			for (int i = 0; i < hijos.size(); ++i)
			{
				
				if(hijos[i].Frontera==0){
					if(Frontera[j].size()>1){		
						if (hijos[i].objetivo1>=Frontera[j][k].objetivo1 and hijos[i].objetivo1<=Frontera[j][k+1].objetivo1 and 
							hijos[i].objetivo2<=Frontera[j][k].objetivo2 and hijos[i].objetivo2>=Frontera[j][k+1].objetivo2 )
						{
							hijos[i].Frontera=j+1;
							Frontera[j].push_back(hijos[i]);
							std::sort (Frontera[j].begin(), Frontera[j].end(),Comp1());
							k=0;
						}
					}
				}
			//cout<<endl;		
			}//for k
		}
		//cout<<"HOLA"<<endl;
		std::sort (hijos.begin(), hijos.end(),Comp1());
		part.clear();
		for (int l = 0; l < hijos.size(); ++l)
		{
			if(part.size()!=1){
				if(hijos[l].Frontera==0){
					hijos[l].Frontera=j+2;
					part.push_back(hijos[l]);
				}
			}else{
				break;
			}
		}
		std::sort (hijos.begin(), hijos.end(),Comp());
		for (int l = 0; l < hijos.size(); ++l)
		{
			if(part.size()!=2){
				if(hijos[l].Frontera==0){
					hijos[l].Frontera=j+2;
					part.push_back(hijos[l]);
				}
			}else{
				break;
			}
		}
		if(part.size()>=1)
			Frontera.push_back(part);
			
		//cout<<endl;
	}//for i
	//cout<<endl;
	std::sort (hijos.begin(), hijos.end(),Comp1());
	//mostrar_fronteras();
	//mostrar_poblacion();

	mostrar_hijos();
	individuos.clear();
	for (int i = 0; i < Frontera.size(); ++i)
	{
		for (int j = 0; j < Frontera[i].size(); ++j)
		{
		    if(individuos.size()<cantidad_poblacion){
				Frontera[i][j].Frontera=0;
				individuos.push_back(Frontera[i][j]);
			}
		}
	}
	hijos.clear();
	Frontera.clear();
	cout<<"NUEVA POBLACION"<<endl;
	mostrar_poblacion();
	}
}

void NSGAII::mutacion(Individuo &hijo){
	int randomp,random1;

	//if(this->mutacion>=alpha1){
		randomp=(Num)(rand()%100)/100.0;
		if(randomp>=0.5){
			Num r1 = static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/maximoX));		
			random1=(Num)(rand()%100)/100.0;
			if(random1<0.5){
				r1=r1*(-1);
			}
			hijo.x=r1;
		}else{
			Num r1 = static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/maximoY));		
			random1=(Num)(rand()%100)/100.0;
			if(random1<0.5){
				r1=r1*(-1);
			}
			hijo.y=r1;
		}
	//}
	hijo.objetivo1=funcion1(hijo.x,hijo.y);
	hijo.objetivo2=funcion2(hijo.x,hijo.y);
}

void NSGAII::cruzamiento(){
	Individuo hijo;
	int pos1,pos2;
	while(hijos.size()<cantidad_poblacion*2){
			
			//cout<<endl<<"Participantes Padre"<<endl;
			pos1=buscar_ganador();//retorna la pocision
			//cout<<endl<<"Participantes Madre"<<endl;
			pos2=buscar_ganador();//retorna la pocision 
			while(pos2==pos1){
				//cout<<endl<<"Participantes Madre"<<endl;
				pos2=buscar_ganador();//retorna la pocision 
			}
			Num aleatorio = Num (rand()) / (Num (RAND_MAX/alpha));
			Num al = (Num)(rand()%100)/100.0;
			if(al<0.5){
				aleatorio=aleatorio*-1;
			}
			hijo.x=individuos[pos1].x+aleatorio*(individuos[pos2].x-individuos[pos1].x);
			hijo.y=individuos[pos1].y+aleatorio*(individuos[pos2].y-individuos[pos1].y);
			hijo.objetivo1=funcion1(hijo.x,hijo.y);
			hijo.objetivo2=funcion2(hijo.x,hijo.y);
			hijo.Frontera=0;
			Num aleatorio1=(Num)(rand()%100)/100.0;
			if(aleatorio1<=0.4){
				//cout<<"mutacion"<<endl;
				mutacion(hijo);
			}
			if(0<=hijo.x and hijo.x<=5 and 0<=hijo.y and hijo.y<=3 and 0>=funcion3(hijo.x,hijo.y) and 0>=funcion4(hijo.x,hijo.y)){
				hijos.push_back(hijo);
			}
	}
}

void NSGAII::mostrar_poblacion(){
	for (int i = 0; i < individuos.size(); ++i)
	{
		cout<<individuos[i].x<<"\t"<<individuos[i].y<<"\t"<<individuos[i].objetivo1<<"\t"<<individuos[i].objetivo2<<"\t"<<individuos[i].Frontera<<endl;
	}
}

void NSGAII::mostrar_hijos(){
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<hijos[i].x<<"\t"<<hijos[i].y<<"\t"<<hijos[i].objetivo1<<"\t"<<hijos[i].objetivo2<<"\t"<<hijos[i].Frontera<<endl;
	}
}

void NSGAII::mostrar_fronteras(){
	for (int i = 0; i < Frontera.size(); ++i)
	{
		cout<<"FRONTERA: "<<i<<endl;
		for (int j = 0; j < Frontera[i].size(); ++j)
		{
			cout<<Frontera[i][j].x<<"\t"<<Frontera[i][j].y<<"\t"<<Frontera[i][j].objetivo1<<"\t"<<Frontera[i][j].objetivo2<<"\t"<<Frontera[i][j].Frontera<<endl;
			//cout<<hijos[i].x<<"\t"<<hijos[i].y<<"\t"<<hijos[i].objetivo1<<"\t"<<hijos[i].objetivo2<<"\t"<<hijos[i].Frontera<<endl;
		}
	}	
}

NSGAII::NSGAII(int cantidad_poblacion){
	this->cantidad_poblacion=cantidad_poblacion;
	while(individuos.size()<cantidad_poblacion){
		Individuo I1;
		I1.x = Num (rand()) / (Num (RAND_MAX/maximoX));
		I1.y = Num (rand()) / (Num (RAND_MAX/maximoY));
		
		I1.objetivo1=funcion1(I1.x,I1.y);
		I1.objetivo2=funcion2(I1.x,I1.y);
		//cout<<I1.x<<" "<<I1.y<<""<<I1.objetivo1<<""<<I1.objetivo2<<endl;
		I1.Frontera=0;
		Num aleatorio=(Num)(rand()%100)/100.0;
		
		if(0>=funcion3(I1.x,I1.y) and funcion4(I1.x,I1.y)<=0){
			individuos.push_back(I1);
		}
	}
}

int NSGAII::buscar_ganador(){
	std::vector<tuple<int,Num,Num>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->cantidad_poblacion);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num,Num>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->cantidad_poblacion);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num,Num>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,(individuos[selec]).objetivo1,(individuos[selec]).objetivo2);
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp2());
	

/*
	for (int i = 0; i < participantes; ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}
*/
	return (get<0>(seleccionados[participantes-1]));
}

Num funcion1(Num x, Num y){
	return 4*pow(x,2)+4*pow(y,2);
}

Num funcion2(Num x, Num y){
	return pow(x-5,2)+pow(y-5,2);
}

Num funcion3(Num x, Num y){
	return pow(x-5,2)+pow(y,2)-25;
}

Num funcion4(Num x, Num y){
	return -1*pow(x-8,2)-pow(y+3,2)+7.7;
}
#endif	
