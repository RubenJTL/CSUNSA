#ifndef ABC_H
#define ABC_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef double Num;

void mostrar_matriz(vector<vector<Num>> &);

typedef struct {
	vector<Num> x;
	Num Fx;
	Num fit;
	int cont;
}Alimento;

void mostrar_alimento(Alimento a){
	for (int i = 0; i < a.x.size(); ++i)
	{
		printf("%f\t", a.x[i]);
	}
	printf("%f\t%f\t%d\n",a.Fx,a.fit,a.cont );
	
}


Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}

int random(int min, int max){
	return (rand() % max + min);
}
/*
struct Comp
{
   bool operator()(Hormiga & s1, Hormiga & s2)
   {
       	return s1.costo<s2.costo;
   }
}; ////

bool mypredicate (int i, int j) {
  return (i==j);
}

*/
class ABC
{
public:
	ABC(int it);
	//~ABC();
	void run();


	Num funcion(std::vector<Num> &v);
	Num fit(Num a);
	
	void mostrar_soluciones();


	int tamnanho_colmena=6;
	int Numero_soluciones=3;
	int dimension=2;
	Num limite=(tamnanho_colmena*dimension)/2;
	int MaximoCiclosNumber=60;

	int limite_inf=-5;
	int limite_superior=5;
	Alimento MS;
	std::vector<Alimento> Soluciones;
	std::vector<Alimento> v;
	std::vector<Num> P;
	std::vector<Num> Piscum;


};
void ABC::run(){
	int k,j;
	Num deltha;
	for (int iteraciones = 0; iteraciones < MaximoCiclosNumber; ++iteraciones)
	{
		printf("****************************************SOLUCIONES CANDIDATAS*******************************************\n");
		printf("k\tj\tdeltha\t\tvij\t\tvij\t\tf(vi)\t\tfiti\t\tcont\n");
		for (int i = 0; i < Numero_soluciones; ++i)
		{
			
			do{
				k=random(0,Numero_soluciones);
			}while(k==i);
			j=random(0,dimension);
			deltha=random(1);
			if (random(1)<0.5)
			{
				deltha=deltha*(-1);
			}
			v[i].x[j]=Soluciones[i].x[j]+(deltha*(Soluciones[i].x[j]-Soluciones[k].x[j]));
			v[i].Fx=funcion(v[i].x);
			v[i].fit=fit(v[i].Fx);
			if (v[i].fit<Soluciones[i].fit)
			{
				Soluciones[i].cont=Soluciones[i].cont+1;
				v[i].cont=v[i].cont+1;
				if (Soluciones[i].cont==limite)
				{
					Alimento a;
					do{
						for (int dim = 0; dim < dimension; ++dim)
						{
							Num aleatorio=random(limite_superior);
							Num signo=random(1);
							if (signo<0.5)
							{
								aleatorio=aleatorio*(-1);
							}
							a.x.push_back(aleatorio);
						}
					}while(a.x[0]>limite_superior or a.x[0]<limite_inf or a.x[1]>limite_superior or a.x[1]<limite_inf);
					a.Fx=funcion(a.x);
					a.fit=fit(a.Fx);
					a.cont=0;
					Soluciones[i]=a;
				}
			}else{
				Soluciones[i]=v[i];
				Soluciones[i].cont=0;
			}
			printf("%d\t%d\t%f\t",k+1,j+1,deltha);
			mostrar_alimento(v[i]);		
		}
		printf("********************************************************************************************************\n");
		printf("\n");
		printf("OBSERVADORAS\n");
		for (int i = 0; i < Numero_soluciones; ++i)
		{
			printf("Mejores Soluciones***************************************************************************\n");
			printf("Fuente\tx1\t\tx2\t\tf(xi)\t\tfiti\t\tcont\n");
			Num sum=0;
			for (int i = 0; i < Numero_soluciones; ++i)
			{
				printf("%d\t",i+1);
				mostrar_alimento(Soluciones[i]);
				sum+=Soluciones[i].fit;
			}
			printf("Sumatoria de fit %f\n", sum );
			for (int i = 0; i < Numero_soluciones; ++i)
			{
				P[i]=Soluciones[i].fit/sum;
				if (i==0)
				{
					Piscum[i]=P[i];
				}else{
					Piscum[i]=Piscum[i-1]+P[i];
				}	
			}
			printf("Pi\t\tPiscum\n" );	
			for (int i = 0; i < Numero_soluciones; ++i)
			{
				printf("%f\t%f\n",P[i],Piscum[i] );
			}
			Num NA=random(1);
			int pos;
			for (int p= 0; p < Numero_soluciones; ++p)
			{
				if (NA<Piscum[p])
				{
					//printf("%f  %f AQUI %d\n",NA,Piscum[p],p );
					pos=p;
					break;
				}
			}
			do{
				k=random(0,Numero_soluciones);
			}while(k==pos);
			j=random(0,dimension);
			v[pos]=Soluciones[pos];
			printf("NA %f\n",NA );
			printf("Fuente\tx1\t\tx2\t\tf(xi)\t\tfiti\t\tk\tj\n");
			printf("%d\t%f\t%f\t%f\t%f\t%d\t%d\n",pos+1,Soluciones[pos].x[0],Soluciones[pos].x[1],Soluciones[pos].Fx,Soluciones[pos].fit,k+1,j+1);	
			printf("%d\t%f\t%f\n\n",k+1,Soluciones[k].x[0],Soluciones[k].x[1]);	
			deltha=random(1);
			if (random(1)<0.5)
			{
				deltha=deltha*(-1);
			}
			v[pos].x[j]=Soluciones[pos].x[j]+(deltha*(Soluciones[pos].x[j]-Soluciones[k].x[j]));
			v[pos].Fx=funcion(v[pos].x);
			v[pos].fit=fit(v[pos].Fx);
			if (v[pos].fit<Soluciones[pos].fit)
			{
				Soluciones[pos].cont=Soluciones[pos].cont+1;
				v[pos].cont=v[pos].cont+1;
				if (Soluciones[pos].cont==limite)
				{
					Alimento a;
					do{
						for (int dim = 0; dim < dimension; ++dim)
						{
							Num aleatorio=random(limite_superior);
							Num signo=random(1);
							if (signo<0.5)
							{
								aleatorio=aleatorio*(-1);
							}
							a.x.push_back(aleatorio);
						}
					}while(a.x[0]>limite_superior or a.x[0]<limite_inf or a.x[1]>limite_superior or a.x[1]<limite_inf);
					a.Fx=funcion(a.x);
					a.fit=fit(a.Fx);
					a.cont=0;
					Soluciones[pos]=a;
				}
			}else{
				Soluciones[pos]=v[pos];
				Soluciones[pos].cont=0;
			}		
			printf("deltha\t\tvij\t\tvij\t\tf(xi)\t\tfiti\t\tcont\n");
			printf("%f\t%f\t%f\t%f\t%f\t%d\n\n",deltha,v[pos].x[0],v[pos].x[1],v[pos].Fx,v[pos].fit,v[pos].cont);	
		}
		printf("Mejores Soluciones\n");
		printf("Fuente\t\tx1\t\tx2\t\tf(xi)\t\tfiti\n");
		printf("Mejor anterior\t%f\t%f\t%f\t%f\n",MS.x[0],MS.x[1],MS.Fx,MS.fit );
		for (int i = 0; i < Numero_soluciones; ++i)
		{
			if (Soluciones[i].fit>MS.fit)
			{
				MS=Soluciones[i];
			}
		}
		printf("Mejor nuevo\t%f\t%f\t%f\t%f\n",MS.x[0],MS.x[1],MS.Fx,MS.fit );
		printf("Memorizado\t%f\t%f\t%f\t%f\n",MS.x[0],MS.x[1],MS.Fx,MS.fit );
	}

}

