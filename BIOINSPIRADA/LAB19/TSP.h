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

bool comparar1(vector<Num> a,vector<Num> b){
//	cout<<a[0]<<" and "<<b[0]<<" and "<<a[1]<<" and "<<b[1]<<endl;
	if (a[0]>b[0] and a[1]<b[1])
	{
//		cout<<"es dominado"<<endl;
		return true;
	}
//	cout<<"no dominado"<<endl;
	return false;
}
bool comparar2(vector<Num> a,vector<Num> b){
//	cout<<a[0]<<" and "<<b[0]<<" and "<<a[1]<<" and "<<b[1]<<endl;
	if (a[0]<b[0] and a[1]>b[1] )
	{
//		cout<<"es dominado"<<endl;
		return true;
	}
//	cout<<"no dominado"<<endl;
	return false;
}
bool comparar3(vector<Num> a,vector<Num> b){
//	cout<<a[0]<<" and "<<b[0]<<" and "<<a[1]<<" and "<<b[1]<<endl;
	if (a[0]>b[0] and a[1]>b[1] )
	{
//		cout<<"es dominado"<<endl;
		return true;
	}
	if (a[0]<b[0] and a[1]>b[1] )
	{
//		cout<<"es dominado"<<endl;
		return true;
	}
	if (a[0]>b[0] and a[1]<b[1])
	{
//		cout<<"es dominado"<<endl;
		return true;
		
	}
//	cout<<"no dominado"<<endl;
	return false;
}

bool comparar(vector<Num> a,vector<Num> b){
//	cout<<a[0]<<" and "<<b[0]<<" and "<<a[1]<<" and "<<b[1]<<endl;
	if (a[0]<b[0] and a[1]>b[1] )
	{
//		cout<<"es dominado"<<endl;
		return true;
	}
	else if (a[0]>b[0] and a[1]<b[1])
	{
//		cout<<"es dominado"<<endl;
		return true;
		
	}
//	cout<<"no dominado"<<endl;
	return false;
}

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
	vector<int> fitness;

}Particula;

bool myfunctionx (Particula i,Particula j) { return (i.fitness[0]<j.fitness[0]); }
bool myfunctiony (Particula i,Particula j) { return (i.fitness[1]<j.fitness[1]); }

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
		else if (p.x[i]==7)
		{
			printf("'H'");
		}
		else if (p.x[i]==8)
		{
			printf("'I'");
		}
		else if (p.x[i]==9)
		{
			printf("'J'");
		}
		else if (p.x[i]==10)
		{
			printf("'K'");
		}
		else if (p.x[i]==11)
		{
			printf("'L'");
		}
		else if (p.x[i]==12)
		{
			printf("'M'");
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
	PSO(vector<vector<Num>> & matriz,vector<vector<Num>> & matriz2);
	//~PSO();
	void mostrar_particulas();
	void mostrar_MPG();
	void actualizar();
	void run();

	int generar_aptitud1(vector<Num> v);
	int generar_aptitud2(vector<Num> v);
	

	vector<int> ValorX();
	Num Function(vector<Num> & x);

	Particula gBest;
	Particula lBest;

	vector<Particula> MPG;
	vector<Particula> particulas;
	vector<Particula> pBest;
	vector<std::vector<int>> matrixdis;
	vector<std::vector<int>> matrixcos;	

	int cantidad_de_iteraciones=50;
	int tam_poblacion=20;
	//int dimensiones=2;
};




