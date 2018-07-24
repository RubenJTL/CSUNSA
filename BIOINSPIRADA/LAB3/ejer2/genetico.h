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

typedef struct {
	vector<int> datos;
	int aptitud;
}Individuo;



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
}; ////
struct Comp2
{
   bool operator()(tuple<int,int>& s1, tuple<int,int>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////


class genetico{
public:
	genetico(vector<vector<int>> & matriz,int poblacion);
	void run();
	int generar_aptitud(vector<int>);
	void mostrar_poblacion();
	void mostrar_hijos();
	void mostrar_individuo(Individuo);
	void mutacion(Individuo &a);
	void reproducir();
	int buscar_ganador();
	void new_generation();
	void crear_hijos(tuple<Individuo,Individuo>);
	tuple<Individuo,Individuo> cross_OBX(int,int);
	tuple<Individuo,Individuo> cross_PBX(int,int);
	tuple<Individuo,Individuo> cross_PMX(int,int);
	tuple<Individuo,Individuo> cross_CX(int,int);


	int poblacion;
	int punto1=3;
	int punto2=5;
	int participantes=3;
	int Iteracion=2;
	int tc=3;
	int puntopmx1=1;
	int puntopmx2=4;
	Num prob_cross=0.9;
	Num pro_mut=0.5;
	vector<std::vector<int>> matrix;	
	vector<Individuo> hijos;
	vector<Individuo> individuos;
};
void genetico::run(){
	cout<<"POBLACION: "<<poblacion<<endl;
	cout<<"Mutacion simple"<<endl;
	cout<<"Iteraciones: "<<Iteracion<<endl;
	cout<<"Probabilidad de mutacion: "<<pro_mut<<endl;
	cout<<"Probabilidad de Cruzamiento: "<<prob_cross<<endl;
	cout<<"Seleccion por competencia, competidores: "<<participantes<<endl;
	cout<<"Puntos en el caso de PMX: P1: "<<puntopmx1<<"P2: "<<puntopmx2<<endl;
	for(int i=0;i<Iteracion;i++){
		if(i==0){
			cout<<"poblacion Inicial"<<endl;
		}
		cout<<"Iteracion "<<i<<endl;
		mostrar_poblacion();
	    cout<<endl;

	    reproducir();
	    new_generation();
    }
    cout<<"Poblacion Final"<<endl;
    mostrar_poblacion();
}

void genetico::new_generation(){
	bool t=true;
	int i=0,j=0;
	while(t==true){
		if(individuos[i].aptitud>hijos[j].aptitud){
			individuos[i]=hijos[j];
			i++;j++;
		}else{
			t=false;
		}
	}
	hijos.clear();
}

void genetico::crear_hijos(tuple<Individuo,Individuo> a){
	hijos.push_back(get<0>(a));
	hijos.push_back(get<1>(a));
}

tuple<Individuo,Individuo> genetico::cross_CX(int a, int b){
	//srand(time(NULL));
	Individuo h1;
	Individuo h2;
	//h1=individuos[a];
	//h2=individuos[b];
	std::vector<int> h1s;
	std::vector<int> h2s;
	//vector<int> marcados;
	Num random_cross;
	//cout<<"HOLA1"<<endl;
	mostrar_individuo(individuos[a]);
	mostrar_individuo(individuos[b]);
	cout<<endl;
	//cout<<"HOLA"<<endl;
	for(int i=0;i<individuos[a].datos.size();i++){
		h1s.push_back(-1);
		h2s.push_back(-1);
	}
	int i=0;
	auto it = find (h1s.begin(), h1s.end(), individuos[b].datos[i]);
	do
	{
		it = find (h1s.begin(), h1s.end(), individuos[b].datos[i]);
		h1s[i]=individuos[a].datos[i];
		h2s[i]=individuos[b].datos[i];
		int pos1 = std::find(individuos[a].datos.begin(), individuos[a].datos.end(),individuos[b].datos[i]) - individuos[a].datos.begin();
		i=pos1;
	}
	while(it == h1s.end());

	for(int i=0;i<h1s.size();i++){
		if(h1s[i]==-1){
			h1s[i]=individuos[b].datos[i];
			h2s[i]=individuos[a].datos[i];
		}
	}
	h1.datos=h1s;
	h1.aptitud=0;
	h2.datos=h2s;
	h2.aptitud=0;
	mostrar_individuo(h1);
	mostrar_individuo(h2);
	auto r=make_tuple(h1,h2);
	return r;
}

tuple<Individuo,Individuo> genetico::cross_PMX(int a, int b){
	//srand(time(NULL));
	Individuo h1;
	Individuo h2;
	//h1=individuos[a];
	//h2=individuos[b];
	std::vector<int> h1s;
	std::vector<int> h2s;
	//vector<int> marcados;
	Num random_cross;
	//cout<<"HOLA1"<<endl;
	mostrar_individuo(individuos[a]);
	mostrar_individuo(individuos[b]);
	cout<<endl;
	//cout<<"HOLA"<<endl;
	for(int i=0;i<individuos[a].datos.size();i++){
		h1s.push_back(individuos[a].datos[i]);
		h2s.push_back(individuos[b].datos[i]);
	}
	for(int i=puntopmx1-1;i<puntopmx2;i++){
		cout<<endl<<"AQUII "<<endl<<individuos[b].datos[i]<<endl<<endl;
		int pos1 = std::find(h1s.begin(), h1s.end(),h2s[i]) - h1s.begin();
		int pos2 = std::find(h2s.begin(), h2s.end(),h1s[i]) - h2s.begin();
		if( pos1 < h1s.size() and pos2 < h2s.size()){
			h1s[pos1]=h1s[i];
		  	h2s[pos2]=h2s[i];
		  	swap(h1s[i],h2s[i]);
		}
	}
	h1.datos=h1s;
	h1.aptitud=0;
	h2.datos=h2s;
	h2.aptitud=0;
	mostrar_individuo(h1);
	mostrar_individuo(h2);
	auto r=make_tuple(h1,h2);
	return r;
}

tuple<Individuo,Individuo> genetico::cross_PBX(int a, int b){
	//srand(time(NULL));
	Individuo h1;
	Individuo h2;
	//h1=individuos[a];
	//h2=individuos[b];
	std::vector<int> h1s;
	std::vector<int> h2s;
	//vector<int> marcados;
	Num random_cross;
	//Num random_mut;
	//cout<<"HOLA1"<<endl;
	mostrar_individuo(individuos[a]);
	mostrar_individuo(individuos[b]);
	cout<<endl;
	//cout<<"HOLA"<<endl;
	for(int i=0;i<individuos[a].datos.size();i++){
		random_cross=(Num)(rand()%100)/100.0;
		cout<<"esto "<<random_cross<<endl;
		if(random_cross>=0.5){
			h1s.push_back(individuos[b].datos[i]);
			h2s.push_back(individuos[a].datos[i]);
		}else{
			h1s.push_back(-1);
			h2s.push_back(-1);
		}
	}
	for(int i=0;i<individuos[a].datos.size();i++){
		auto it = find (h1s.begin(), h1s.end(), individuos[a].datos[i]);
		if (it != h1s.end()){
		}
		else{
			int pos1 = std::find(h1s.begin(), h1s.end(), -1) - h1s.begin();
		    if( pos1 < h1s.size() ){
		    	h1s[pos1]=individuos[a].datos[i];
		    }
		}

		auto it2 = find (h2s.begin(), h2s.end(), individuos[b].datos[i]);
		if (it2 != h2s.end()){
		}
		else{
			int pos2 = std::find(h2s.begin(), h2s.end(), -1) - h2s.begin();
		    if( pos2 < h2s.size() ){
		    	h2s[pos2]=individuos[b].datos[i];
		    }
		}

	}
	h1.datos=h1s;
	h1.aptitud=0;
	h2.datos=h2s;
	h2.aptitud=0;
	mostrar_individuo(h1);
	mostrar_individuo(h2);
	auto r=make_tuple(h1,h2);
	return r;
}

tuple<Individuo,Individuo> genetico::cross_OBX(int a, int b){
	//srand(time(NULL));
	Individuo h1;
	Individuo h2;
	h1=individuos[a];
	h2=individuos[b];
	vector<int> marcados;
	Num random_cross;
	Num random_mut;
	//cout<<"HOLA1"<<endl;
	mostrar_individuo(individuos[a]);
	mostrar_individuo(individuos[b]);
	//cout<<"HOLA"<<endl;
	for(int i=0;i<individuos[a].datos.size();i++){
		random_cross=(Num)(rand()%100)/100.0;
		if(random_cross>=0.5){
			marcados.push_back(i);
		}
	}
	if(marcados.size()>1){
	for(int i=0;i<marcados.size()-1;i++){
		cout<<endl<<marcados[i]<<endl;
		swap(h1.datos[marcados[i]],h1.datos[marcados[i+1]]);
		swap(h2.datos[marcados[i]],h2.datos[marcados[i+1]]);
	}
	}
	mostrar_individuo(h1);
	mostrar_individuo(h2);
	auto r=make_tuple(h1,h2);
	return r;
}

void genetico::reproducir(){
	Num random1,random2,random_cross;
	int pos1,pos2;
	Num randomc;
	Num random_mut;
	tuple<Individuo,Individuo>hijos1;
	for (unsigned i = 0; i < poblacion/2; ++i)
	{
		cout<<endl<<"Participantes Padre"<<endl;
		pos1=buscar_ganador();//retorna la pocision
		//cout<<"HOla"<<endl;
		cout<<endl<<"Participantes Madre"<<endl;
		pos2=buscar_ganador();//retorna la pocision 
		while(pos2==pos1){
			cout<<endl<<"Participantes Madre"<<endl;
			pos2=buscar_ganador();//retorna la pocision 
		}
		random_cross=(Num)(rand()%100)/100.0;
		cout<<endl<<"Padre: "<<pos1+1<<endl<<"Madre: "<<pos2+1<<endl;
		
		cout<<endl<<"Cruzamiento ";
			if(prob_cross>=random_cross	){
				
				if(tc==0){
					cout<<"OBX"<<endl;
					hijos1=cross_OBX(pos1,pos2);	
				}else if(tc==1){
					cout<<"PBX"<<endl;
					hijos1=cross_PBX(pos1,pos2);	
				}else if(tc==2){
					cout<<"PMX"<<endl;
					hijos1=cross_PMX(pos1,pos2);	
				}else if(tc==3){
					cout<<"CX"<<endl;
					hijos1=cross_CX(pos1,pos2);	
				}
				random_mut=(Num)(rand()%100)/100.0;
				cout<<random_mut<<endl;
				//mostrar_individuo(get<0>(hijos1));
				if(random_mut>=pro_mut){
					cout<<"Muto hijo1"<<endl;
					mutacion(get<0>(hijos1));
				//	mostrar_individuo(get<0>(hijos1));
					
				}
				get<0>(hijos1).aptitud=generar_aptitud(get<0>(hijos1).datos);
				mostrar_individuo(get<0>(hijos1));

				random_mut=(Num)(rand()%100)/100.0;
				cout<<random_mut<<endl;
				if(random_mut>=pro_mut){
					cout<<"Muto hijo2"<<endl;
					//mostrar_individuo(get<1>(hijos1));
					mutacion(get<1>(hijos1));
					//mostrar_individuo(get<1>(hijos1));
				}
				get<1>(hijos1).aptitud=generar_aptitud(get<1>(hijos1).datos);
				mostrar_individuo(get<1>(hijos1));
				crear_hijos(hijos1);
			}
			
	}
	std::sort (hijos.begin(), hijos.end(), Comp1());
	std::sort (individuos.begin(), individuos.end(),Comp());
	mostrar_poblacion();
	mostrar_hijos();
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();	
}

int genetico::buscar_ganador(){
	std::vector<tuple<int,int>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->poblacion);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,int>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->poblacion);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,int>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,(individuos[selec]).aptitud);
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp2());
	


	for (int i = 0; i < seleccionados.size(); ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}

	return (get<0>(seleccionados[0]));
}

