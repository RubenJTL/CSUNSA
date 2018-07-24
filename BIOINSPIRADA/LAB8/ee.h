#ifndef EE_H
#define EE_H

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

class EE
{
public:
	EE(int poblacion,Num lim_inf,Num lim_sup);
	//~EE();
	void mutacion();
	void mostrar_poblacion();
	void mostrar_hijos();
	double new_poblacion();

	void run();

	vector<Individuo> individuos;
	vector<Individuo> hijos;
	int poblacion;
	Num lim_inf=-2.048;
	Num lim_sup=2.048;
	Num liminf=-100;
	Num limsup=100;
	Num desviacion;
	Num delta=0.001;
	int iteraciones=100;
};

void EE::run(){
	//std::sort (individuos.begin(), individuos.end(), Comp());
	//mostrar_poblacion();

	int i=0;
	Num ps;
	for (int i = 0; i < 500; ++i){
	//do{	
		cout<<individuos[0].x1<<" "<<individuos[0].x2<<" "<<individuos[0].deltha1<<" "<<individuos[0].deltha2<<" "<<individuos[0].aptitud<<endl;
		cout<<endl<<"ITERACION: "<<i<<endl;
		mutacion();
		//cout<<"hola";
		ps=new_poblacion();
		cout<<endl<<"Poblacion"<<endl;
	//	mostrar_poblacion();
	//	i++;
		if(i%5==0){
			//for (int j = 0; j < poblacion; ++i)
			//{
				if (ps<0.2)
				{
					for (int k = 0; k <individuos.size() ; ++k)
					{
						individuos[k].deltha1=individuos[k].deltha1*0.817;
						individuos[k].deltha2=individuos[k].deltha2*0.817;
					}
				}else if (ps>0.2)
				{
					for (int k = 0; k <individuos.size() ; ++k)
					{
						individuos[k].deltha1=individuos[k].deltha1/0.817;
						individuos[k].deltha2=individuos[k].deltha2/0.817;
					}
				}
			//}
		}
	}//while(individuos[poblacion-1].aptitud>=-0.99999 and i<iteraciones);
	cout<<endl<<"ULTIMA POBLACION"<<endl;
	//std::sort (individuos.begin(), individuos.end(), Comp());
	//mostrar_poblacion();
	cout<<individuos[0].x1<<" "<<individuos[0].x2<<" "<<individuos[0].deltha1<<" "<<individuos[0].deltha2<<" "<<individuos[0].aptitud<<endl;
	cout<<endl<<"El mejor resultado es: "<<individuos[0].aptitud<<endl;
}

double EE::new_poblacion(){
	//std::sort (hijos.begin(), hijos.end(), Comp());
	Num succes=0,failer=0;
	cout<<endl<<"Hijos"<<endl;
		cout<<hijos[0].x1<<" "<<hijos[0].x2<<" "<<hijos[0].deltha1<<" "<<hijos[0].deltha2<<" "<<hijos[0].aptitud<<endl;
		//mostrar_hijos();
	//std::sort (individuos.begin(), individuos.end(), Comp());
	for (int i = 0; i < poblacion; ++i)
	{
		if(individuos[i].aptitud<hijos[i].aptitud){
			individuos[i]=hijos[i];
			succes++;
		}
		else{
			failer++;
		}
	}
	hijos.clear();
	return (succes/(succes+failer));
}

void EE::mutacion(){
	Individuo hijo;
	Num aleatorio1;
	Num aleatorio2;
	//for (int i = 0; i < poblacion; ++i){
	int i=0;

	while(individuos.size()>=hijos.size()){
		hijo.deltha1=individuos[i].deltha1;
		hijo.deltha2=individuos[i].deltha2;
		hijo.x1=individuos[i].x1;
		hijo.x2=individuos[i].x2;
		
		aleatorio1=(Num)(rand()%100)/100.0;
		aleatorio2=(Num)(rand()%100)/100.0;
		hijo.x1=hijo.x1+valor_x(liminf,limsup,hijo.deltha1,aleatorio1,delta);
		hijo.x2=hijo.x2+valor_x(liminf,limsup,hijo.deltha2,aleatorio2,delta);
		//cout<<i<<" "<<hijo.x1<<" "<<hijo.x2<<" "<<lim_inf<<" "<<lim_sup<<endl;
		hijo.aptitud=funcion(hijo.x1,hijo.x2);
		if(hijo.x1<=lim_sup and hijo.x1>=lim_inf and hijo.x2<=lim_sup and hijo.x2>=lim_inf){
			//if(hijos)
			hijos.push_back(hijo);
			//i++;
		//	cout<<i<<endl;
		}
			
	}
}

void EE::mostrar_hijos(){
	cout<<endl;
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<hijos[i].x1<<"\t"<<hijos[i].x2<<"\t"<<hijos[i].deltha1<<"\t"<<hijos[i].deltha2<<"\t"<<hijos[i].aptitud<<endl;
	}
}

void EE::mostrar_poblacion(){
	cout<<endl;
	for (int i = 0; i < individuos.size(); ++i)
	{
		cout<<individuos[i].x1<<"\t"<<individuos[i].x2<<"\t"<<individuos[i].deltha1<<"\t"<<individuos[i].deltha2<<"\t"<<individuos[i].aptitud<<endl;
	}
}

EE::EE(int poblacion,Num lim_if,Num lim_sup){
	//this->lim_sup=lim_sup;
	//this->lim_inf=lim_inf;
	//cout<<this->lim_inf;
	this->poblacion=poblacion;
	//this->desviacion=desviacion;
	Individuo I1;
	Num aleatorio1;
	Num aleatorio2;	
	//for (int i = 0; i < poblacion ; ++i)
	while(poblacion>=individuos.size())
	{
		I1.deltha1=(Num)(rand()%100)/100.0;
		I1.deltha2=(Num)(rand()%100)/100.0;
		aleatorio1=(Num)(rand()%100)/100.0;
		aleatorio2=(Num)(rand()%100)/100.0;
		I1.x1=valor_x(liminf,lim_sup,I1.deltha1,aleatorio1,delta);
		I1.x2=valor_x(liminf,lim_sup,I1.deltha2,aleatorio2,delta);		
		I1.aptitud=funcion(I1.x1,I1.x2);
		if(I1.x1<=lim_sup and I1.x1>=lim_inf and I1.x2<=lim_sup and I1.x2>=lim_inf){
			//if(hijos)
			individuos.push_back(I1);
			//i++;
		//	cout<<i<<endl;
		}

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
	//return (-1*cos(x1)*cos(x2)*exp(-1*pow(x1-M_PI,2)-pow(x2-M_PI,2)));
	return (100*pow(pow(x1,2)-x2,2)+pow(1-x1,2));
}
#endif	