Num PSO::Function(vector<Num> & x){
	int sum=0;
	for (int i = 1; i < x.size(); ++i)
	{
		sum+=matrixdis[x[i-1]][x[i]];
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum;
}

vector<int> PSO::ValorX(){
	
	vector<int> ciudad;
	while(ciudad.size()!=matrixdis.size()){
		Num aleatorio=random(matrixdis.size());
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

void PSO::actualizar(){
	std::vector<Particula> tMPG;
	std::sort (MPG.begin(), MPG.end(), myfunctionx);
	tMPG.push_back(MPG.front());
	std::sort (MPG.begin(), MPG.end(), myfunctiony);
	tMPG.push_back(MPG.front());

	for (int i = 0; i < MPG.size(); ++i)
	{
		for (int j = 1; j < tMPG.size(); ++j)
		{
			if (MPG[i].fitness[0]>tMPG[j-1].fitness[0] and MPG[i].fitness[0]<tMPG[j].fitness[0] and MPG[i].fitness[1]<tMPG[j-1].fitness[1] and MPG[i].fitness[1]>tMPG[j].fitness[1])
			{
				tMPG.push_back(MPG[i]);
			}
		}
		std::sort (tMPG.begin(), tMPG.end(), myfunctionx);
	}
	MPG=tMPG;

}

void PSO::mostrar_MPG(){
	printf("MEJORES GLOBALES:");
	for (int i = 0; i < MPG.size(); ++i)
	{
		
		printf("Secuencia: [");
		mostrar_particula_x(MPG[i]);
		printf("]\n");
		printf("Costo Actual: %d , %d \n",MPG[i].fitness[0],MPG[i].fitness[1]);
		
	}
	printf("MEJORES GLOBALES FITNESS: \n");
	for (int i = 0; i < MPG.size(); ++i)
	{	
		printf("%d , %d \n",MPG[i].fitness[0],MPG[i].fitness[1]);
	}
}


void PSO::mostrar_particulas(){
		for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("Actual: [");
		mostrar_particula_x(particulas[i]);
		printf("]\n");
		printf("Costo Actual: %d , %d \n",particulas[i].fitness[0],particulas[i].fitness[1]);
		
		printf("Actual: [");
		mostrar_particula_x(pBest[i]);
		printf("]\n");
		printf("Costo del Mejor: %d , %d \n",particulas[i].fitness[0],particulas[i].fitness[1]);

		printf("Velocidad: [");
		mostrar_particula_v(particulas[i]);
		printf("]\n\n");
	}
}

void PSO::run(){
	Num w,d1,d2,rand1,rand2;
	mostrar_MPG();
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		printf("Iteracion %d *************\n", iteraciones+1);
		/*printf("Mejor Global: [");
		mostrar_particula_x(gBest);
		printf("]\n");
		printf("Costo del mejor Global: %d \n\n",gBest.fitness );
		*/
		mostrar_particulas();

		w=random(1);
		d1=1.0;
		d2=1.0;
		//rand1=random(1);
		//rand2=random(1);
		for (int i = 0; i < tam_poblacion; ++i)
		{
			int numalG=random(MPG.size());
			int numalP=random(pBest.size());
	
			particulas[i].v=((pBest[numalP].x)-(particulas[i].x))+(MPG[numalG].x - particulas[i].x);
			
			particulas[i].x=SS(particulas[i].x,particulas[i].v);
			particulas[i].fitness[0]=generar_aptitud1(particulas[i].x);
			particulas[i].fitness[1]=generar_aptitud2(particulas[i].x);
			if (comparar3(pBest[i].fitness,particulas[i].fitness)==true)
			{
				pBest[i]=particulas[i];
				if (comparar1(MPG.front().fitness,particulas[i].fitness)==true)
				{
					MPG.push_back(particulas[i]);
				}else if(comparar2(MPG.back().fitness,particulas[i].fitness)==true){
					MPG.push_back(particulas[i]);
				}
				else{
					for (int iMPG = 1; iMPG < MPG.size(); ++iMPG)
					{
						if (MPG[iMPG-1].fitness[0]<particulas[i].fitness[0] and MPG[iMPG].fitness[0]>particulas[i].fitness[0] and MPG[iMPG-1].fitness[1]>particulas[i].fitness[1] and MPG[iMPG].fitness[1]<particulas[i].fitness[0]  )
						{
							MPG.push_back(particulas[i]);
							iMPG=MPG.size();
						}	
					}
				}
				std::sort (MPG.begin(), MPG.end(), myfunctionx);
			}
			actualizar();
		}

		lBest=Mejor(particulas);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}
		//mostrar_particulas();
	}
	mostrar_particulas();
	mostrar_MPG();
}

PSO::PSO(vector<vector<Num>> & matriz,vector<vector<Num>> & matriz2){
	
	this->matrixdis=matriz;
	this->matrixcos=matriz2;
	vector<int> ciudad;
	
	//cout<<"HOLa";
	Particula P;
	for (int i = 0; i < tam_poblacion; ++i)
	{

		while(ciudad.size()!=matrixdis.size()){
			Num aleatorio=random(matrixdis.size());
			auto it=find (ciudad.begin(), ciudad.end(),aleatorio);
			if (it != ciudad.end()){
				;
			}
			else{
			    ciudad.push_back(aleatorio);//std::cout << "Element not found in myvector\n";			
			}
		}
		P.x=ciudad;

		P.fitness.push_back(generar_aptitud1(P.x));
		P.fitness.push_back(generar_aptitud1(P.x));
				
		particulas.push_back(P);
		
		pBest.push_back(P);
		ciudad.clear();
		P.fitness.clear();
		//P.x.clear();
	}

	std::vector<Particula> ptmp=pBest;

	std::sort (ptmp.begin(), ptmp.end(), myfunctionx);
	
	MPG.push_back(ptmp[0]);
	std::sort (ptmp.begin(), ptmp.end(), myfunctiony);
	MPG.push_back(ptmp[0]);
	
	for (int ipBest = 0; ipBest < pBest.size(); ++ipBest)
	{
		for (int iMPG = 1; iMPG < MPG.size(); ++iMPG)
		{
			if (MPG[iMPG-1].fitness[0]<pBest[ipBest].fitness[0] and MPG[iMPG].fitness[0]>pBest[ipBest].fitness[0] and MPG[iMPG-1].fitness[1]>pBest[ipBest].fitness[1] and MPG[iMPG].fitness[1]<pBest[ipBest].fitness[0]  )
				{
					MPG.push_back(pBest[ipBest]);
				}	
		}
		std::sort (MPG.begin(), MPG.end(), myfunctionx);
	}
	gBest=Mejor(pBest);
	//mostrar_particula(gBest);
	lBest=Mejor(pBest);
	//mostrar_particula(lBest);
	run();

}	

int PSO::generar_aptitud1(vector<int> v){
	int sum=0;
	for (int i = 1; i < v.size(); ++i)
	{
		sum+=matrixdis[v[i-1]][v[i]];
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum;
}

int PSO::generar_aptitud2(vector<int> v){
	int sum=0;
	for (int i = 1; i < v.size(); ++i)
	{
		sum+=matrixcos[v[i-1]][v[i]];
		//cout<<matrix[v[i-1]][v[i]]<<endl;
	}
	//cout<<endl;
	return sum;
}

#endif	
