#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
//#include <vector>
#include <math.h>
#include <iomanip>

////BOOST
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/container/vector.hpp>


using namespace std;
using namespace boost::numeric::ublas;
using namespace boost::container;



typedef matrix<int> matriz;
typedef double Num;
typedef matrix<Num> Capa;
typedef boost::container::vector<Capa> Capas;


///Operaciones
Num Error(Capa &,Capa &);
Num EA(Capa &,Capa &,int,int);
Capa DelthaO(Capa &,Capa &);
Capa DelthaH(Capa &,Capa &,Capa &);
Num EP(Capa &,Capa &,int,int);

void ChangeW(Capa &,Capa &,Capa &,Num);
//void ChangeW(Capa &,)

///SIGMOIDE
Num Sigmoide(Num);
Capa Sigmoide(Capa,int);

///CREATS

Capas creatHide(int,int,int);
Capa readF(char*,int ,int );

///ESCRITURA DE ARCHIVO
void Guardar_Pesos(char* stri,Capa WH,Capa WO);

////TEST

class RN
{
public:
	RN(Capa & m,Capa & n,Capa &mT,Capa & nT);

	Capa creatInput(Capa &,int);
	Capa creatOutput(Capa &,int);
	Capa creatLayer(int,int);
	Capas creatWHs(int ini,int fin,int cantidad);
	boost::container::vector<std::string> creatFuncion(int cantidad);
	

	boost::container::vector<std::string> Funcion;	

	Capa Input;
	Capa Output;
	Capa Salida_deseada;
	Capa InputTest;
	Capa OutputtTest;
	Capas WH;
	Capas SH;
	Capa SO;


	Capa WO;
	Capa delthaO;
	Capas delthaH;

	Num error, umbral=0.0001, errorant, alpha=1;
};

RN::RN(Capa & m,Capa & n,Capa &mT,Capa & nT) {

	int fin=8,cantidad=1;
	WH=creatWHs(m.size1(),fin,cantidad);
	SH=creatWHs(m.size1(),fin,cantidad);
	WO=creatLayer(fin,n.size1());
	Funcion=creatFuncion(cantidad);
	Num errorT=0;
	errorant=1;
	Num rangoalpha=0.09;

	do{
		errorT=0;
		for(unsigned posicion=0;posicion<m.size1();++posicion){	
			
			Input=creatInput(m,posicion);
			Salida_deseada=creatOutput(n,posicion);
			
			Capa prod=prod(Input,WH[0]);
			cout<<"HOLA"<<endl;
			SH[0]=Sigmoide(prod,0);
			
			for (int i = 1; i < cantidad; ++i)
			{
				
				SH[i]=Sigmoide(prod(SH[i-1],WH[i]),0);
			}

			SO=Sigmoide(prod(SH[cantidad-1],WO),1);
			error=Error(SO,Salida_deseada);
			delthaO=DelthaO(SO,Salida_deseada);
			delthaH[cantidad-1]=DelthaH(SH[cantidad-1],delthaO,WO);
			for (int i = 1; i < cantidad; ++i)
			{
				delthaH[cantidad-1-i]=DelthaH(SH[cantidad-1-i],delthaH[cantidad-1],WH[cantidad-1]);
			}
			ChangeW(WO,delthaO,SH[cantidad-1],alpha);
			for (int i = cantidad-1; i >0 ; --i)
			{
				ChangeW(WH[i],delthaH[i],SH[i-1],alpha);	
			}
			ChangeW(WH[0],delthaH[0],Input,alpha);
			errorT+=error;
		}
		if(errorant-(errorT/m.size2())>=rangoalpha){
			alpha=alpha*0.9;
			rangoalpha=rangoalpha*0.9;
		}
		errorant=errorT/m.size2();
		printf("Error %.20f  alpha  %.20f   rango de alpha %.20f\n",errorT/90,alpha,rangoalpha);
	}while(errorT/m.size2()>umbral);
}

boost::container::vector<std::string> RN::creatFuncion(int cantidad){
	std::string tipo="Sigmoide";
	boost::container::vector<std::string> FM;
	for (int i = 0; i < cantidad+1; ++i)
	{
		printf("Capa %d \n",i);
		FM.push_back(tipo);//[i]=tipo;
	}
	return FM;
}
Capas RN::creatWHs(int ini,int fin,int cantidad){
	int cantidad_anterior=8;
	int cantidad_neuronas=8;
	Capas H;
	H.push_back(creatLayer(ini,cantidad_neuronas));
	for (int i = 1; i < cantidad; ++i)
	{
		//cambiar cantidad_neuronas
		H.push_back(creatLayer(cantidad_anterior,cantidad_neuronas));
		cantidad_anterior=cantidad_neuronas;
	}
	return H;
}

Capa RN::creatInput(Capa & m,int posicion){
	Capa  I(1,m.size2()+1);
	I(0,0)=1.0;
	for(unsigned i=1;i<I.size2();++i){
		I(0,i)=m(posicion,i-1);
	}
	return I;
}

Capa RN::creatOutput(Capa & output,int posicion){
	Capa O(1,output.size2());
	for(unsigned i=0;i<O.size2();++i){
		O(0,i)=output(posicion,i);
	}
	return O;
}

