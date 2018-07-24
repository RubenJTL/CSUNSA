#ifndef COLONIA_H
#define COLONIA_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

typedef double Num;

void mostrar_matriz(vector<vector<Num>> &);

typedef struct {
	vector<int> orden;
	//vector<int> F;
	Num costo;
	//Num costoF;
}Hormiga;



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


class Colonia{
public:
	Colonia(vector<vector<Num>> & ,vector<vector<Num>> & );

	void mostrar_hormigas();
	Num generar_costo(vector<vector<Num>> & D,vector<vector<Num>> & F, vector<int> &S);
	void run();

	int cantidad_de_hormigas=50;
	Num p=0.9;
	Num a=1;
	Num b=1;
	Num Q=1;
	Num e=5;
	Num tmin=0.00000009;
	Num tmax=10;
	Num Feromona_Inicial=tmax;
	int cantidad_de_iteraciones=1000;
	int ciudad_inicial=3;

	vector<std::vector<Num>> matrixdis;
	vector<std::vector<Num>> matrixF;
	vector<std::vector<Num>> matrixvis;
	vector<std::vector<Num>> matrixfer;

	vector<Hormiga> Hormigas;

};

Colonia::Colonia(vector<vector<Num>> & v, vector<vector<Num>> & F){
	vector<Num> temp;
	for (int i = 0; i < v.size(); ++i)
	{
		temp.push_back(0.0);
	}
	for (int i = 0; i < v.size(); ++i)
	{
		matrixvis.push_back(temp);
		matrixfer.push_back(temp);
	}
	matrixdis=v;
	matrixF=F;

}


