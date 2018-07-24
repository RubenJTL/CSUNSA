#ifndef CLONALG_H
#define CLONALG_H

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

int random(int min, int max){
	return (rand() % (max+1) + min);
}


Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}


Num BinaryToDecimal(std::vector<int> x,int ini,int fin,int decimal){
	Num sum=0;
	for (int i = ini; i < fin; ++i)
	{
		if (x[i]!=0)
		{
			sum+=pow(2,decimal-1-(i%decimal));
		//	printf("%d %f\n",x[i],pow(2,decimal-1-(i%decimal)) );
		}else{
		//	printf("%d %d\n",x[i],0 );
		}
		//sum+=pow(2*x[i],decimal-1-(i%decimal));
	}
	return sum;
}
Num ValorX(Num sum,Num max,Num min,int decimal){
	//printf("%f\n",min+((max-min)/(pow(2.0,decimal)-1.0)*sum));
	return (min+((max-min)/(pow(2.0,decimal)-1.0)*sum));
}

Num funcion(std::vector<Num> x){
	Num sum=0;
	for (int i = 0; i < x.size(); ++i)
	{
		sum+=pow(x[i],2);
	}
	return sum;
}

Num afinidad(Num f,Num Maxf, Num Minf){
	return 1.0-(f/(Maxf-Minf));
}



typedef struct 
{
	vector<int> Xb;
	vector<Num> Xd;
	Num fitness;
	Num afinidad;
}Individuo;

struct CompA
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       	return s1.afinidad>s2.afinidad;
   }
}; ////

struct CompF
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       	return s1.fitness<s2.fitness;
   }
}; ////


void mostrar_Binary(std::vector<int> b){
	printf("=");
	for (int i = 0; i < b.size(); ++i)
	{
		printf("%d",b[i]);
	}
}
void mostrar_Decimal(std::vector<Num> b){
	printf("=[");
	for (int i = 0; i < b.size(); ++i)
	{
		printf("%f",b[i]);
		if (i!=b.size()-1)
		{
			printf(", ");
		}
	}
	printf("]");
}

void mostrar_Num(Num n){
	printf("={%f}",n);
}
void mostrar_Individuo(Individuo I){
	printf("X");
	mostrar_Binary(I.Xb);
	printf("\n");
	printf("X");
	mostrar_Decimal(I.Xd);
	printf(", ");
	printf("f");
	mostrar_Num(I.fitness);
	printf("\n");
}

void Mutar(Individuo &I,int decimal, std::vector<Num> max,std::vector<Num>  min, Num mutacionR){
	for (int i = 0; i < I.Xb.size(); ++i)
	{
		Num num=random(1);
		if (num<mutacionR)
		{
			if (I.Xb[i]==1)
			{
				I.Xb[i]=0;
			}else{
				I.Xb[i]=1;
			}
		}
	}
	for (int i = 0; i < max.size(); ++i)
	{
		Num sum=BinaryToDecimal(I.Xb,i*decimal,(i+1)*decimal,decimal);
		//printf("%f\n",sum );
		//Num valor=ValorX(sum,max[i],min[i],decimal);
		//printf("%f\n", valor);
		I.Xd[i]=(ValorX(sum,max[i],min[i],decimal));
		//printf("\n");
	}
	I.fitness=funcion(I.Xd);
}

Individuo Clonar(Individuo I){
	Individuo nuevo= I;
	return nuevo;
}

class CLONALG
{
public:
	CLONALG(int a);
	//~CLONALG();
	void mostrar_poblacion();
	void mostrar_Clones();
	void run();
	

	std::vector<Individuo> Poblacion;
	std::vector<Individuo> PoblacionS;
	std::vector<Individuo> PoblacionC;

	vector<Num> max={5,5};
	vector<Num> min={-5,-5};
	int decimal=16;
	int Generaciones=100;
	int Population=4;
	int Selection=4;
	int RandomCells=2;
	Num MutationF=-2.5;
	Num CloneR=0.5;
	Num Maxf;
	Num Minf;
};

