#include <iostream>
#include <ctime> 
#include <stdlib.h>

#define MAX 1000


using namespace std;

typedef double matriz[MAX][MAX];


void generar_vector(double *a,int tam,double l, double u);
void mostrar_matriz(double *a,int ca,int fa,int lda);
void multiplicacion_clasica(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc);

int main(){
	srand (time(NULL));
	double *a,*b,*c,*d,l,u;
  	int fa,ca,lda,fb,cb,ldb,fc,cc,ldc,tb,fd,cd,ldd;
	unsigned t0, t1;
	//fila y columna de A
	ca=MAX;
	fa=MAX;
	lda=ca;
	fb=ca;
	//columna de B
	
	cb=MAX;
	ldb=cb;
	fc=fa;
	cc=cb;
	ldc=cc;

	fd=fa;
	cd=cb;
	ldd=cd;
	//tama;ano de bloque
	tb=6;
	//valor maximo y minino de datos
	l=0;
	u=10;
	
	a=(double *) malloc(sizeof(double)*fa*ca);
	b=(double *) malloc(sizeof(double)*fb*cb);
	c=(double *) malloc(sizeof(double)*fc*cc);
	d=(double *) malloc(sizeof(double)*fd*cd);

	generar_vector(a,fa*ca,l,u);
	generar_vector(b,fb*cb,l,u);
/*	mostrar_matriz(a,ca,fa,lda);
	mostrar_matriz(b,cb,fb,ldb);
	mostrar_matriz(c,cc,fc,ldc);
*/
		//cout<<"AQUI"<<endl;	
	
	t0=clock();
	multiplicacion_clasica(a,fa,ca,lda,b,fb,cb,ldb,c,fc,cc,ldc);
	t1 = clock();
//	mostrar_matriz(c,cc,fc,ldc);	
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	//cout << "Execution Time: " << time << endl;
	
///	mostrar_matriz(d,cd,fd,ldd);

	return 0;
}

void generar_vector(double *a,int tam,double l, double u){
	
	for (int i = 0; i < tam; ++i)
	{
		a[i]=rand()%((int)l-(int)u+1)+(int)u;
	}
}

void mostrar_matriz(double *a,int ca,int fa,int lda){
	cout<<endl;
	for (int i = 0; i < ca; ++i)
	{
		for (int j = 0; j < fa; ++j)
		{
			cout<<a[i*lda+j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

}

void multiplicacion_clasica(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc){
	int i,j,k;
	double s;
	for(i=0;i<fa;i++){
		for(j=0;j<cb;j++){
			s=0.;
			for(k=0;k<ca;k++){
				s+=a[i*lda+k]*b[k*ldb+j];
			}
			c[i*ldc+j]=s;
		}		
	}
}
