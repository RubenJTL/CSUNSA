#ifndef ACS_H
#define ACS_H

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


struct Comptn
{
   bool operator()(tuple<int,Num> & s1, tuple<int,Num> & s2)
   {
       	return get<1>(s1)>get<1>(s2);
   }
};

bool mypredicate (int i, int j) {
  return (i==j);
}


class Colonia{
public:
	Colonia(vector<vector<Num>> & matriz);
	Colonia(vector<vector<Num>> & matriz, vector<vector<Num>> & F);

	void mostrar_hormigas();
	Num generar_costo(vector<int> &);
	Num generar_costo(vector<vector<Num>> & D,vector<vector<Num>> & F, vector<int> &S);
	void run();

	int cantidad_de_hormigas=4;
	Num p=0.99;
	Num a=1;
	Num b=1;
	Num Q=1;
	Num q0=0.7;
	//Num delta=0.05;

	Num e=0.05;
	Num Feromona_Inicial=0.1;
	int cantidad_de_iteraciones=100;
	//int ciudad_inicial=4;

	vector<std::vector<Num>> matrixdis;
	vector<std::vector<Num>> matrixvis;
	vector<std::vector<Num>> matrixfer;
	vector<std::vector<Num>> matrixF;

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

}
Colonia::Colonia(vector<vector<Num>> & v , vector<vector<Num>> & F){
	vector<Num> temp;
	std::vector<std::vector<Num>> Me;
	for (int i = 0; i < v.size(); ++i)
	{
		temp.push_back(0.0);
	}
	for (int i = 0; i < v.size(); ++i)
	{
		matrixvis.push_back(temp);
		matrixfer.push_back(temp);
		Me.push_back(temp);
	}
	matrixdis=v;
	matrixF=F;
	for(int i=0; i<matrixdis.size(); ++i)
        for(int j=0; j<matrixdis.size(); ++j)
            for(int z=0; z<matrixdis.size(); ++z)
                Me[i][j] += matrixdis[i][z] * matrixF[z][j];
	for (int i = 0; i < matrixdis.size(); ++i)
	{
		for (int j = 0; j < matrixdis[i].size(); ++j)
		{
			if (i!=j)
			{
				matrixvis[i][j]=1/Me[i][j];
				matrixfer[i][j]=Feromona_Inicial;
			}
		}
	}
}