void CLONALG::run(){
	for (int iteraciones = 0; iteraciones < Generaciones; ++iteraciones)
	{

		mostrar_poblacion();

		printf("\nCalcular afinidad\n");
		for (int p = 0; p < Population; ++p)
		{
			Poblacion[p].afinidad=afinidad(Poblacion[p].fitness,Maxf,Minf);
			printf("X");
			mostrar_Decimal(Poblacion[p].Xd);
			printf(", f");
			mostrar_Num(Poblacion[p].fitness);
			printf(", a");
			mostrar_Num(Poblacion[p].afinidad);
			printf("\n");
		}
		Num cantidadClone=Population*CloneR;
		sort (Poblacion.begin(), Poblacion.end(),CompA());
		for (int s = 0; s < Selection; ++s)
		{
			PoblacionS.push_back(Poblacion[s]);
		}
		printf("\nCantidad de clones %f \n",cantidadClone);
		for (int s = 0;s < Selection; ++s)
		{
			Num mutationR=exp(MutationF*PoblacionS[s].afinidad);
			printf("Clon %d Mutacion Rate %f\n",s,mutationR );
			for (int c = 0; c < cantidadClone; ++c)
			{
				Individuo Cl=Clonar(PoblacionS[c]);
				//if (mutationR<1.0)
				//{
				Mutar(Cl,decimal,max,min,mutationR);
				//}	
				PoblacionC.push_back(Cl);
			}		
		}
		
		sort (Poblacion.begin(), Poblacion.end(),CompF());
		sort (PoblacionC.begin(), PoblacionC.end(),CompF());
		mostrar_Clones();
		mostrar_poblacion();
		for (int it = 0; it < Population; ++it)
		{
			if (Poblacion[it].fitness>PoblacionC[it].fitness)
			{
				Poblacion[it]=PoblacionC[it];
			}
		}
		printf("Poblacion+Clones(Mejores)\n");
		PoblacionC.clear();
		mostrar_poblacion();

		printf("\nGeneracion Aleatoria\n");
		std::vector<Individuo> PoblacionA;
		for (int r = 0; r < RandomCells; ++r)
		{
			Individuo tmp;
			for (int k = 0; k < decimal*2; ++k)
			{
				tmp.Xb.push_back(random(0,1));
			}
			for (int k = 0; k < max.size(); ++k)
			{
				Num sum=BinaryToDecimal(tmp.Xb,k*decimal,(k+1)*decimal,decimal);
				//printf("%f\n",sum );
				//Num valor=ValorX(sum,max[i],min[i],decimal);
				//printf("%f\n", valor);
				tmp.Xd.push_back(ValorX(sum,max[k],min[k],decimal));
				//printf("\n");
			}
			tmp.fitness=funcion(tmp.Xd);
/*				
*/		
			PoblacionA.push_back(tmp);
		}
		sort (Poblacion.begin(), Poblacion.end(),CompF());
		sort (PoblacionA.begin(), PoblacionA.end(),CompF());
		int it2=0;
		for (int it = 0; it < PoblacionA.size(); ++it)
		{	

			if (Poblacion[it].fitness>PoblacionA[it2].fitness)
			{
				Poblacion[it]=PoblacionA[it2];
				it2++;
			}
		}
		for (int it= 0; it < Population; ++it)
		{
			if (it==0)
			{
				Maxf=Poblacion[it].fitness;
				Minf=Poblacion[it].fitness;
			}else{
				if (Maxf<Poblacion[it].fitness)
				{
					Maxf=Poblacion[it].fitness;
				}
				if (Minf>Poblacion[it].fitness)
				{
					Minf=Poblacion[it].fitness;
				}	
			}
		}
		for (int it = 0; it < PoblacionA.size(); ++it)
		{
			mostrar_Individuo(PoblacionA[it]);
		}
		printf("Reemplazar:\n");
		mostrar_poblacion();
	}
	printf("\nMEJOR INDIVIUDO\n");
	mostrar_Individuo(Poblacion[0]);
}

void CLONALG::mostrar_Clones(){
	printf("Clones\n");
	for (int i = 0; i < PoblacionC.size(); ++i)
	{
		mostrar_Individuo(PoblacionC[i]);
		
	}
	printf("\n");
}

void CLONALG::mostrar_poblacion(){
	printf("Poblacion\n");
	for (int i = 0; i < Poblacion.size(); ++i)
	{
		mostrar_Individuo(Poblacion[i]);
	}
}

CLONALG::CLONALG(int a){
	
	for (int p = 0; p < Population; ++p)
	{	
		Individuo tmp;
		for (int i = 0; i < decimal*2; ++i)
		{
			tmp.Xb.push_back(random(0,1));
		}
		for (int i = 0; i < max.size(); ++i)
		{
			Num sum=BinaryToDecimal(tmp.Xb,i*decimal,(i+1)*decimal,decimal);
			//printf("%f\n",sum );
			Num valor=ValorX(sum,max[i],min[i],decimal);
			//printf("%f\n", valor);
			tmp.Xd.push_back(ValorX(sum,max[i],min[i],decimal));
			//printf("\n");
		}
		tmp.fitness=funcion(tmp.Xd);
		if (p==0)
		{
			Maxf=tmp.fitness;
			Minf=tmp.fitness;
		}else{
			if (Maxf<tmp.fitness)
			{
				Maxf=tmp.fitness;
			}
			if (Minf>tmp.fitness)
			{
				Minf=tmp.fitness;
			}
		}
		Poblacion.push_back(tmp);
	}
	run();
	//mostrar_poblacion();

	/*for (int iteraciones = 0; iteraciones < Generaciones; ++iteraciones)
	{
	
	}*/
}



#endif	
