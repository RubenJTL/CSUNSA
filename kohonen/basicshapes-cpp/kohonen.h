#ifndef KOHONEN_H
#define KOHONEN_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

#define RANDOM_RANGE 20

using namespace std;

typedef double Val;

typedef struct{
    int dim[3];
}Winner;

class NeuroMap{
    public:
        NeuroMap(int dimension, int numInputs, Val radioInicial, Val LearningInicial, int numIterations,
            string file, string test);
        Winner getWin(Val * intput);
        Val getDistance(Val * a, Val * b);
        Val getDistance(Winner a, Winner b);
        void print();
        void printWin(Winner win);
        void printTraining();
        void changePesos(Winner win, Val * in);
        void run();
        Winner test();
        Val * splitLine(string line);
        vector<Val *> getTraining(string file);
        Val getNewRadius();
        Val getNewLearning();
        Val getTheta(Winner win, Winner actual, Val radio);

        int NMsize;
        int Isize;
        int numIterations;
        int iteracionActual;
        Val LearningInicial;
        Val radioInicial;
        Val lambda;
        Val **** cube;
        vector<Val *> training;
        vector<Val *> tests;
};



NeuroMap::NeuroMap(int dimension, int numInputs, Val radioInicial, Val LearningInicial, int numIterations,
                 string file, string test){
    srand(time(NULL));
    NMsize = dimension;
    Isize = numInputs;
    this->radioInicial = radioInicial;
    this->numIterations = numIterations;
    this->LearningInicial = LearningInicial;
    this->training = training;
    lambda = numIterations / radioInicial;
    iteracionActual = 0;
    training = getTraining(file);
    tests = getTraining(test);
    cube = (Val ****) malloc(sizeof(void ***) * dimension);
    for(int i = 0; i < NMsize; i++){
        cube[i] = (Val ***) malloc(sizeof(void **) * dimension);
        for(int j = 0; j < NMsize; j++){
            cube[i][j] = (Val **) malloc(sizeof(void *) * dimension);
            for(int k = 0; k < NMsize; k++){
                cube[i][j][k] = (Val *) malloc(sizeof(Val) * Isize);
            }
        }
    }
    for(int i = 0; i < NMsize; i++){
        for(int j = 0; j < NMsize; j++){
            for(int k = 0; k < NMsize; k++){
                for(int w = 0; w < Isize; w++){
                    cube[i][j][k][w] = rand() % RANDOM_RANGE;
                }
            }
        }
    }
}

vector<Val *> NeuroMap::getTraining(string file){
    vector<Val *> Vres;
    ifstream archivo(file.c_str());
    string temp = "";
    while(archivo>>temp){
        Val * res = (Val *) malloc(sizeof(Val) * Isize);
        res[0] = stod(temp);
        for(int i = 1; i < Isize; i++){
            archivo>>temp;
            res[i] =stod(temp);
        }
        Vres.push_back(res);
    }
    archivo.close();
    return Vres;
}

void NeuroMap::print(){
    for(int i = 0; i < NMsize; i++){
        for(int j = 0; j < NMsize; j++){
            for(int k = 0; k < NMsize; k++){
                for(int w = 0; w < Isize; w++){
                    cout<<cube[i][j][k][w]<<" ";
                }
                cout<<"  ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<endl;
}

void NeuroMap::printWin(Winner win){
    cout<<"Dim1->"<<win.dim[0]<<endl;
    cout<<"Dim2->"<<win.dim[1]<<endl;
    cout<<"Dim3->"<<win.dim[2]<<endl;
    for(int i = 0; i < Isize; i++){
        cout<<cube[win.dim[0]][win.dim[1]][win.dim[2]][i]<<" ";
    }
    cout<<endl;
}

void NeuroMap::printTraining(){
    for(Val * v : training){
        for(int i = 0; i < Isize; i++){
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

Val NeuroMap::getDistance(Val * a, Val * b){
    Val res = 0;
    for(int i = 0; i < Isize; i++) res += pow(a[i] - b[i],2);
    return sqrt(res);
}

Val NeuroMap::getDistance(Winner a, Winner b){
    Val res = 0;
    for(int i = 0; i < 3; i++) res += pow(a.dim[i] - b.dim[i],2);
    return sqrt(res);
}

Winner NeuroMap::getWin(Val * inputs){
    Winner res;
    res.dim[0] = -1;
    res.dim[1] = -1;
    res.dim[2] = -1;
    Val menor = -1;
    Val temp = 0;
    for(int i = 0; i < NMsize; i++){
        for(int j = 0; j < NMsize; j++){
            for(int k = 0; k < NMsize; k++){
                temp = getDistance(inputs, cube[i][j][k]);
                if(menor > temp or menor == -1){
                    menor = temp;
                    res.dim[0] = i;
                    res.dim[1] = j;
                    res.dim[2] = k;
                }
            }
        }
    }
    return res;
}


Val NeuroMap::getNewRadius(){
    return radioInicial * exp(-iteracionActual / lambda);
}

Val NeuroMap::getNewLearning(){
    return LearningInicial * exp(-iteracionActual / lambda);
}

Val NeuroMap::getTheta(Winner win, Winner actual, Val radio){
    Val distancia = getDistance(win, actual);
    return exp(-(distancia*distancia) / (2.0 * radio * radio));
}


void NeuroMap::changePesos(Winner win, Val * in){
    iteracionActual++;
    Val radio = getNewRadius();
    Val Learning = getNewLearning();
    Val thetha = 0;
    Winner actual;
    for(int i = 0; i < NMsize; i++){
        for(int j = 0; j < NMsize; j++){
            for(int k = 0; k < NMsize; k++){
                actual.dim[0] = i;
                actual.dim[1] = j;
                actual.dim[2] = k;
                thetha = getTheta(win, actual, radio);
                for(int w = 0; w < Isize; w++){
                    cube[i][j][k][w] += thetha * Learning * (in[w] - cube[i][j][k][w]);
                }
            }
        }
    }
}


void NeuroMap::run(){
    srand(time(NULL));
    Winner win;
    Val * randIn;
    int random = 0;
    for(int i = 0; i < numIterations; i++){
        random = rand() % training.size();
        randIn = training[random];
        win = getWin(randIn);
        changePesos(win, randIn);
    }
}

Winner  NeuroMap::test(){
    srand(time(NULL));
    Val * randIn;
    int random = rand() % tests.size();
    randIn = tests[random];
    return getWin(randIn);
}

#endif
