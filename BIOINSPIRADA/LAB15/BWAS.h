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


Num normal(Num x, Num desviacion);

Num valor_x(Num lim_inf,Num lim_sup, Num desviacion,Num aleatorio,Num delta);

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
	Colonia(vector<vector<Num>> & ,vector<vector<Num>> & );

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
	int cantidad_de_iteraciones=1000;
	int ciudad_inicial=4;//=4;

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
	Hormiga PEORL;
	int ci=0;
	
	for (int iteraciones = 0; iteraciones < cantidad_de_iteraciones; ++iteraciones)
	{
		cout<<"ITERACION: "<<iteraciones<<endl;
		int pos;
		for (int hs = 0; hs < cantidad_de_hormigas; ++hs)
		{
		cout<<"HORMIGA :"<<hs<<endl;
		vector<int> ciudad;

		ciudad_inicial=(int) (rand()) / (int) (RAND_MAX/matrixdis.size());
		//ciudad.push_back(pos);
		ciudad.push_back(ciudad_inicial);
		vector<tuple<int,Num>> tn;
		vector<Num> prob;
		pos=ciudad_inicial;//4;//s(int) (rand()) / (int) (RAND_MAX/matrixdis.size());//ciudad_inicial;
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
		H1.costo=generar_costo(matrixdis,matrixF,H1.ciudades);//generar_costo(H1.ciudades);
		Hormigas.push_back(H1);
		
		ciudad.clear();

		}
	sort (Hormigas.begin(), Hormigas.end(),Comp());
	mostrar_hormigas();
	if(MEJORG.costo>Hormigas[0].costo or iteraciones==0){
		MEJORG=Hormigas[0];
		ci=0;
	}else{
		ci++;
	}
	if (ci==cantidad_de_iteraciones*0.2)
	{
		for (int i = 0; i < matrixdis.size(); ++i)
		{
			for (int j = 0; j < matrixdis[i].size(); ++j)
			{
				if (i!=j)
				{
					matrixfer[i][j]=Feromona_Inicial;
				}
			}
		}
	}
	MEJORL=Hormigas[0];
	PEORL=Hormigas[Hormigas.size()-1];

	cout<<"MEJOR HORMIGA LOCAL"<<endl;
	for (int i = 0; i < MEJORL.ciudades.size(); ++i)
	{
		cout<<MEJORL.ciudades[i]<<"  "; 
	}

	cout<<"Mejor Costo: "<<MEJORL.costo<<endl;

	cout<<"PEOR HORMIGA LOCAL"<<endl;
	for (int i = 0; i < PEORL.ciudades.size(); ++i)
	{
		cout<<PEORL.ciudades[i]<<"  "; 
	}

	cout<<"Peor Costo: "<<PEORL.costo<<endl;


	cout<<"MEJOR HORMIGA GLOBAL"<<endl;
	for (int i = 0; i < MEJORG.ciudades.size(); ++i)
	{
		cout<<MEJORG.ciudades[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJORG.costo<<endl;


	for (int i = 0; i < matrixfer.size(); ++i)
	{
		for (int j = i; j < matrixfer.size(); ++j)
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
				/*for(int h=0;h<Hormigas.size();h++){
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
 				it=search(MEJORG.ciudades.begin(), MEJORG.ciudades.end(), temp, temp+2,mypredicate);
 				std::vector<int>::iterator it1;
 				it1=search(MEJORG.ciudades.begin(), MEJORG.ciudades.end(), temp1, temp1+2,mypredicate);
				if (it!=MEJORG.ciudades.end() or it1!=MEJORG.ciudades.end() )
				    sum+=1/MEJORG.costo;
				else
					sum+=0;

				matrixfer[i][j]=sum;
				matrixfer[j][i]=sum;


				std::vector<int>::iterator it2;
 				it2=search(PEORL.ciudades.begin(), PEORL.ciudades.end(), temp, temp+2,mypredicate);
 				std::vector<int>::iterator it3;
 				it3=search(PEORL.ciudades.begin(), PEORL.ciudades.end(), temp1, temp1+2,mypredicate);
 				if (it!=MEJORG.ciudades.end() or it1!=MEJORG.ciudades.end() ){

 				}	    
				else if(it2!=PEORL.ciudades.end() or it3!=PEORL.ciudades.end() ){
					matrixfer[i][j]=(1-p)*matrixfer[i][j];
					matrixfer[j][i]=(1-p)*matrixfer[j][i];
				}

			}

		}
	}
	
		Num umbral;
		Num sum=0;
		int count=0;
		for (int i = 0; i < matrixfer.size(); ++i)
		{
			for (int j = 0; j < matrixfer[i].size(); ++j)
			{
				if(i!=j){
					int temp[2];
					temp[0]=i;
					temp[1]=j;
					int temp1[2];
					temp1[0]=j;
					temp1[1]=i;
					std::vector<int>::iterator it;
	 				it=search(MEJORG.ciudades.begin(), MEJORG.ciudades.end(), temp, temp+2,mypredicate);
	 				std::vector<int>::iterator it1;
	 				it1=search(MEJORG.ciudades.begin(), MEJORG.ciudades.end(), temp1, temp1+2,mypredicate);
					if (it!=MEJORG.ciudades.end() or it1!=MEJORG.ciudades.end() ){
					    sum+=matrixfer[i][j];
						count++;
					}
					else{
						sum+=0;
					}
				}
			}
		}
		umbral=sum/count;
		for (int i = 0; i < matrixfer.size(); ++i)
		{
			for (int j = 0; j < matrixfer[i].size(); ++j)
			{
				if(i!=j){
					Num pm=(Num)(rand()%100)/100.0;	
					if (pm<0.2)
					{
						Num aleatorio=(Num)(rand()%1000)/1000.0;
						Num v=valor_x(-1*umbral,umbral,umbral,aleatorio,0.001);
						matrixfer[i][j]=matrixfer[i][j]+v;
						matrixfer[j][i]=matrixfer[j][i]+v;
					}
				}
			}
		}

		
	Hormigas.clear();
	}
	
	cout<<"MEJOR HORMIGA GLOBAL"<<endl;
	for (int i = 0; i < MEJORG.ciudades.size(); ++i)
	{
		cout<<MEJORG.ciudades[i]<<"  "; 
	}
	cout<<"Mejor Costo: "<<MEJORG.costo<<endl;
	mostrar_matriz(matrixfer);


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

Num normal(Num x, Num desviacion){
	Num retorno=-0.5*((x/desviacion)*(x/desviacion));
	retorno=exp(retorno);
	retorno=retorno/(desviacion*sqrt(M_PI*2));
	return retorno;
}

Num valor_x(Num lim_inf,Num lim_sup, Num desviacion,Num aleatorio,Num delta){
	Num area=0;
	Num aux_suma, aux=normal(lim_inf,desviacion);

	for (double i = lim_inf+delta; i < lim_sup; i+=delta)
	{
		aux_suma=normal(i,desviacion);
		area+=(aux+aux_suma);
		if((area*(delta/2))>aleatorio){
			return i;
		}
		aux=aux_suma;
	}
	return -1;//*std::numeric_limits<double>::max();
}

#endif	
