#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>


#define RANDOM_RANGE 31


using namespace std;

typedef double Num;
 
string convert_to_binary(int,int);
int convert_to_decimal(string);


Num function(int , int);
Num function(int);


typedef struct {
	Num genotipo[2];
	Num aptitud;
}Individuo;



struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////comparador para maxheap de hijos

struct Comp1
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////

struct Comp2
{
   bool operator()(tuple<int,Num>& s1, tuple<int,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////




class genetico{
public:
	


	genetico(int poblacion);
	genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes, Num cross);

	void run();
	void mostrar_poblacion();
	void mostrar_poblacion_e();
	void mostrar_hijos_e();
	void reproducir();
	bool Mutar(Individuo &hijo, Num alpha1);
	void new_generation();
	tuple<bool,Individuo> crear_hijo(tuple<Num,Num> hijo,Num randomc);
	void save();

	tuple<Num,Num>CrossOver(int pos1,int pos2);

	int buscar_ganador();


	vector<Individuo> I;

	Num mutacion=0.5;
	Num prob_cross=0.9;
	Num sup;
	Num inf;
	int iteraciones=10;
	int cromosomas=5;
	int participantes=5;
	Num betha=0.5;
	Num alpha=0.5;
	int poblacion; 
	vector<Individuo> hijos;

};

void genetico::run(){
	cout<<"Tamanho de la poblacion: "<<this->poblacion<<endl;
	cout<<"Cantidad de iteraciones: "<<this->iteraciones<<endl;
	cout<<"Limite superior: "<<this->sup<<endl;
	cout<<"Limite inferior: "<<this->inf<<endl;
	cout<<"Alpha: "<<this->alpha<<endl;
	cout<<"Betha: "<<this->betha<<endl;
	cout<<"Probabilidad de mutacion: "<<this->mutacion<<endl<<"Mutacion Simple"<<endl<<endl;
	cout<<"Probabilidad de cruzamiento: "<<this->prob_cross<<endl;
	//buscar_ganador();
	for (int i = 0; i < this->iteraciones; ++i)
   	{
   		if(i==0){
   			cout<<endl<<"Generando Poblacion Inicial"<<endl;
   		}
   		mostrar_poblacion();
   		cout<<endl<<"Iteracion: "<<i<<endl;
   		cout<<endl<<"Evaluando individuos "<<endl;
   		mostrar_poblacion_e();
   		cout<<endl<<"Selecion de individuos - Metodo de Enfrentamiento"<<endl;
   		

	    reproducir();
	    cout<<endl<<"Seleccionando Siguiente Poblacion"<<endl;
	    mostrar_poblacion_e();
	    mostrar_hijos_e();		    
	    new_generation();
	    cout<<endl;
	    //a.save();
		//}	
   	}

   	cout<<endl<<"Ultima Poblacion"<<endl;
   	mostrar_poblacion_e();

}

genetico::genetico(int poblacion,Num alpha,Num inf, Num sup,int iteraciones, Num mutacion,int participantes, Num cross){
	srand (time(NULL));
	this->poblacion=poblacion;
	this->iteraciones=iteraciones;
	this->mutacion=mutacion;
	this->alpha=alpha;
	this->inf=inf;
	this->sup=sup;
	this->participantes=participantes;
	this->prob_cross=cross;
	Num bet=(Num)(rand()%100)/100.0;
	if(bet>0.5){
		this->betha=bet+alpha;	
	}else{
		this->betha=bet-alpha;	
	}
	Individuo I1;
	for(unsigned i=0;i<poblacion;++i){
		Num neg=(Num)(rand()%100)/100.0;
		Num r2 = static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/sup));
		Num r1 = static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/sup));
		if(neg<0.5 and inf<0){
			r2=r2*(-1);
		}
		neg=(Num)(rand()%100)/100.0;
		if(neg<0.5 and inf<0 ){
			r1=r1*(-1);
		}
		I1.genotipo[0]=r2;
		I1.genotipo[1]=r1;
		I1.aptitud=function(I1.genotipo[0],I1.genotipo[1]);
		
		I.push_back(I1);
	}
}


tuple<Num,Num> genetico::CrossOver(int pos1,int pos2){

	Num C1,C2;
	C1=I[pos1].genotipo[0]+(betha*(I[pos2].genotipo[0]-I[pos1].genotipo[0]));
	C2=I[pos1].genotipo[1]+(betha*(I[pos2].genotipo[1]-I[pos1].genotipo[1]));
	auto hijo=make_tuple(C1,C2);
	
	return hijo;
}
tuple<bool,Individuo> genetico::crear_hijo(tuple<Num,Num> hijo,Num randomc){
	Individuo hijo1;
	hijo1.genotipo[0]=get<0> (hijo);
	hijo1.genotipo[1]=get<1> (hijo);
	bool muto=Mutar(hijo1,randomc);
	hijo1.aptitud=function(hijo1.genotipo[0],hijo1.genotipo[1]);
	hijos.push_back(hijo1);
	return make_tuple(muto,hijo1);
}

bool genetico::Mutar(Individuo &hijo, Num alpha1){
	
	int randomp,random1;

	if(this->mutacion>=alpha1){
		Num r1 = static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/sup));
		
		randomp=(Num)(rand()%100)/100.0;
		random1=(Num)(rand()%100)/100.0;
		if(random1<0.5 and inf<0){
			r1=r1*(-1);
		}

		if(randomp>=0.5){
			hijo.genotipo[1]=r1;
		}else{
			hijo.genotipo[0]=r1;
		}
		return true;
	}
	return false;
	
}