void ABC::mostrar_soluciones(){
	printf("Fuente\tx1\t\tx2\t\tf(xi)\t\tfiti\t\tcont\n");
	Num mejor=0;
	for (int i = 0; i < Numero_soluciones; ++i)
	{
		printf("%d\t",i+1);
		mostrar_alimento(Soluciones[i]);
	}
	//printf("\n");
}

ABC::ABC(int it){
	while(Soluciones.size()<Numero_soluciones)
	{
		Alimento a;
		for (int dim = 0; dim < dimension; ++dim)
		{
			Num aleatorio=random(limite_superior);
			Num signo=random(1);
			if (signo<0.5)
			{
				aleatorio=aleatorio*(-1);
			}
			a.x.push_back(aleatorio);
		}
		a.Fx=funcion(a.x);
		a.fit=fit(a.Fx);
		a.cont=0;
		bool posible=true;
		for (int dim = 0; dim < dimension; ++dim)
		{
			if (a.x[dim]>limite_superior or a.x[dim]<limite_inf)
			{
				posible=false;
				break;
			}
		}
		if (posible==true)
		{
			if (Soluciones.size()==0)
			{
				MS=a;
			}
			else{
				if (MS.fit<a.fit)
				{
					MS=a;
				}
			}
			Soluciones.push_back(a);
		}
	}
	printf("Fuentes de Alimento Iniciales***********************************************\n");
	mostrar_soluciones();
	printf("\t\t\tMejor fuente de alimento\t%f\n",MS.fit );	
	printf("****************************************************************************\n\n");
	v=Soluciones;
	for (int i = 0; i < Numero_soluciones; ++i)
	{
		P.push_back(0);
		Piscum.push_back(0);
	}
	run();
}

Num ABC::fit(Num a){
	if (a>=0)
	{
		return 1/(1+a);
	}
	else{
		return 1+abs(a);
	}
}

Num ABC::funcion(vector<Num> &v){
	Num sum=0;
	for (int i = 0; i < dimension; ++i)
	{
		sum+=pow(v[i],2);
	}
	return sum;
}



#endif	
