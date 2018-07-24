#ifndef PSO_H
#define PSO_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef int Num;


bool iguales(vector<int>& a,std::vector<int > & b){
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i]!=b[i])
		{
			return false;
		}
	}
	return true;
}
void SO(vector<int> & ciudades, tuple<int,int> p){
	swap(ciudades[get<0>(p)],ciudades[get<1>(p)]);
}
vector<int> SS(vector<int> ciudades,vector<tuple<int,int>> p){
	std::vector<int> tmp=ciudades;
	for (int i = 0; i < p.size(); ++i)
	{
		SO(tmp,p[i]);
	}
	return tmp;
}
vector<tuple<int,int>> operator +(const vector<tuple<int,int>>& a, const vector<tuple<int,int>> &b){
	vector<tuple<int,int>> c;
	for (int i = 0; i < a.size(); ++i)
	{
		c.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); ++i)
	{
		c.push_back(b[i]);
	}

	return c;

}
vector<tuple<int,int>> operator -(const vector<int> p1, const std::vector<int> p2){

	vector<tuple<int,int>> r;
	vector<int> tmp=p1;
	vector<int> tmp2=p2;
	while(iguales(tmp,tmp2)==false){
		for (int i = 0; i < tmp.size(); ++i)
		{
			auto it = find(tmp2.begin(), tmp2.end(),tmp[i]);
			if (it != tmp2.end()){
				if((it-tmp2.begin())!=i){
					auto tuple=make_tuple(i,it-tmp2.begin());
					r.push_back(tuple);
					SO(tmp,tuple);
					i=0;
				}
			}
			else{
			    ;//std::cout << "Element not found in myvector\n";			
			}
		}
	}
	//cout<<"HOLAA"<<endl;
	return r;
}




Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}




typedef struct {
	vector<tuple<int,int>> v;
	vector<int> x;
	int fitness;
}Particula;

void mostrar_particula_x(Particula p){
	for (int i = 0; i < p.x.size(); ++i)
	{
		if (p.x[i]==0)
		{
			printf("'A'");
		}
		else if (p.x[i]==1)
		{
			printf("'B'");
		}
		else if (p.x[i]==2)
		{
			printf("'C'");
		}
		else if (p.x[i]==3)
		{
			printf("'D'");
		}
		else if (p.x[i]==4)
		{
			printf("'E'");
		}
		else if (p.x[i]==5)
		{
			printf("'F'");
		}
		else if (p.x[i]==6)
		{
			printf("'G'");
		}
		if (i!=p.x.size()-1)
		{
			printf(", ");
		}
	}
}

void mostrar_particula_v(Particula p){
	for (int i = 0; i < p.v.size(); ++i)
	{
		printf("(%d, %d)",get<0>(p.v[i]), get<1>(p.v[i]));
		if (i!=p.v.size()-1)
		{
			printf(", ");
		}
	}
	//printf("\n");
}

Particula Mejor(vector<Particula> Best){
	Particula X;
	X=Best[0];
	for (int i = 1; i < Best.size(); ++i)
	{
		if (X.fitness>Best[i].fitness)
		{
			X=Best[i];
		}
	}
	return X;
}

class PSO{
public:
	PSO(int iteraciones,vector<vector<int>> & matrix);
	//~PSO();
	void mostrar_particulas();
	void run();
	vector<int> ValorX();
	Num Function(vector<Num> & x);

	Particula gBest;
	Particula lBest;

	vector<vector<int>> Mciudades;

	vector<Particula> particulas;
	vector<Particula> pBest;

	int cantidad_de_iteraciones=2;
	int tam_poblacion=6;
	//int dimensiones=2;
};

Num PSO::Function(vector<Num> & x){
	int sum=0;
	for (int i = 1; i < x.size(); ++i)
	{
		sum+=Mciudades[x[i-1]][x[i]];
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum;
}

vector<int> PSO::ValorX(){
	
	vector<int> ciudad;
	while(ciudad.size()!=Mciudades.size()){
		Num aleatorio=random(Mciudades.size());
		auto it=find (ciudad.begin(), ciudad.end(),aleatorio);
		if (it != ciudad.end()){
			;
		}
		else{
		    ciudad.push_back(aleatorio);//std::cout << "Element not found in myvector\n";			
		}
	}
	return ciudad;
}

void PSO::mostrar_particulas(){
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("Actual: [");
		mostrar_particula_x(particulas[i]);
		printf("]\n");
		printf("Costo Actual: %d \n",particulas[i].fitness);
		
		printf("Actual: [");
		mostrar_particula_x(pBest[i]);
		printf("]\n");
		printf("Costo del Mejor: %d \n",pBest[i].fitness);

		printf("Velocidad: [");
		mostrar_particula_v(particulas[i]);
		printf("]\n\n");
	}

}

void PSO::run(){
	Num w,d1,d2,rand1,rand2;
	
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		printf("Iteracion %d *************\n", iteraciones+1);
		printf("Mejor Global: [");
		mostrar_particula_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %d \n\n",gBest.fitness );
		
		mostrar_particulas();

		w=random(1);
		d1=1.0;
		d2=1.0;
		//rand1=random(1);
		//rand2=random(1);
		for (int i = 0; i < tam_poblacion; ++i)
		{
	
			particulas[i].v=((pBest[i].x)-(particulas[i].x))+(gBest.x - particulas[i].x);
			
			particulas[i].x=SS(particulas[i].x,particulas[i].v);
			particulas[i].fitness=Function(particulas[i].x);
			if (pBest[i].fitness>particulas[i].fitness)
			{
				pBest[i]=particulas[i];
			}
		}

		lBest=Mejor(particulas);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}
		//mostrar_particulas();
	}
		printf("Mejor Global: [");
		mostrar_particula_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %d \n\n",gBest.fitness );
}

PSO::PSO(int iteraciones,vector<vector<int>> & matrix){
	Mciudades=matrix;
	vector<int> ciudad;
	
	//cout<<"HOLa";
	Particula P;
	for (int i = 0; i < tam_poblacion; ++i)
	{
		while(ciudad.size()!=Mciudades.size()){
			Num aleatorio=random(Mciudades.size());
			auto it=find (ciudad.begin(), ciudad.end(),aleatorio);
			if (it != ciudad.end()){
				;
			}
			else{
			    ciudad.push_back(aleatorio);//std::cout << "Element not found in myvector\n";			
			}
		}
		P.x=ciudad;
		P.fitness=Function(P.x);
		particulas.push_back(P);
		pBest.push_back(P);
		ciudad.clear();
		//P.x.clear();
	}
	gBest=Mejor(pBest);
	//mostrar_particula(gBest);
	lBest=Mejor(pBest);
	//mostrar_particula(lBest);
	run();

}	


#endif	