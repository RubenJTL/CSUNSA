#ifndef EVOLUCION_H
#define EVOLUCION_H

#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;


typedef double Num;


typedef struct {
	Num x1;
	Num x2;
	Num deltha1;
	Num deltha2;	
	Num aptitud;
}Individuo;

Num funcion(Num,Num);
Num normal(Num x, Num deviacion);
Num integral(Num lim_inf,Num lim_sup,Num desviacion, Num delta);
Num valor_x(Num lim_inf,Num lim_sup, Num desviacion,Num aleatorio,Num delta);

struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud > s2.aptitud;
   }
}; ////

struct Comp1
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////

class P_evolutiva
{
public:
	P_evolutiva(int poblacion,Num desviacion,Num lim_inf,Num lim_sup);
	//~P_evolutiva();
	void mutacion();
	void mostrar_poblacion();
	void mostrar_hijos();
	void new_poblacion();

	void run();

	vector<Individuo> individuos;
	vector<Individuo> hijos;
	int poblacion;
	Num lim_inf;
	Num lim_sup;
	Num desviacion;
	Num delta=0.01;
	int iteraciones=100;
};

void P_evolutiva::run(){
	mostrar_poblacion();
	int i=0;
	//for (int i = 0; i < 500; ++i){
	do{	
		cout<<endl<<"ITERACION: "<<i<<endl;
		mutacion();
		new_poblacion();
		cout<<endl<<"Poblacion"<<endl;
		mostrar_poblacion();
		i++;
	}while(individuos[poblacion-1].aptitud>=-0.99999 and i<iteraciones);
	cout<<endl<<"ULTIMA POBLACION"<<endl;
	mostrar_poblacion();
}

void P_evolutiva::new_poblacion(){
	std::sort (hijos.begin(), hijos.end(), Comp1());
	cout<<endl<<"Hijos"<<endl;
		mostrar_hijos();
	std::sort (individuos.begin(), individuos.end(), Comp());
	for (int i = 0; i < poblacion; ++i)
	{
		if(individuos[i].aptitud>=hijos[i].aptitud)
			individuos[i]=hijos[i];
		else
			break;
	}
	hijos.clear();
}

void P_evolutiva::mutacion(){
	Individuo hijo;
	Num aleatorio1;
	Num aleatorio2;
	//for (int i = 0; i < poblacion; ++i){
	int i=0;
	while(poblacion>=hijos.size()){
		hijo.deltha1=individuos[i].deltha1;
		hijo.deltha2=individuos[i].deltha2;
		hijo.x1=individuos[i].x1;
		hijo.x2=individuos[i].x2;
		//aleatorio1=(Num)(rand()%100)/100.0;
		//hijo.deltha1=hijo.deltha1*(1+2*valor_x(lim_inf,lim_sup,desviacion,aleatorio1,delta));
		//aleatorio1=(Num)(rand()%100)/100.0;
		//hijo.deltha2=hijo.deltha2*(1+2*valor_x(lim_inf,lim_sup,desviacion,aleatorio1,delta));
		aleatorio1=(Num)(rand()%100)/100.0;
		aleatorio2=(Num)(rand()%100)/100.0;
		hijo.x1=hijo.x1+hijo.deltha1*valor_x(lim_inf,lim_sup,desviacion,aleatorio1,delta);
		hijo.x2=hijo.x2+hijo.deltha2*valor_x(lim_inf,lim_sup,desviacion,aleatorio1,delta);
		hijo.aptitud=funcion(hijo.x1,hijo.x2);
		if(hijo.x1<=10 and hijo.x1>=-10 and hijo.x2<=10 and hijo.x2>=-10){
			hijos.push_back(hijo);
		//	i++;
		//	cout<<i<<endl;
		}
			
	}
}

void P_evolutiva::mostrar_hijos(){
	cout<<endl;
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<hijos[i].x1<<"\t"<<hijos[i].x2<<"\t"<<hijos[i].deltha1<<"\t"<<hijos[i].deltha2<<"\t"<<hijos[i].aptitud<<endl;
	}
}

void P_evolutiva::mostrar_poblacion(){
	cout<<endl;
	for (int i = 0; i < individuos.size(); ++i)
	{
		cout<<individuos[i].x1<<"\t"<<individuos[i].x2<<"\t"<<individuos[i].deltha1<<"\t"<<individuos[i].deltha2<<"\t"<<individuos[i].aptitud<<endl;
	}
}

P_evolutiva::P_evolutiva(int poblacion,Num desviacion,Num lim_if,Num lim_sup){
	this->lim_sup=lim_sup;
	this->lim_inf=lim_inf;
	this->poblacion=poblacion;
	this->desviacion=desviacion;
	Individuo I1;
	Num aleatorio1;
	Num aleatorio2;	
	for (int i = 0; i < poblacion ; ++i)
	{
		I1.deltha1=(Num)(rand()%100)/100.0;
		I1.deltha2=(Num)(rand()%100)/100.0;
		aleatorio1=(Num)(rand()%100)/100.0;
		aleatorio2=(Num)(rand()%100)/100.0;
		I1.x1=valor_x(lim_inf,lim_sup,desviacion,aleatorio1,delta);
		I1.x2=valor_x(lim_inf,lim_sup,desviacion,aleatorio2,delta);		
		I1.aptitud=funcion(I1.x1,I1.x2);
		individuos.push_back(I1);
	}

}

Num normal(Num x, Num desviacion){
	Num retorno=-0.5*((x/desviacion)*(x/desviacion));
	retorno=exp(retorno);
	retorno=retorno/(desviacion*sqrt(M_PI*2));
	return retorno;
}

Num integral(Num lim_inf,Num lim_sup,Num desviacion, Num delta){
	Num area=0;
	Num aux_suma, aux=normal(lim_inf,desviacion);

	for (double i = lim_inf+delta; i < lim_sup; i+=delta)
	{
		aux_suma=normal(i,desviacion);
		area+=(aux+aux_suma);
		aux=aux_suma;
	}
	area*=(delta/2);
	return area;
}

Num valor_x(Num lim_inf,Num lim_sup, Num desviacion,Num aleatorio,Num delta){
	Num area=0;
	Num aux_suma, aux=normal(lim_inf,desviacion);

	for (double i = lim_inf+delta; i < lim_sup; i+=delta)
	{
		aux_suma=normal(i,desviacion);
		area+=(aux+aux_suma);
		if((area*(delta/2))>aleatorio){
			return i;
		}
		aux=aux_suma;
	}
	return -1;//*std::numeric_limits<double>::max();
}

Num funcion(Num x1,Num x2){
	return (-1*cos(x1)*cos(x2)*exp(-1*pow(x1-M_PI,2)-pow(x2-M_PI,2)));

}
#endif	
