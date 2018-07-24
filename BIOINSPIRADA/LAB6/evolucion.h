#ifndef EVOLUCION_H
#define EVOLUCION_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

string E="NSSNSSNSSNSSNSS";
class estados
{
public:
	estados(int nombre,int activo, char entrada[2],char salida[2]);
	estados(int nombre);
	void mostrar_estado();
	~estados();
	

	int activo;
	char entrada[2];
	char salida[2];
	estados* salidas[2];
	
	int nombre;
};

void estados::mostrar_estado(){
	cout<<"Estado: ";
	if(nombre==0){
		cout<<"A";
	}
	if(nombre==1){
		cout<<"B";
	}
	if(nombre==2){
		cout<<"C";
	}
	if(nombre==3){
		cout<<"D";
	}
	cout<<endl;
	if(activo==1){
		cout<<"entradas: "<<entrada[0]<<" "<<entrada[1]<<endl;
		cout<<"salidas: "<<salida[0]<<" "<<salida[1]<<endl;
		cout<<"estados de salida: ";
		for(int i=0;i<2;i++){
			if(salidas[i]->nombre==0){
				cout<<"A ";
			}
			if(salidas[i]->nombre==1){
				cout<<"B ";
			}
			if(salidas[i]->nombre==2){
				cout<<"C ";
			}
			if(salidas[i]->nombre==3){
				cout<<"D ";
			}	
		}
	}else{
		cout<<"Estado desactivado"<<endl;
	}
	cout<<endl;
}

estados::estados(int nombre,int activo, char entrada[2],char salida[2]){
	this->nombre=nombre;
	this->activo=activo;
	this->entrada[0]=entrada[0];
	this->entrada[1]=entrada[1];
	this->salida[0]=salida[0];
	this->salida[0]=salida[0];
	this->salidas[0]=NULL;
	this->salidas[1]=NULL;
}
estados::estados(int nombre){
	this->nombre=nombre;
	this->activo=1;
	this->salidas[0]=NULL;
	this->salidas[1]=NULL;	
}

struct Comp
{
   bool operator()(tuple<vector<estados*>,double>& s1, tuple<vector<estados*>,double>& s2)
   {
       return get<1>(s1) > get<1>(s2);
   }
}; ////

