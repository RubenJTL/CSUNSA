#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

void mostrar_matrix(vector<vector<int>> v);
void mostrar_vector(std::vector<int> v);

int main()
{
	//vector<vector<int>> V={{0,1,1,0,1},{1,0,1,0,1}};
	//vector<vector<int>> V={{0,0,1,0},{1,1,1,-1}};
	vector<vector<int>> V={{1, -1, 1, -1, 1, 1},{1, 1, 1, -1, -1, -1}};
	std::vector<int> deseado={1,1,1,0};
	vector<vector<int>> W;
	std::vector<int> y;
	for (int j = 0; j < V[0].size(); ++j)
	{
		y.push_back(0);
	}
	for (int i = 0; i < V[0].size(); ++i)
	{
		W.push_back(y);
	}
	for (int i = 0; i < W.size(); ++i)
	{
		for (int j = 0; j < W[i].size(); ++j)
		{
			int sum=0;
			for (int k = 0; k < V.size(); ++k)
			{
				sum+=V[k][i]*V[k][j];//(2V[k][i]-1)*(2V[k][j]-1);
			}
			W[i][j]=sum;
			W[i][i]=0;
		}
	}
	mostrar_matrix(W);
	for (int i = 0; i < y.size(); ++i)
	{
		int sum=0;
		for (int j = 0; j < W[i].size(); ++j)
		{
			sum+=W[i][j]*V[0][j];
		}
		y[i]=sum;
	}
	for (int i = 0; i < y.size(); ++i)
	{
		int sum=0;
		for (int j = 0; j < W.size(); ++j)
		{
			sum+=y[j]*W[j][i];
		}
		if (V[0][i]+sum>=0)
		{
			y[i]=1;
		}else{
			y[i]=0;
		}
		
	}
	mostrar_vector(y);

}

void mostrar_vector(std::vector<int> v){
	for (int j = 0; j < v.size(); ++j)
		{
			cout<<v[j]<<"\t";
		}
		cout<<endl;
}
void mostrar_matrix(vector<vector<int>> v){
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			cout<<v[i][j]<<"\t";
		}
		cout<<endl;
	}
}
