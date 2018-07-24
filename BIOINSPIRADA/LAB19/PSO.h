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

typedef double Num;


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

Num Function1(vector<Num> & x){
	Num sum=0;
	for (int i = 0; i < x.size(); ++i)
	 {
	 	sum+=pow(x[i],2);
	 } 
	 return sum;
}

Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}

Num ValorX(Num lim_inf,Num lim_sup){
	Num aleatorio;
	Num signo;
	for (Num i = lim_inf; i < lim_sup; i+=1)
	{

	/*do{
		aleatorio=random(lim_sup);
		//printf("%f\n", aleatorio );
		if(signo>0.5){
			aleatorio=aleatorio*(-1);
		}
	}while(aleatorio<=lim_inf and aleatorio>=lim_sup);
		//printf("%f\n", aleatorio );*/
		aleatorio=random(1);
		if (aleatorio<=0.5)
		{
			return i;
		}
	}
	return lim_inf;
		//return aleatorio;
}


typedef struct {
	vector<Num> x;
	vector<Num> v;
	vector<Num> fitness;
}Particula;

bool myfunctionx (Particula i,Particula j) { return (i.fitness[0]<j.fitness[0]); }
bool myfunctiony (Particula i,Particula j) { return (i.fitness[1]<j.fitness[1]); }

void mostrar_particula(Particula p){
	for (int i = 0; i < p.x.size(); ++i)
	{
		printf("x%d = %le;\t",i+1, p.x[i]);
	}
	for (int i = 0; i < p.v.size(); ++i)
	{
		printf("v%d = %le;\t",i+1, p.v[i]);
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
	PSO(int iteraciones);
	//~PSO();
	void mostrar_particulas();
	void mostrar_MPG();
	void run();
	void actualizar();
	Num funcion1(Num x,Num y);
	Num funcion2(Num x,Num y);

	Num lim_inf=-1;
	Num lim_sup=10;
	Particula gBest;
	Particula lBest;
	vector<Particula> particulas;
	vector<Particula> MPG;
	vector<Particula> pBest;

	vector<vector<Num>> distancias;
	vector<vector<Num>> costos;

	int cantidad_de_iteraciones=50;
	int tam_poblacion=4;
	int dimensiones=2;
};

Num PSO::funcion1(Num x,Num y){
	return (4*pow(x,2))+(4*pow(y,2));
}
Num PSO::funcion2(Num x,Num y){
	return (pow(x-5,2)+pow(y-5,2));
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
	printf("***MEJORES GLOBALES***\n");
	for (int i = 0; i < MPG.size(); ++i)
	{
		printf("%d) ", i+1);
		mostrar_particula(MPG[i]);
		printf("\n");
	}
	printf("***FITNESS MEJORES GLOBALES***\n");
	for (int i = 0; i < MPG.size(); ++i)
	{
		printf("%f , %f \n",MPG[i].fitness[0],MPG[i].fitness[1]);
	}
}

void PSO::mostrar_particulas(){
	printf("***Cumulo de particulas***\n");
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("%d) ", i+1);
		mostrar_particula(particulas[i]);
		printf("\n");
	}
	printf("***Fitness***\n");
	for (int i = 0; i < tam_poblacion; ++i)
	{
		printf("%d) (%f,%f) \n", i+1,particulas[i].fitness[0],particulas[i].fitness[1]);
	}
}

void PSO::run(){
	//printf("HOLA\n");
	mostrar_particulas();
	mostrar_MPG();
	Num w,d1,d2,rand1,rand2;
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		printf("*****Iteracion %d \n", iteraciones+1);
		/*printf("Mejor: ");
		mostrar_particula(gBest);
		printf("Fitness: %f \n", gBest.fitness );
		*/
		w=random(1);
		d1=1.0;
		d2=1.0;
		rand1=random(1);
		rand2=random(1);
		for (int i = 0; i < tam_poblacion; ++i)
		{
			int numalG=random(MPG.size());
			int numalP=random(pBest.size());
			for (int dim = 0; dim < dimensiones; ++dim)
			{
				particulas[i].v[dim]=w*particulas[i].v[dim];
				particulas[i].v[dim]+=d1*rand1*(pBest[numalP].x[dim]-particulas[i].x[dim]);
				particulas[i].v[dim]+=d2*rand2*(MPG[numalG].x[dim]-particulas[i].x[dim]);
				particulas[i].x[dim]=particulas[i].x[dim]+particulas[i].v[dim];
			}
			if (particulas[i].x[0]>=0 and particulas[i].x[0]<=5 and particulas[i].x[1]>=0 and particulas[i].x[1]<=3)
			{
				particulas[i].fitness[0]=funcion1(particulas[i].x[0],particulas[i].x[1]);
				particulas[i].fitness[1]=funcion2(particulas[i].x[0],particulas[i].x[1]);	
			}else{
				particulas[i].x[0]=0;
				particulas[i].x[1]=0;
				particulas[i].fitness[0]=funcion1(particulas[i].x[0],particulas[i].x[1]);
				particulas[i].fitness[1]=funcion2(particulas[i].x[0],particulas[i].x[1]);		
			}
						
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
		}
		actualizar();
		/*lBest=Mejor(particulas);
		if (lBest.fitness<gBest.fitness)
		{
			gBest=lBest;
		}*/
		mostrar_particulas();
		mostrar_MPG();
	}
	std::sort (MPG.begin(), MPG.end(), myfunctionx);
	mostrar_MPG();
	/*printf("Mejor: ");
	mostrar_particula(gBest);
	printf("Fitness: %f \n", gBest.fitness );*/
}

PSO::PSO(int iteraciones){
	Num x,v;
	//cout<<"HOLa";
	Particula P;
	while (particulas.size()<tam_poblacion)
	{
		for (int dim = 0; dim < dimensiones; ++dim)
		{
			x=ValorX(lim_inf,lim_sup);
			v=random(1);//ValorX(lim_inf,lim_sup);
			P.x.push_back(x);
			P.v.push_back(v);
		}
		if(P.x[0]>=0 and P.x[0]<=5 and P.x[1]>=0 and P.x[1]<=3){
			P.fitness.push_back(funcion1(P.x[0],P.x[1]));
			P.fitness.push_back(funcion2(P.x[0],P.x[1]));
			particulas.push_back(P);
			pBest.push_back(P);
			//MPG.push_back(P);
			P.fitness.clear();
		}
		P.x.clear();
		P.v.clear();
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
	
	/*for (int iMPG = 1; iMPG < MPG.size() ; ++iMPG)
	{
		if (MPG[iMPG].x[0]==MPG[iMPG-1].x[0])
		{

		}
	}
	*/
	gBest=Mejor(pBest);
	//mostrar_particula(gBest);
	lBest=Mejor(pBest);
	//mostrar_particula(lBest);
	run();

}	


#endif	