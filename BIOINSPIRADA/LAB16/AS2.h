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
	vector<int> ciudades;
	Num costo;
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
	Colonia(vector<vector<Num>> & matriz);

	void mostrar_hormigas();
	Num generar_costo(vector<int> &);
	void run();

	int cantidad_de_hormigas=5;
	Num p=0.99;
	Num a=1;
	Num b=1;
	Num Q=1;
	Num Feromona_Inicial=0.1;
	int cantidad_de_iteraciones=100;
	int ciudad_inicial=0;

	vector<std::vector<Num>> matrixdis;
	vector<std::vector<Num>> matrixvis;
	vector<std::vector<Num>> matrixfer;

	vector<Hormiga> Hormigas;

};

Colonia::Colonia(vector<vector<Num>> & v){
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

}


void Colonia::run(){
	Hormiga MEJOR;

	for (int i = 0; i < matrixdis.size(); ++i)
	{
		for (int j = 0; j < matrixdis[i].size(); ++j)
		{
			if (i!=j)
			{
				matrixvis[i][j]=1/matrixdis[i][j];
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
		int tmpp=pos;
		ciudad.push_back(pos);
		vector<tuple<int,Num>> tn;
		vector<Num> prob;
		//int pos=ciudad_inicial;
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
			cout<<"Ciudad Siguiente: "<<get<0>(tn[pos])<<endl;
			pos=get<0>(tn[pos]);	
			tn.clear();
			prob.clear();
		}
		Hormiga H1;
		H1.ciudades=ciudad;
		H1.costo=generar_costo(H1.ciudades);

		for (int escalada = 0; escalada < 5; ++escalada)
		{
			vector<int> ciudad1;
			int pos1=(int) (rand()) / (int) (RAND_MAX/matrixdis.size());
			int tmpp=pos1;
			ciudad.push_back(pos1);
			vector<tuple<int,Num>> tn;
			vector<Num> prob;
			mostrar_matriz(matrixvis);
			mostrar_matriz(matrixfer);
			while(ciudad1.size()<matrixdis.size()){
				cout<<ciudad1.size()+1<<" ciudad1"<<endl;
				if(ciudad1.size()==1){
					cout<<"ciudad1 Inicial "<<pos1<<endl;	
				}
				
				Num sum=0.0;
				for (int i = 0; i < matrixvis.size(); ++i)
				{
					if(i!=pos1){
						std::vector<int>::iterator it;
						it = find (ciudad1.begin(), ciudad1.end(), i);
						if (it != ciudad1.end()){
							///std::cout << "Element found in myvector: " << *it << '\n';
						}
						else{
							auto cid=make_tuple(i,pow(matrixfer[pos1][i],a)*pow(matrixvis[pos1][i],b));
							tn.push_back(cid);
							sum+=pow(matrixfer[pos1][i],a)*pow(matrixvis[pos1][i],b);
							cout<<pos1<<"-"<<i<<": "<<matrixfer[pos1][i]*matrixvis[pos1][i]<<endl;
							//cout<<"Suma: "<<sum<<endl;
						}

					}
				}
				cout<<"Suma: "<<sum<<endl;
				

				for (int i = 0; i < tn.size(); ++i)
				{
					prob.push_back(get<1>(tn[i])/sum);
					cout<<pos1<<"-"<<get<0>(tn[i])<<": "<<get<1>(tn[i])/sum<<endl;
				}
				Num aleatorio=(Num)(rand()%10000000)/10000000.0;
				cout<<"Numero aleatorio para la probabilidad "<<aleatorio<<endl;
				Num rango=0;
				for (int i = 0; i < prob.size(); ++i)
				{
					if(aleatorio>=rango and aleatorio<rango+prob[i]){
						pos1=i;
						break;
					}
					rango+=prob[i];
				}
				//cout<<pos1<<endl;
				ciudad1.push_back(get<0>(tn[pos1]));
				cout<<"ciudad1 Siguiente: "<<get<0>(tn[pos1])<<endl;
				pos1=get<0>(tn[pos1]);	
				tn.clear();
				prob.clear();
			}
			Hormiga H2;
			H2.ciudades=ciudad1;
			H2.costo=generar_costo(H1.ciudades);
			if(H1.costo>H2.costo){
				H1=H2;
				break;	
			}
			ciudad1.clear();
		}


		Hormigas.push_back(H1);
		
		ciudad.clear();

	}
	sort (Hormigas.begin(), Hormigas.end(),Comp());
	mostrar_hormigas();
	




	for (int i = 0; i < matrixfer.size(); ++i)
	{
		for (int j = i; j < matrixfer.size(); ++j)
		{
			Num sum=0;
			sum+=matrixfer[i][j]*p;
			int temp[2];
			temp[0]=i;
			temp[1]=j;
			if(i!=j){
				for(int h=0;h<Hormigas.size();h++){
					std::vector<int>::iterator it;
 					it=search((Hormigas[h]).ciudades.begin(), (Hormigas[h]).ciudades.end(), temp, temp+2,mypredicate);
					if (it!=Hormigas[h].ciudades.end())
					    sum+=Q/Hormigas[h].costo;
					else
						sum+=0;
				}
				matrixfer[i][j]=sum;
				matrixfer[j][i]=sum;
			}

		}
	}
	MEJOR=Hormigas[0];
	Hormigas.clear();
	}
	mostrar_matriz(matrixfer);
	cout<<"MEJOR HORMIGA"<<endl;
	for (int i = 0; i < MEJOR.ciudades.size(); ++i)
	{
		cout<<MEJOR.ciudades[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJOR.costo<<endl;


}

Num Colonia::generar_costo(vector<int> & ciudades){
	Num sum=0;
	for (int i = 1; i < ciudades.size(); ++i)
	{
		//cout<<endl<<ciudades[i-1]<<endl;
		//cout<<endl<<ciudades[i-1]<<endl;
		sum+=matrixdis[ciudades[i-1]][ciudades[i]];
	}
	//cout<<"costo: "<<sum<<endl;
	return sum;
}

void Colonia::mostrar_hormigas(){
	for (int i = 0; i < Hormigas.size(); ++i)
	{
		cout<<"Hormiga: "<<i+1<<endl;
		for (int j = 0; j < Hormigas[i].ciudades.size(); ++j)
		{
			cout<<Hormigas[i].ciudades[j]<<"  ";
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
