#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

typedef int Num;
typedef vector<Num> lista;
typedef vector<lista> matrix;

void print(matrix);
void print(lista);
lista dijkstra(matrix,Num);
Num minDistance(lista, bool sptSet[]);


int main(){
	matrix grafo=	{ {0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };

    print(grafo);
    cout<<endl;
    Num vertice=0;
    cout<<"Para el vertice "<<vertice<<" los caminos mas cortos son: "<<endl;
    print(dijkstra(grafo,vertice));
}

Num minDistance(lista dist, bool sptSet[])
{
   Num min = INT_MAX, min_index;
    for (int v = 0; v < dist.size(); v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}

lista dijkstra(matrix graph,Num src){
	lista dist(graph.size());
	bool sptSet[graph.size()];
	for (int i = 0; i < graph.size(); i++)
       dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;
	for (int count = 0; count < graph.size()-1; count++)
    {
    	int u = minDistance(dist, sptSet);
  		sptSet[u] = true;
  		
  		for (int v = 0; v < graph.size(); v++)
  			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            	dist[v] = dist[u] + graph[u][v];
    }
    return dist;
}

void print(matrix m){
	for(unsigned i=0; i < m.size(); i++){
		print(m[i]);
	}
	cout<<endl;
}

void print(lista L){
	for(unsigned i=0; i < L.size(); i++){
		cout<<L[i]<<"\t";
	}
	cout<<endl;
}