int genetico::generar_aptitud(vector<int> v){
	int sum=0;
	for (int i = 1; i < v.size(); ++i)
	{
		sum+=matrix[v[i-1]][v[i]];
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum;
}

void genetico::mutacion(Individuo & a){
	int temp=a.datos[punto2-1];
	for (int i = punto2-1; i > punto1-1; --i)
	{
		a.datos[i]=a.datos[i-1];
	}
	a.datos[punto1-1]=temp;
}

genetico::genetico(vector<vector<int>> & matriz,int poblacion){
	
	this->poblacion=poblacion;
	this->matrix=matriz;
	//srand(time(NULL));
	
	for (int i = 0; i < poblacion; ++i)
	{
		Individuo I1;

		int sum=0;
		int j=0;
		while(I1.datos.size()<matrix.size()){
			
			int r2 = (int) (rand()) / (int) (RAND_MAX/matrix.size());	
			auto it = std::find((I1.datos).begin(), (I1.datos).end(), r2);
			while (it != (I1.datos).end()) {
		  		r2 = (int) (rand()) / (int) (RAND_MAX/matrix.size());	
				it = std::find((I1.datos).begin(), (I1.datos).end(),r2);
			}
			(I1.datos).push_back(r2);
		}
		I1.aptitud=generar_aptitud(I1.datos);
		individuos.push_back(I1);
		(I1.datos).clear();

	}
}

void genetico::mostrar_individuo(Individuo a){
	for (int j = 0; j < a.datos.size(); ++j)
	{
		cout<<a.datos[j]<<" ";				
	}
	cout<<"\t"<<a.aptitud<<endl;
}

void genetico::mostrar_hijos(){
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<poblacion+i+1<<")\t";
		for (int j = 0; j < hijos[i].datos.size(); ++j)
		{
			cout<<hijos[i].datos[j]<<" ";				
		}
		cout<<"\t"<<hijos[i].aptitud<<endl;
	}
}

void genetico::mostrar_poblacion(){
	for (int i = 0; i < individuos.size(); ++i)
	{
		cout<<i+1<<")\t";
		for (int j = 0; j < individuos[i].datos.size(); ++j)
		{
			cout<<individuos[i].datos[j]<<" ";				
		}
		cout<<"\t"<<individuos[i].aptitud<<endl;
	}
}

#endif	