void Colonia::run(){
	Hormiga MEJORG;
	Hormiga MEJORL;
	//std::vector<std::vector<Num>> e;
	std::vector<Num> t1;
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
		
		mostrar_matriz(matrixvis);
		mostrar_matriz(matrixfer);

		while(ciudad.size()<matrixdis.size()){
			cout<<ciudad.size()+1<<" CIUDAD"<<endl;
			if(ciudad.size()==1){
				cout<<"Ciudad Inicial "<<pos<<endl;	
			}
			Num q=(Num)(rand()%100)/100.0;
			cout<<"Valor de q "<<q<<endl;
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
			if(q<=q0){
				sort (tn.begin(), tn.end(),Comptn());
				pos=0;
				
			}
			else{
				int tmppos=pos;
				for (int i = 0; i < tn.size(); ++i)
				{
					prob.push_back(get<1>(tn[i])/sum);
					cout<<pos<<"-"<<get<0>(tn[i])<<": "<<get<1>(tn[i])/sum<<endl;
				}
				Num aleatorio=(Num)(rand()%10000)/10000.0;
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
				if (tmppos==pos)
				{
					pos=0;
				}
			//cout<<pos<<endl;
			}
			ciudad.push_back(get<0>(tn[pos]));

			cout<<"Ciudad Siguiente: "<<get<0>(tn[pos])<<endl;
			if(pos!=get<0>(tn[pos])){
				matrixfer[pos][get<0>(tn[pos])]=(1-e)*matrixfer[pos][get<0>(tn[pos])]+e*Feromona_Inicial;
				matrixfer[get<0>(tn[pos])][pos]=(1-e)*matrixfer[get<0>(tn[pos])][pos]+e*Feromona_Inicial;
			}
			pos=get<0>(tn[pos]);	
			tn.clear();
			prob.clear();
		}
		Hormiga H1;
		H1.ciudades=ciudad;
		H1.costo=generar_costo(H1.ciudades);

		for (int escala = 0; escala < 5; ++escala)
		{
			vector<int> ciudad1;
			ciudad1.push_back(tmpp);
			int pos1=tmpp;
			vector<tuple<int,Num>> tn;
			vector<Num> prob;
			
			mostrar_matriz(matrixvis);
			mostrar_matriz(matrixfer);

			while(ciudad1.size()<matrixdis.size()){
				cout<<ciudad1.size()+1<<" ciudad1"<<endl;
				if(ciudad1.size()==1){
					cout<<"ciudad1 Inicial "<<pos1<<endl;	
				}
				Num q=(Num)(rand()%100)/100.0;
				cout<<"Valor de q "<<q<<endl;
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
				if(q<=q0){
					sort (tn.begin(), tn.end(),Comptn());
					pos1=0;
					
				}
				else{
					int tmppos=pos1;
					for (int i = 0; i < tn.size(); ++i)
					{
						prob.push_back(get<1>(tn[i])/sum);
						cout<<pos1<<"-"<<get<0>(tn[i])<<": "<<get<1>(tn[i])/sum<<endl;
					}
					Num aleatorio=(Num)(rand()%10000)/10000.0;
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
					if (tmppos==pos1)
					{
						pos1=0;
					}
				//cout<<pos1<<endl;
				}
				ciudad1.push_back(get<0>(tn[pos1]));

				cout<<"ciudad1 Siguiente: "<<get<0>(tn[pos1])<<endl;
				if(pos1!=get<0>(tn[pos1])){
					matrixfer[pos1][get<0>(tn[pos1])]=(1-e)*matrixfer[pos1][get<0>(tn[pos1])]+e*Feromona_Inicial;
					matrixfer[get<0>(tn[pos1])][pos1]=(1-e)*matrixfer[get<0>(tn[pos1])][pos1]+e*Feromona_Inicial;
				}
				pos1=get<0>(tn[pos1]);	
				tn.clear();
				prob.clear();
			}
			Hormiga H2;
			H2.ciudades=ciudad1;
			H2.costo=generar_costo(H2.ciudades);	
			if (H1.costo>H2.costo)
			{
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
	//	if(MEJOR.costo>Hormigas[0].costo or iteraciones==0)	
	if(MEJORG.costo>Hormigas[0].costo or iteraciones==0){
		MEJORG=Hormigas[0];
	}
	MEJORL=Hormigas[0];

	cout<<"MEJOR HORMIGA LOCAL"<<endl;
	for (int i = 0; i < MEJORL.ciudades.size(); ++i)
	{
		cout<<MEJORL.ciudades[i]<<"  "; 
	}

	cout<<"Mejor Costo: "<<MEJORL.costo<<endl;

	cout<<"MEJOR HORMIGA GLOBAL"<<endl;
	for (int i = 0; i < MEJORG.ciudades.size(); ++i)
	{
		cout<<MEJORG.ciudades[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJORG.costo<<endl;



	for (int i = 0; i < matrixfer.size(); ++i)
	{
		for (int j = 0; j < matrixfer.size(); ++j)
		{
			Num sum=0;
			sum+=matrixfer[i][j]*(p);
			//Num mult;
			int temp[2];
			temp[0]=i;
			temp[1]=j;
			int temp1[2];
			temp1[0]=j;
			temp1[1]=i;
			if(i!=j){
			/*	for(int h=0;h<Hormigas.size();h++){
					std::vector<int>::iterator it;
 					it=search((Hormigas[h]).ciudades.begin(), (Hormigas[h]).ciudades.end(), temp, temp+2,mypredicate);
 					std::vector<int>::iterator it1;
 					it1=search((Hormigas[h]).ciudades.begin(), (Hormigas[h]).ciudades.end(), temp1, temp1+2,mypredicate);
					if (it!=Hormigas[h].ciudades.end() or it1!=Hormigas[h].ciudades.end() )
					    sum+=Q/Hormigas[h].costo;
					else
						sum+=0;
				}*/
				std::vector<int>::iterator it;
 				it=search(MEJORL.ciudades.begin(), MEJORL.ciudades.end(), temp, temp+2,mypredicate);
 				std::vector<int>::iterator it1;
 				it1=search(MEJORL.ciudades.begin(), MEJORL.ciudades.end(), temp1, temp1+2,mypredicate);
				if (it!=MEJORL.ciudades.end() or it1!=MEJORL.ciudades.end() )
				    sum+=(1/MEJORL.costo)*(1-p);
				else
					sum+=0;

				matrixfer[i][j]=sum;
			}

		}
	}
	
	Hormigas.clear();
	}
	cout<<"MEJOR HORMIGA LOCAL"<<endl;
	for (int i = 0; i < MEJORL.ciudades.size(); ++i)
	{
		cout<<MEJORL.ciudades[i]<<"  "; 
	}

	cout<<"Mejor Costo: "<<MEJORL.costo<<endl;

	cout<<"MEJOR HORMIGA GLOBAL"<<endl;
	for (int i = 0; i < MEJORG.ciudades.size(); ++i)
	{
		cout<<MEJORG.ciudades[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJORG.costo<<endl;
}

Num Colonia::generar_costo(vector<vector<Num>> & D,vector<vector<Num>> & F, vector<int> &S){
	Num sum=0;
	for (int i = 0; i < D.size(); ++i)
	{
		for (int j = 0; j < D[i].size(); ++j)
		{
			sum+=F[i][j]*D[S[i]][S[j]];
		}
		//cout<<endl<<ciudades[i-1]<<endl;
		//cout<<endl<<ciudades[i-1]<<endl;
		
	}
	//cout<<"costo: "<<sum<<endl;
	return sum;
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
