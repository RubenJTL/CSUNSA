#include <iostream>
#include <ctime> 
#include <stdlib.h>

#define MAX 1000


using namespace std;

typedef double matriz[MAX][MAX];



void mostrar_matriz(double *a,int ca,int fa,int lda);
void generar_vector(double *a,int tam,double l, double u);
void multiplicacion_clasica(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc);
void matriz_cero(double *m,int fm,int cm,int ldm);
void copiar_matriz(double *mo,int fmo,int cmo,int ldmo,double *md,int fmd,int cmd,int ldmd);
void multiplicar_acumular_matrices(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc);
void matriz_matriz_bloques(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc,int tb);

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
	//c=(double *) malloc(sizeof(double)*fc*cc);
	d=(double *) malloc(sizeof(double)*fd*cd);

	generar_vector(a,fa*ca,l,u);
	generar_vector(b,fb*cb,l,u);
/*	mostrar_matriz(a,ca,fa,lda);
	mostrar_matriz(b,cb,fb,ldb);
	mostrar_matriz(c,cc,fc,ldc);
*/
		//cout<<"AQUI"<<endl;	
	
	t0=clock();
 	 matriz_matriz_bloques(a,fa,ca,lda,b,fb,cb,ldb,d,fd,cd,ldd,tb);

	t1 = clock();
//	mostrar_matriz(d,cd,fd,ldd);	
//	mostrar_matriz(c,cc,fc,ldc);	
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	//cout << "Execution Time: " << time << endl;


	return 0;
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
void generar_vector(double *a,int tam,double l, double u){
	
	for (int i = 0; i < tam; ++i)
	{
		a[i]=rand()%((int)l-(int)u+1)+(int)u;
	}
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

void matriz_cero(double *m,int fm,int cm,int ldm)
{
  int i,j;
  double *dm;

  for(i=0;i<fm;i++)
  {
    dm=&m[i*ldm];
    for(j=0;j<cm;j++)
    {
      dm[j]=0.;
    }
  }
}

void copiar_matriz(double *mo,int fmo,int cmo,int ldmo,double *md,int fmd,int cmd,int ldmd)
{
  int i,j;
  double *dmo,*dmd;

  for(i=0;i<fmo;i++)
  {
    dmo=&mo[i*ldmo];
    dmd=&md[i*ldmd];
    for(j=0;j<cmo;j++)
    {
      dmd[j]=dmo[j];
    }
  }
}

void multiplicar_acumular_matrices(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc)
{
  int i,j,k,kb;
  double *da,*db,s;

  for(i=0;i<fa;i++)
  {
    da=&a[i*lda];
    for(j=0;j<cb;j++)
    {
      db=&b[j];
      s=c[i*ldc+j];
    //  cout<<endl<<"ESTO1 "<<s<<endl;
      for(k=0,kb=0;k<ca;k++,kb=kb+ldb)
      {
        s=s+da[k]*db[kb];
      }
     // cout<<endl<<"ESTO "<<s<<endl;
      c[i*ldc+j]=s;
    }
  }
}

void matriz_matriz_bloques(double *a,int fa,int ca,int lda,double *b,int fb,int cb,int ldb,double *c,int fc,int cc,int ldc,int tb)
{
  int i,j,k;
  double *s;

  s=(double *) malloc(sizeof(double)*tb*tb);

  for(i=0;i<fa;i=i+tb)
  {
    for(j=0;j<cb;j=j+tb)
    {
      matriz_cero(s,tb,tb,tb);
      for(k=0;k<ca;k=k+tb)
      {
        multiplicar_acumular_matrices(&a[i*lda+k],tb,tb,lda,&b[k*ldb+j],tb,tb,ldb,s,tb,tb,tb);
      }
      copiar_matriz(s,tb,tb,tb,&c[i*ldc+j],tb,tb,ldc);
    }
  }
}