Capa RN::creatLayer(int inputs,int outputs){	
	Capa  I(inputs+1,outputs);
	for(unsigned i=0;i<I.size1();++i){	
		for(unsigned j=0;j<I.size2();++j){
			I(i,j)=((Num) (rand())) / ((Num )(RAND_MAX));
		}
	}
	return I;
}





int main()
{
	srand(time(NULL));
	int contador=0;

	char* inputs= (char *)"XOR2.txt";
	char* deseado=(char *)"XORO2.txt";
	char* inputsT= (char *)"XOR2.txt";
	char* deseadoT=(char *)"XORO2.txt";
	

//	Capa m =readF(inputs,4,90), n =readF(deseado,3,90),mT =readF(inputsT,4,60), nT =readF(deseadoT,3,60);
	//Capa m =readF(inputs,3,8), n =readF(deseado,1,8),mT =readF(inputsT,3,8), nT =readF(deseadoT,1,8);
	Capa m =readF(inputs,2,4), n =readF(deseado,1,4),mT =readF(inputsT,2,4), nT =readF(deseadoT,1,4);
	RN a(m,n,mT,nT);
	///INICIAR CAPAS
    
   /* WH=creatLayer(4,8);
    //H2=creatLayer(8,3);
	WO=creatLayer(8,3);
    */

    /*


	cout<<endl;
	for(unsigned posicion=0;posicion<mT.size1();++posicion){	
		Input=creatInput(mT,posicion);
		Salida_deseada=creatOutput(nT,posicion);
		SH=Sigmoide(prod(Input,WH),0);
		SO=Sigmoide(prod(SH,WO),1);
		

		for(unsigned i=0;i<SO.size2();++i){
			SO(0,i)=round(SO(0,i));
		}
		for(unsigned i=0;i<SO.size2();++i){
			cout<<SO(0,i)<<endl;
		}
	}*/
}


void Guardar_Pesos(char* stri,Capa WH,Capa WO){
	
	ofstream myfile (stri);
	myfile <<WH.size1()<<"\t"<<WH.size2()<<"\n";
    for(unsigned i=0;i<WH.size1();++i){
    	for(unsigned j=0;j<WH.size2();++j){
    		myfile << setprecision(20) << WH(i,j)<<"\t";		
    	}
    	myfile <<"\n";
    }
    myfile <<WO.size1()<<"\t"<<WO.size2()<<"\n";
    for(unsigned i=0;i<WO.size1();++i){
    	for(unsigned j=0;j<WO.size2();++j){
    		myfile << setprecision(20) << WO(i,j)<<"\t";		
    	}
    	myfile <<"\n";
    }
    
    myfile.close();   
}

void TEST(){

}


///Operaciones
Num Error(Capa & So,Capa & Salida_deseada){
	Num sum=0;
	for(unsigned i=0;i<So.size2();++i){
		sum+=pow(So(0,i)-Salida_deseada(0,i),2);
	}
	return (sum/(2.0*So.size2()));
}

Num EA(Capa & So,Capa & Salida_deseada,int j,int boole){
	if(boole==1){
	return(So(0,j)-Salida_deseada(0,j));
	}
	else{
		Num sum=0;
		for(unsigned i=0;i<Salida_deseada.size2();++i){
			sum+=So(0,i)*Salida_deseada(j,i);
		}
		return sum;
	}
}

Capa DelthaO(Capa & So,Capa & Salida_deseada){
	Capa D(1,So.size2());
	for(unsigned i=0;i<D.size2();++i){
		D(0,i)=EA(So,Salida_deseada,i,1)*So(0,i)*(1-So(0,i));
	}
	return D;
}

Capa DelthaH(Capa & SH,Capa & deltha,Capa & W){
	Capa D(1,SH.size2()-1);
	for(unsigned i=0;i<D.size2();++i){
		D(0,i)=EA(deltha,W,i,0)*SH(0,i+1)*(1-SH(0,i+1));
	}
	return D;
}

Num EP(Capa & deltha,Capa &So,int j,int i){
	return (deltha(0,j)*So(0,i));
}

void ChangeW(Capa &W,Capa & deltha,Capa & SA,Num alpha){
	for(unsigned i=0;i<W.size2();++i){
		for(unsigned j=0;j<W.size1();++j){
			W(j,i)=W(j,i)-alpha*EP(deltha,SA,i,j);
		}
	}
}





///LECTURA DE ARCHIVO
Capa readF(char* file,int caracteristicas, int neuronas){
	Capa m (neuronas, caracteristicas);
	Num val;
    ifstream f(file);
    for (unsigned i = 0; i < m.size1 (); ++ i){
        for (unsigned j = 0; j < m.size2 (); ++ j){
            f>>m(i,j);
        }
    }
    return m;
}

///SIGMOIDE
Num Sigmoide(Num T){
	return ((1)/(1+exp(-T)));
}
Capa Sigmoide(Capa neta,int boole){
	if(boole==0){
		Capa S(neta.size1(),neta.size2()+1);
		for(unsigned i=0;i<S.size1();++i){
			for(unsigned j=0;j<S.size2();++j){
				if(j==0) S(i,j)=1.0;
				else S(i,j)=Sigmoide(neta(i,j-1));
			}
		}
		return S;
	}
	else {
		Capa S(neta.size1(),neta.size2());
		for(unsigned i=0;i<S.size1();++i){
			for(unsigned j=0;j<S.size2();++j){
				S(i,j)=Sigmoide(neta(i,j));
			}
		}
		return S;	
	}
}