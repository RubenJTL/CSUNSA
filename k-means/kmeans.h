#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <math.h>

#include <limits>/// MAXIMO DOUBLE
#include <cstddef>
#include <cfloat>


#define RANDOM_RANGE 8192

using namespace std;

typedef double Num;
typedef tuple<Num,Num> punto;
typedef vector<punto> puntos;
typedef vector<Num> distancias;

Num distancia(punto, punto);
Num distancia(puntos);



class kmeans
{
public:
	kmeans(int);
	kmeans(int,int);
	kmeans(string,int);


	void mostrar();
	void mostrar_centros();
	void mostrar_distancias();
	void run();
	void clasificar();
	void cambiar_centros();
	void save();
	void load(string);
	//~kmeans();

	puntos ps1;
	int cantidad;
	int k;
	vector<distancias> dist;
	vector<int> cluster;
	puntos centros;
};

kmeans::kmeans(int puntos){
	cantidad=puntos;
	vector<int > cl(puntos);
	srand(time(NULL));
	for(unsigned i=0 ; i <puntos; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		ps1.push_back(punto);
	}
	cluster=cl;
}

kmeans::kmeans(string p, int k){
	this->k = k;
	load(p);
}

kmeans::kmeans(int puntos,int k){
	cantidad=puntos;
	vector<distancias> distmp(puntos);
	vector<int> clustmp(puntos);
	this->k=k;
	srand(time(NULL));
	for(unsigned i=0 ; i <puntos; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		ps1.push_back(punto);
	}
	for(unsigned i=0 ; i <k; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		centros.push_back(punto);
	}
	dist=distmp;
	cluster=clustmp;
}

void kmeans::load(string puntos){
    ifstream f(puntos.c_str());
    Num x,y;
    f >> cantidad;
    for (unsigned i = 0; i < cantidad; ++ i){
    		f >> x;
    		f >> y;
    		cout<<x<<"  "<<y<<endl;
    		auto punto = make_tuple((Num)x,(Num)y);
            ps1.push_back(punto);
    }
    vector<distancias> distmp(cantidad);
	vector<int> clustmp(cantidad);

	for(unsigned i=0 ; i <k; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		centros.push_back(punto);
	}
	dist=distmp;
	cluster=clustmp;
}

void kmeans::save(){
	char* stri=(char*)"puntos.dat";
	char* clus=(char*)"num.dat";
	ofstream myfile1 (clus);//, std::ios_base::app
	myfile1 <<cantidad;
    myfile1.close();


	ofstream myfile (stri);//, std::ios_base::app
	for(unsigned i=0; i<cantidad; ++i){
		myfile <<setprecision(20);
		myfile <<get<0>(ps1[i])<<"\t";
		myfile <<get<1>(ps1[i])<<"\t";
		myfile <<cluster[i];
		myfile <<"\n";
	}
    myfile.close();
}

void kmeans::cambiar_centros(){
	vector<Num> sumx(k); 
	vector<Num> sumy(k);
	vector<Num> contador(k);
	for(unsigned i=0; i<cantidad; ++i){
		sumx[cluster[i]]+= get<0>(ps1[i]);
		sumy[cluster[i]]+= get<1>(ps1[i]);
		contador[cluster[i]]+=1;
	}
	for(unsigned i=0; i<k; ++i){
		sumx[i]= sumx[i]/contador[i];
		sumy[i]= sumy[i]/contador[i];
		auto t=make_tuple(sumx[i],sumy[i]);
		centros[i]=t;

	}
}

void kmeans::run(){
	distancias d;
	dist.clear();
	for(unsigned j=0; j<k ; ++j){
		for(unsigned i=0; i<cantidad ; ++i){
			d.push_back(distancia(ps1[i],centros[j]));
		}
		dist.push_back(d);
		d.clear();
	}
	clasificar();

}

void kmeans::clasificar(){
	Num menor;
	int pos;
	for(unsigned j=0; j<cantidad ; ++j){
		menor=DBL_MAX;
		for(unsigned i=0; i<k ; ++i){
			if(dist[i][j]<menor){
				menor=dist[i][j];
				pos=i;
			}
		}
		cluster[j]=pos;
	}
}



void kmeans::mostrar(){
	for(unsigned i=0; i<cantidad; ++i){
		cout<<get<0>(ps1[i])<<"\t"<<get<1>(ps1[i])<<"\t"<<cluster[i]<<endl;
	}
}

void kmeans::mostrar_centros(){
	for(unsigned i=0; i<k; ++i){
		cout<<get<0>(centros[i])<<"  "<<get<1>(centros[i])<<endl;
	}
}

void kmeans::mostrar_distancias(){
	for(unsigned j=0; j<cantidad; ++j){
		for(unsigned i=0; i<k; ++i){
			cout<<dist[i][j]<<"  ";
		}
		cout<<endl;
	}
}

Num distancia(punto a, punto b){
	return sqrt(pow(get<0>(a)-get<0>(b),2)+pow(get<1>(a)-get<1>(b),2));
}

#endif
