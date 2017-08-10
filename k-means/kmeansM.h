#ifndef KMEANSM_H
#define KMEANSM_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <math.h>

#include <limits>/// MAXIMO DOUBLE
#include <cstddef>
#include <cfloat>


#define RANDOM_RANGE 8192

using namespace std;

typedef double Num;
typedef vector<Num> dato;
typedef vector<dato> datos;

typedef vector<Num> distancias;

Num distancia(dato, dato);



class kmeans
{
public:
//	kmeans(int);
//	kmeans(int,int);
	kmeans(string,int);


	void mostrar();
	void mostrar_centros();
	void mostrar_distancias();
	void mostrar_cluster();
	void run();
	void clasificar();
	void cambiar_centros();
	void save();
	void load(string);
	void test(string);
	void test();
	//~kmeans();

	datos dats;
	datos centros;

	int cantidad;
	int clas;
	int k;
	vector<distancias> dist;
	vector<int> cluster;
	vector<int> clusterout;
	
};

/*kmeans::kmeans(int puntos){
	cantidad=puntos;
	vector<int > cl(puntos);
	srand(time(NULL));
	for(unsigned i=0 ; i <puntos; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		ps1.push_back(punto);
	}
	cluster=cl;
}
*/
kmeans::kmeans(string p, int k){
	this->k = k;
	load(p);
}
/*
kmeans::kmeans(int puntos,int k){
	cantidad=puntos;
	vector<distancias> distmp(puntos);
	vector<int> clustmp(puntos);
	this->k=k;
	srand(time(NULL));
	for(unsigned i=0 ; i <puntos; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		ps1.push_back(punto);
	}
	for(unsigned i=0 ; i <k; ++i){
		auto x=(Num)(rand() % 101)/100;
		auto y=(Num)(rand() % 101)/100;
		auto punto = make_tuple(x,y);
		centros.push_back(punto);
	}
	dist=distmp;
	cluster=clustmp;
}*/

void kmeans::load(string puntos){
    ifstream f(puntos.c_str());
    
    f >> cantidad;
    f >> clas;
    dato xDat;
    dato xcent;
    Num x;
    for (unsigned i = 0; i < cantidad; ++ i){
    		xDat.clear();
    		for(unsigned j = 0; j < clas; ++ j){
    			f >> x;
    			xDat.push_back(x);
    			//cout<<xDat[j]<<"  ";
    		}
    		dats.push_back(xDat);
    		//cout<<endl;
    }

    vector<distancias> distmp(cantidad);
	vector<int> clustmp(cantidad);

	for(unsigned i=0 ; i <k; ++i){
		xcent.clear();
		for(unsigned j = 0; j < clas; ++ j){
    		x=(Num)(rand() % 101)/100;
    		xcent.push_back(x);
    	}
		centros.push_back(xcent);
	}
	dist=distmp;
	cluster=clustmp;
	f.close();
}

void kmeans::mostrar_cluster(){
	for(unsigned i=0; i<cantidad; ++i){
		cout<<clusterout[i]<<endl;
	}	
}

void kmeans::test(){
	vector<int> clus;
	clus.push_back(cluster[0]);

	for(unsigned i=0; i<cantidad; ++i){
		auto it=find(clus.begin(),clus.end(),cluster[i]);
		if(it!=clus.end()){
        	clusterout.push_back(it-clus.begin());
    	}
    	else{
        	clus.push_back(cluster[i]);
        	auto it1=find(clus.begin(),clus.end(),cluster[i]);
        	clusterout.push_back(it1-clus.begin());	
    	}
	}
}