void genetico::new_generation(){
	bool t=true;
	unsigned j=0,l=hijos.size()-1;
	if(hijos.size()!=0){
	while(j<I.size() and l>0 ){
		if(I[j].aptitud<hijos[l].aptitud){
			I[j].genotipo[0]=hijos[l].genotipo[0];
			I[j].genotipo[1]=hijos[l].genotipo[1];
			I[j].aptitud=hijos[l].aptitud;
			l--;
			j++;
		}else{
			break;
		}
	}
	}
	hijos.clear();
}

void genetico::mostrar_poblacion(){
	cout<<endl;
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")"<<"\t"<<I[i].genotipo[0]<<"\t"<<I[i].genotipo[1]<<endl;
	}
	
}

void genetico::mostrar_poblacion_e(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")\t"<<"\t"<< I[i].genotipo[0]<<"\t"<< I[i].genotipo[1]<<"\t"<< I[i].aptitud<<endl;
	}
	
}

void genetico::mostrar_hijos_e(){
	for(unsigned i=0;i<hijos.size();++i){
		cout<<this->poblacion+1+i<<")\t"<< hijos[i].genotipo[0]<<"\t"<< hijos[i].genotipo[1]<<"\t"<< hijos[i].aptitud<<endl;
	}
}

void genetico::reproducir(){
	Num random1,random2,random_cross;
	int pos1,pos2;
	Num randomc;
	
	for (unsigned i = 0; i < poblacion/2; ++i)
	{
		cout<<endl<<"Participantes Padre"<<endl;
		pos1=buscar_ganador();//retorna la pocision
		//cout<<"HOla"<<endl;
		cout<<endl<<"Participantes Madre"<<endl;
		pos2=buscar_ganador();//retorna la pocision 
		while(pos2==pos1){
			cout<<endl<<"Participantes Madre"<<endl;
			pos2=buscar_ganador();//retorna la pocision 
		}
		random_cross=(Num)(rand()%100)/100.0;
		cout<<endl<<"Padre: "<<pos1+1<<endl<<"Madre: "<<pos2+1<<endl;
		
		cout<<endl<<"Cruzamiento"<<endl;
			if(prob_cross>=random_cross){
			tuple<Num,Num> CromosomasXY=CrossOver(pos1,pos2);
			//CromosomasXY2=CrossOver(pos2,pos1);
			randomc=(Num)(rand()%100)/100.0;	
			auto muto=crear_hijo(CromosomasXY,randomc);
			if(get<0>(muto)==true){
				cout<<"muto hijo 1"<<endl;
				cout<<(get<1>(muto)).genotipo[0]<<"\t"<<(get<1>(muto)).genotipo[1]<<endl;
			}else{
				cout<<(get<1>(muto)).genotipo[0]<<"\t"<<(get<1>(muto)).genotipo[1]<<endl;
			}
		}
	}
	std::sort (hijos.begin(), hijos.end(), Comp1());
	std::sort (I.begin(), I.end(),Comp());
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();
	
}

int genetico::buscar_ganador(){
	std::vector<tuple<int,Num>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->poblacion);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->poblacion);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,(I[selec]).aptitud);
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp2());
	


	for (int i = 0; i < participantes; ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}

	return (get<0>(seleccionados[participantes-1]));
}
/*

Num genetico::function(string x ){
	Num f=0;
	Num x_w=0;
	Num penalty;
	Num sum_w=0;
	
	for (int i = 0; i < cromosomas; ++i)
	{
		if(x[i]=='0'){
			f+=0*p[i];
		}else if(x[i]=='1'){
			f+=1*p[i];
		}
	}
	cout<<endl<<f<<endl;
	for (int i = 0; i < cromosomas; ++i)
	{
		sum_w+=w[i];
	}
	cout<<endl<<"w"<<sum_w<<endl;
	for (int i = 0; i < cromosomas; ++i)
	{
		if(x[i]=='0'){
			x_w += 0*w[i];
		}else if(x[i]=='1'){
			x_w += 1*w[i];
		}
	}
	penalty=sum_w * abs(x_w-W);
	return (f-penalty);


	//return(pow(x,2));
	//return(((pow(-x,2))/10)+(3*x));
}*/

Num function(int x ){
	//return(pow(x,2));
	return(((pow(-x,2))/10)+(3*x));
}


Num function(int x,int y){
	//return(pow(x,2));
	Num sup=pow((sin(pow(x,2)+pow(y,2))),2)-0.5;
	Num inf=pow(1.0+0.001*(pow(x,2)+pow(y,2)),2);

	return(0.5-(sup)/(inf));
}

string convert_to_binary(int a,int cromosomas){
	string bin="";
	unsigned int var = (unsigned int)a;
    unsigned int contador, inicio = pow(2,cromosomas-1); // 2^(8-1) = 128

    for(contador = inicio; contador > 0; contador >>= 1){ // El contador se desplaza un bit a la derecha cada ciclo
        if(contador & var) // Si contador AND var == 1
            bin+="1";
        else
            bin+="0";
    }
    return bin;
}

int convert_to_decimal(string str){
	int decimal=0;
	int a=str.length()-1;
	for(int i=0;i<str.length();i++){
		switch(str[i]){
			case '1':
				decimal+=1*pow(2,a);
				a--;
				break;
			case '0':
				a--;
				break;
		}
	}
	return decimal;
}




#endif	