struct Comp1
{
   bool operator()(tuple<vector<estados*>,double>& s1, tuple<vector<estados*>,double>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////



class MEF{
public:

	friend void swap(estados* &a, estados* &b)
    {
        using std::swap; // bring in swap for built-in types

        swap(a->activo, b->activo);
        swap(a->entrada[0], b->entrada[0]);
        swap(a->entrada[1], b->entrada[1]);
        swap(a->salida[0], b->salida[0]);
        swap(a->salida[1], b->salida[1]);
        swap(a->salidas[0], b->salidas[0]);
        swap(a->salidas[1], b->salidas[1]);
        swap(a->nombre, b->nombre);
    }
		

	MEF(int numero_de_poblacion,string entradas,string salidas);

	vector<estados*> crear_maquina();
	void mutar(vector<estados*> &);
	void quitar_maquina(int nombre,vector<estados*> &maquina);
	void desactivar_estado(vector<estados*> &maquina);
	void cambiar_estado_inicial(vector<estados*> &maquina);
	void cambiar_un_simbolo_de_entrada(vector<estados*> &maquina);
	void cambiar_un_simbolo_de_salida(vector<estados*> &maquina);
	void activar_estado(vector<estados*> &maquina);

	void run();


	string generar_resultado(estados*);
	void generar_resultado(estados* estado, int pos,string &out);
	double generar_aptitud(string);


	void mostrar_maquinas();
	void mostrar_maquina(vector<estados*>);
	void mostrar_hijos();

	vector<tuple<vector<estados*>,double>> maquinas;
	vector<tuple<vector<estados*>,double>> hijos;
	int poblacion=4;
	int numero_de_estados=4;
	string entrada;
	string salida;

};
void MEF::mostrar_hijos(){
	for (int i = 0; i < hijos.size(); ++i)
	{
		cout<<"MAQUINAS HIJAS "<<i+1<<endl;
		for (int j = 0; j < get<0>(hijos[i]).size(); ++j)
		{
			//cout<<maquinas[i][j].size();
			get<0>(hijos[i])[j]->mostrar_estado();
			cout<<endl;
		}

		cout<<get<1>(hijos[i])<<endl;
		cout<<endl;
	}
}

void MEF::run(){
	mostrar_maquinas();
	//for (int i = 0; i < 5; ++i)
	int l=0;
	double sum;
	do{

		cout<<"ITERACION "<<l<<endl;
		mostrar_maquinas();
		while(hijos.size()<4){
			
			int random_estado1=(int)(rand())/((int)RAND_MAX/poblacion);
			vector<estados*> tmp(get<0>(maquinas[random_estado1]));
		//	cout<<endl<<"ANTES"<<endl;
			//cout<<endl<<"MUTADA"<<endl;
			//mostrar_maquina(tmp);
		//	cout<<endl<<"ORIGINAL"<<endl;
			//mostrar_maquina(get<0>(maquinas[random_estado1]));
			mutar(tmp);
		//	cout<<endl<<"DESPUES	"<<endl;
	//		cout<<endl<<"MUTADA de maquina "<<random_estado1<<endl;
		//	mostrar_maquina(tmp);
			//cout<<endl<<"ORIGINAL"<<endl;
			//mostrar_maquina(get<0>(maquinas[random_estado1]));	
			string resultado=generar_resultado(tmp[0]);
			double aptitud=generar_aptitud(resultado);
			hijos.push_back(make_tuple(tmp,aptitud));
			//mostrar_hijos();
			//cout<<"HOLII   "<<hijos.size()<<endl;
			//	mostrar_maquinas();
		}
	
		//cout<<endl<<"PRUEBA";
		//mostrar_hijos();
		cout<<endl;

		mostrar_maquinas();
		cout<<endl;
		mostrar_hijos();

		std::sort (hijos.begin(), hijos.end(), Comp());
		std::sort (maquinas.begin(), maquinas.end(),Comp1());
		
		for (int i = 0; i < poblacion/2; ++i)
		{
			maquinas[i]=hijos[i];
		}
		hijos.clear();
		for (int i = 0; i < poblacion/2; ++i)
		{
			string resultado=generar_resultado(get<0>(maquinas[i])[0]);
			double aptitud=generar_aptitud(resultado);
			get<1>(maquinas[i])=aptitud;
		}

		sum=0;
		for (int i = 0; i < poblacion; ++i)
		{
			sum+=get<1>(maquinas[i]);
		}
		l++;
	}while(l<800 and sum/poblacion!=1);
	cout<<"POBLACION FINAL"<<endl;
	cout<<"TOTAL DE ITERACIONES: "<<l<<endl;
	mostrar_maquinas();	
}

void MEF::quitar_maquina(int nombre,vector<estados*> &maquina){
	
	for (int i = 0; i < maquina.size(); ++i)
	{
		if(maquina[i]->salidas[0]->nombre==nombre){
			
			int random_estado=(int)(rand())/((int)RAND_MAX/maquina.size());
			while(maquina[random_estado]->nombre==nombre or maquina[i]->nombre==random_estado or maquina[random_estado]->activo==0){
				cout<<"AQI"<<nombre<<" "<<random_estado<<"  "<<maquina[i]->nombre<<" "<<maquina[random_estado]->activo<<endl;
				random_estado=(int)(rand())/((int)RAND_MAX/maquina.size());
			}
			maquina[i]->salidas[0]=maquina[random_estado];		
		}else if(maquina[i]->salidas[1]->nombre==nombre){
			int random_estado=(int)(rand())/((int)RAND_MAX/maquina.size());
			while(maquina[random_estado]->nombre==nombre  or maquina[random_estado]->activo==0){
				random_estado=(int)(rand())/((int)RAND_MAX/maquina.size());
			}
			maquina[i]->salidas[1]=maquina[random_estado];
		}
	}
}

void MEF::desactivar_estado(vector<estados*> &maquina){
	int count=0;
	for (int i = 0; i < maquina.size(); ++i)
	{
		if(maquina[i]->activo==1)
			count++;
	}
	if(count>2){
		int random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
		while(random_estado==0 or maquina[random_estado]->activo==0 ){
			random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
		}
		maquina[random_estado]->activo=0;
		quitar_maquina(maquina[random_estado]->nombre,maquina);
	}
}

void MEF::cambiar_estado_inicial(vector<estados*> &maquina){
	int random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	while(random_estado==0 or maquina[random_estado]->activo==0){
		random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	}
	swap(maquina[0],maquina[random_estado]);
}

void MEF::cambiar_un_simbolo_de_entrada(vector<estados*> &maquina){
	int random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	while(random_estado==0 or maquina[random_estado]->activo==0){
		random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	}
	char tmp=maquina[random_estado]->entrada[0];
	maquina[random_estado]->entrada[0]=maquina[random_estado]->entrada[1];
	maquina[random_estado]->entrada[1]=tmp;
}

void MEF::cambiar_un_simbolo_de_salida(vector<estados*> &maquina){
	int random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	while(random_estado==0 or maquina[random_estado]->activo==0){
		random_estado=(int)(rand())/((int)RAND_MAX/maquinas.size());	
	}
	
	int random_salida=(int)(rand())/((int)RAND_MAX/salida.size());
	int random_simbolo=(int)(rand())/((int)RAND_MAX/salida.size());	

	maquina[random_estado]->salida[random_salida]=salida[random_salida];
}

void MEF::activar_estado(vector<estados*> &maquina){
	for (int i = 0; i < maquina.size(); ++i)
	{
		if(maquina[i]->activo==0){
			maquina[i]->activo=1;
			int random_estado1=(int)(rand())/((int)RAND_MAX/maquina.size());
			
			while(random_estado1==i or maquina[random_estado1]->activo==0){
				random_estado1=(int)(rand())/((int)RAND_MAX/maquina.size());
			}
			int random_estado2=(int)(rand())/((int)RAND_MAX/maquina.size());
			while(random_estado2==random_estado1 or maquina[random_estado2]->activo==0){
				random_estado2=(int)(rand())/((int)RAND_MAX/maquina.size());
			}

			int random_salida;
			int random_entrada;
			int random_entrada1;
			
			maquina[i]->salidas[0]=maquina[random_estado1];
			random_salida=(int)(rand())/((int)RAND_MAX/salida.length());
			random_entrada=(int)(rand())/((int)RAND_MAX/entrada.length());
			maquina[i]->entrada[0]=entrada[random_entrada];
			maquina[i]->salida[0]=salida[random_salida];

			maquina[i]->salidas[1]=maquina[random_estado2];
			random_salida=(int)(rand())/((int)RAND_MAX/salida.length());
			random_entrada1=(int)(rand())/((int)RAND_MAX/entrada.length());
			while(random_entrada==random_entrada1){
				random_entrada1=(int)(rand())/((int)RAND_MAX/entrada.length());
			}
			maquina[i]->entrada[1]=entrada[random_entrada1];
			maquina[i]->salida[1]=salida[random_salida];
			break;
		}
	}
}

void MEF::mutar(vector<estados*> & maquina){
	double operador_de_mutacion=(double)(rand()%100)/100.0;
	if(operador_de_mutacion>=0.0 and  operador_de_mutacion<0.2){
		cout<<endl<<"desactivado estado"<<endl;
		desactivar_estado(maquina);
	}
	else if(operador_de_mutacion>=0.2 and  operador_de_mutacion<0.4){
		cout<<endl<<"cambiando estado inicial"<<endl;
		cambiar_estado_inicial(maquina);
	}
	else if(operador_de_mutacion>=0.4 and  operador_de_mutacion<0.6){
		cout<<endl<<"cambiando simbolo de entrada"<<endl;
		cambiar_un_simbolo_de_entrada(maquina);
	}
	else if(operador_de_mutacion>=0.6 and  operador_de_mutacion<0.8){
		cout<<endl<<"cambiar_un_simbolo_de_salida"<<endl;
		cambiar_un_simbolo_de_salida(maquina);
	}
	else if(operador_de_mutacion>=0.8 and  operador_de_mutacion<1.0){
		cout<<endl<<"activado estado"<<endl;
		activar_estado(maquina);
	}
}

string MEF::generar_resultado(estados* estado){
	int i=0;
	string out="";
	generar_resultado(estado,i,out);
	return out;
}

void MEF::generar_resultado(estados* estado, int pos,string &out){
	if(pos<E.length()){
		if(estado->entrada[0]==E[pos]){
			out+=estado->salida[0];
			generar_resultado(estado->salidas[0],pos+1,out);
		}
		else if(estado->entrada[1]==E[pos]){
			out+=estado->salida[1];
			generar_resultado(estado->salidas[1],pos+1,out);
		}
	}

}
double MEF::generar_aptitud(string out){
	double sum=0;
	for (int i = 1; i < E.length(); ++i)
	{
		//cout<<E[i]<<" "<<out[i-1]<<endl;
		if(E[i]==out[i-1]){
			sum++;
		}
	}
	sum=sum/(E.length()-1);
	return sum;
}


MEF::MEF(int numero_de_poblacion,string entrada,string salida){
	this->entrada=entrada;
	this->salida=salida;
	for (int i = 0; i < poblacion; ++i)
	{
		vector<estados*> maquina=crear_maquina();
		string prediccion=generar_resultado(maquina[0]);
		double aptitud=generar_aptitud(prediccion);
		maquinas.push_back(make_tuple(maquina,aptitud));
		/*
		cout<<prediccion<<endl;
		cout<<E<<endl;
		cout<<(generar_aptitud(prediccion))*(E.length()-1)<<endl;
		cout<<endl;*/
	}
	

}

void MEF::mostrar_maquina(vector<estados*> maquina){
	for (int i = 0; i < maquina.size(); ++i)
	{	//cout<<maquinas[i][j].size();
		maquina[i]->mostrar_estado();
		cout<<endl;
	}
}

void MEF::mostrar_maquinas(){
	for (int i = 0; i < maquinas.size(); ++i)
	{
		cout<<"MAQUINA "<<i+1<<endl;
		for (int j = 0; j < get<0>(maquinas[i]).size(); ++j)
		{
			//cout<<maquinas[i][j].size();
			get<0>(maquinas[i])[j]->mostrar_estado();
			cout<<endl;
		}

		cout<<get<1>(maquinas[i])<<endl;
		cout<<endl;
	}
}

vector<estados*> MEF::crear_maquina(){
	vector<estados*> maquinas;
	for (int i = 0; i < numero_de_estados; ++i)
	{
		estados* newEstado=new estados(i);
		maquinas.push_back(newEstado);
	}
	for(int i = 0; i < numero_de_estados; ++i){
		int random_estado1=(int)(rand())/((int)RAND_MAX/maquinas.size());
		int random_estado2=(int)(rand())/((int)RAND_MAX/maquinas.size());
		while(random_estado2==random_estado1){
			random_estado2=(int)(rand())/((int)RAND_MAX/maquinas.size());
		}

		int random_salida;
		int random_entrada;
		int random_entrada1;
		
		maquinas[i]->salidas[0]=maquinas[random_estado1];
		random_salida=(int)(rand())/((int)RAND_MAX/salida.length());
		random_entrada=(int)(rand())/((int)RAND_MAX/entrada.length());
		maquinas[i]->entrada[0]=entrada[random_entrada];
		maquinas[i]->salida[0]=salida[random_salida];

		maquinas[i]->salidas[1]=maquinas[random_estado2];
		random_salida=(int)(rand())/((int)RAND_MAX/salida.length());
		random_entrada1=(int)(rand())/((int)RAND_MAX/entrada.length());
		while(random_entrada==random_entrada1){
			random_entrada1=(int)(rand())/((int)RAND_MAX/entrada.length());
		}
		maquinas[i]->entrada[1]=entrada[random_entrada1];
		maquinas[i]->salida[1]=salida[random_salida];

	}
	return maquinas;
}
#endif	