void kmeans::test(string puntos){
    ifstream f(puntos.c_str());
    vector<vector<int>> confusion(k,vector<int> (k));
    dato points;
    Num x;
    for (unsigned i = 0; i < cantidad; ++ i){
    	f >> x;
    	points.push_back(x);
    }
    for(unsigned i = 0; i < cantidad; ++ i){
    	confusion[points[i]][clusterout[i]]+=1;
    }
    Num total1 = confusion[0][0]+confusion[0][1]+confusion[0][1];
    Num total2 = confusion[1][0]+confusion[1][1]+confusion[1][2];
    Num total3 = confusion[2][0]+confusion[2][1]+confusion[2][2];
    printf("             \t   SETOSA   \t VERSICOLOR\t VIRGINICA\n");
		printf("  SETOSA     \t     %1.0f     \t    %1.0f     \t    %1.0f     \n",(confusion[0][0]*100)/(total1),(confusion[0][1]*100)/(total1),(confusion[0][2]*100)/(total1));
		printf("  VERSICOLOR \t     %1.0f     \t    %1.0f     \t    %1.0f     \n",(confusion[1][0]*100)/(total2),(confusion[1][1]*100)/(total2),(confusion[1][2]*100)/(total2));
		printf("  VIRGINICA  \t     %1.0f     \t    %1.0f     \t    %1.0f     \n",(confusion[2][0]*100)/(total3),(confusion[2][1]*100)/(total3),(confusion[2][2]*100)/(total3));

}


void kmeans::save(){
	char* stri=(char*)"puntos1.dat";
	char* clus=(char*)"num1.dat";
	ofstream myfile1 (clus);//, std::ios_base::app
	myfile1 <<cantidad;
    myfile1.close();


	ofstream myfile (stri);//, std::ios_base::app
	for(unsigned i=0; i<cantidad; ++i){
		//myfile <<setprecision(20);
		for(unsigned j=0; j<clas; ++j){
			myfile << dats[i][j];
			myfile << "\t";
		}
		myfile << cluster[i];
		myfile << "\n";
	}
    myfile.close();
}

void kmeans::cambiar_centros(){
	vector<vector<Num>> sum(k,vector<Num> (clas)); 
	vector<Num> sumy(k);
	vector<Num> contador(k);
	for(unsigned i=0; i<cantidad; ++i){
		for(unsigned j=0; j<clas; ++j){
			sum[cluster[i]][j] += dats[i][j];
		}
		contador[cluster[i]]+=1;
	}
	for(unsigned i=0; i<k; ++i){
		for(unsigned j=0; j<clas; ++j){
			sum[i][j] = sum[i][j]/contador[i];
		}
		centros[i]=sum[i];

	}
}


void kmeans::run(){
	//cout<<"hola";
	distancias d;
	dist.clear();
	//cout<<"hola";
	for(unsigned j=0; j<k ; ++j){
		for(unsigned i=0; i<cantidad ; ++i){
			d.push_back(distancia(dats[i],centros[j]));
		}
		dist.push_back(d);
		d.clear();
	}
	clasificar();
}

void kmeans::clasificar(){
	Num menor;
	int pos;
	for(unsigned j=0; j<cantidad ; ++j){
		menor=DBL_MAX;
		for(unsigned i=0; i<k ; ++i){
			if(dist[i][j]<menor){
				menor=dist[i][j];
				pos=i;
			}
		}
		cluster[j]=pos;
	}
}


void kmeans::mostrar(){
	for(unsigned i=0; i<cantidad; ++i){
		for(unsigned j=0; j<clas; ++j){
			cout<<dats[i][j]<<"\t";
		}
		cout<<cluster[i]<<endl;
	}
}

void kmeans::mostrar_centros(){
	for(unsigned i=0; i<k; ++i){
		for(unsigned j=0; j<clas; ++j){
			cout<<centros[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void kmeans::mostrar_distancias(){
	for(unsigned j=0; j<cantidad; ++j){
		for(unsigned i=0; i<k; ++i){
			cout<<dist[i][j]<<"  ";
		}
		cout<<endl;
	}
}


Num distancia(dato a, dato b){
	Num dis=0;
	for(unsigned i=0;i<a.size();++i){
		dis+=pow(a[i]-b[i],2);
	}
	return sqrt(dis);
}
#endif