void Colonia::run(){
	Hormiga MEJOR;
	std::vector<std::vector<Num>> e;
	std::vector<Num> t1;
	for (int i = 0; i < matrixdis.size(); ++i)
	{
		t1.push_back(0);
	}
	for (int i = 0; i < matrixdis.size(); ++i)
	{
		e.push_back(t1);
	}

	for(int i=0; i<matrixdis.size(); ++i)
        for(int j=0; j<matrixdis.size(); ++j)
            for(int z=0; z<matrixdis.size(); ++z)
                e[i][j] += matrixdis[i][z] * matrixF[z][j];

	for (int i = 0; i < matrixdis.size(); ++i)
	{
		for (int j = 0; j < matrixdis[i].size(); ++j)
		{
			if (i!=j)
			{

				matrixvis[i][j]=1/e[i][j];
				matrixfer[i][j]=Feromona_Inicial;
			}
		}
	}
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		cout<<"ITERACION: "<<iteraciones<<endl;
		for (int hs = 0; hs < cantidad_de_hormigas; ++hs)
		{
		cout<<"HORMIGA :"<<hs<<endl;
		vector<int> ciudad;
		int pos=(int) (rand()) / (int) (RAND_MAX/matrixdis.size());
		ciudad.push_back(pos);
		vector<tuple<int,Num>> tn;
		vector<Num> prob;
		
		mostrar_matriz(matrixvis);
		mostrar_matriz(matrixfer);
		while(ciudad.size()<matrixdis.size()){
			cout<<ciudad.size()+1<<" CIUDAD"<<endl;
			if(ciudad.size()==1){
				cout<<"Ciudad Inicial "<<pos<<endl;	
			}
			
			Num sum=0.0;
			for (int i = 0; i < matrixvis.size(); ++i)
			{
				if(i!=pos){
					std::vector<int>::iterator it;
					it = find (ciudad.begin(), ciudad.end(), i);
					if (it != ciudad.end()){
						///std::cout << "Element found in myvector: " << *it << '\n';
					}
					else{
						auto cid=make_tuple(i,pow(matrixfer[pos][i],a)*pow(matrixvis[pos][i],b));
						tn.push_back(cid);
						sum+=pow(matrixfer[pos][i],a)*pow(matrixvis[pos][i],b);
						cout<<pos<<"-"<<i<<": "<<matrixfer[pos][i]*matrixvis[pos][i]<<endl;
						//cout<<"Suma: "<<sum<<endl;
					}

				}
			}
			cout<<"Suma: "<<sum<<endl;
			

			for (int i = 0; i < tn.size(); ++i)
			{
				prob.push_back(get<1>(tn[i])/sum);
				cout<<pos<<"-"<<get<0>(tn[i])<<": "<<get<1>(tn[i])/sum<<endl;
			}
			Num aleatorio=(Num)(rand()%10000000)/10000000.0;
			cout<<"Numero aleatorio para la probabilidad "<<aleatorio<<endl;
			Num rango=0;
			for (int i = 0; i < prob.size(); ++i)
			{
				if(aleatorio>=rango and aleatorio<rango+prob[i]){
					pos=i;
					break;
				}
				rango+=prob[i];
			}
			//cout<<pos<<endl;
			ciudad.push_back(get<0>(tn[pos]));
			cout<<"Siguiente: "<<get<0>(tn[pos])<<endl;
			pos=get<0>(tn[pos]);	
			tn.clear();
			prob.clear();
		}
		Hormiga H1;
		H1.orden=ciudad;
		H1.costo=generar_costo(matrixdis,matrixF,H1.orden);
		Hormigas.push_back(H1);
		
		ciudad.clear();

	}
	sort (Hormigas.begin(), Hormigas.end(),Comp());
	mostrar_hormigas();
	//	if(MEJOR.costo>Hormigas[0].costo or iteraciones==0)	
	MEJOR=Hormigas[0];





	for (int i = 0; i < matrixfer.size(); ++i)
	{
		for (int j = 0; j < matrixfer.size(); ++j)
		{
			Num sum=0;
			sum+=matrixfer[i][j]*(1-p);
			int temp[2];
			temp[0]=i;
			temp[1]=j;
			int temp1[2];
			temp1[0]=j;
			temp1[1]=i;
			if(i!=j){
			/*	for(int h=0;h<Hormigas.size();h++){
					std::vector<int>::iterator it;
 					it=search((Hormigas[h]).orden.begin(), (Hormigas[h]).orden.end(), temp, temp+2,mypredicate);
 					std::vector<int>::iterator it1;
 					it1=search((Hormigas[h]).orden.begin(), (Hormigas[h]).orden.end(), temp1, temp1+2,mypredicate);
					if (it!=Hormigas[h].orden.end() or it1!=Hormigas[h].orden.end() )
					    sum+=Q/Hormigas[h].costo;
					else
						sum+=0;
				}*/
				std::vector<int>::iterator it;
 				it=search(MEJOR.orden.begin(), MEJOR.orden.end(), temp, temp+2,mypredicate);
 				std::vector<int>::iterator it1;
 				it1=search(MEJOR.orden.begin(), MEJOR.orden.end(), temp1, temp1+2,mypredicate);
				if (it!=MEJOR.orden.end() or it1!=MEJOR.orden.end() )
				    sum+=1/MEJOR.costo;
				else
					sum+=0;

				matrixfer[i][j]=sum;
				if (matrixfer[i][j]<tmin)
				{
					matrixfer[i][j]=tmin;
				}else if(matrixfer[i][j]>tmax){
					matrixfer[i][j]=tmax;
				}
			}

		}
	}
	
	Hormigas.clear();
	}
	cout<<"MEJOR HORMIGA"<<endl;
	for (int i = 0; i < MEJOR.orden.size(); ++i)
	{
		cout<<MEJOR.orden[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJOR.costo<<endl;
	mostrar_matriz(matrixfer);


}

Num Colonia::generar_costo(vector<vector<Num>> & D,vector<vector<Num>> & F, vector<int> &S){
	Num sum=0;
	for (int i = 0; i < D.size(); ++i)
	{
		for (int j = 0; j < D[i].size(); ++j)
		{
			sum+=F[i][j]*D[S[i]][S[j]];
		}
		//cout<<endl<<orden[i-1]<<endl;
		//cout<<endl<<orden[i-1]<<endl;
		
	}
	//cout<<"costo: "<<sum<<endl;
	return sum;
}

void Colonia::mostrar_hormigas(){
	for (int i = 0; i < Hormigas.size(); ++i)
	{
		cout<<"Hormiga: "<<i+1<<endl;
		for (int j = 0; j < Hormigas[i].orden.size(); ++j)
		{
			cout<<Hormigas[i].orden[j]<<"  ";
		}
		cout<<Hormigas[i].costo;
		cout<<endl;
	}
	cout<<endl;
}

void mostrar_matriz(vector<vector<Num>> & matriz){
	for (int i = 0; i < matriz.size(); ++i)
	{
		for (int j = 0; j < matriz[i].size(); ++j)
		{
			cout<<matriz[i][j]<<"    ";
		}
		cout<<endl;
	}
	cout<<endl;
}
#endif	
