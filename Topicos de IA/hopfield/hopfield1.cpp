// Software: Training Artificial Neural Network for MNIST database
// Author: Hy Truong Son
// Major: BSc. Computer Science
// Class: 2013 - 2016
// Institution: Eotvos Lorand University
// Email: sonpascal93@gmail.com
// Website: http://people.inf.elte.hu/hytruongson/
// Copyright 2015 (c). All rights reserved.

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

// Training image file name
const string training_image_fn = "mnist/train-images.idx3-ubyte";

// Training label file name
const string training_label_fn = "mnist/train-labels.idx1-ubyte";

// Weights file name
const string model_fn = "model-neural-network.dat";

// Report file name
const string report_fn = "training-report.dat";

// Number of training samples



// Image size in MNIST database
const int width = 28;//28;
const int height =28; //28;

// n1 = Number of input neurons
// n2 = Number of hidden neurons
// n3 = Number of output neurons
// epochs = Number of iterations for back-propagation algorithm
// learning_rate = Learing rate
// momentum = Momentum (heuristics to optimize back-propagation algorithm)
// epsilon = Epsilon, no more iterations if the learning error is smaller than epsilon

const int n1 = width * height; // = 784, without bias neuron 
const int nTraining = 10000;//0.138*n1;//60000;

int* w=new int[n1*n1];
int d[width + 1][height + 1];
int* pattern=new int[nTraining*n1];
const int n3 = 10;
double expected[n3 + 1];



// From layer 2 to layer 3. Or; Hidden layer - Output layer
// File stream to read data (image, label) and write down a report
ifstream image;
ifstream label;
ofstream report;

// +--------------------+
// | About the software |
// +--------------------+

void about() {
	// Details
	cout << "**************************************************" << endl;
	cout << "*** Hopfield Artificial Neural Network (ANN)   ***" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
	
}

// +-----------------------------------+
// | Memory allocation for the network |
// +-----------------------------------+

// +--------------------------------------------------------------+
// | Reading input - gray scale image and the corresponding label |
// +--------------------------------------------------------------+

void input() {
	// Reading image
	for (int k = 0; k < nTraining; ++k)
	{
		char number;
	    	for (int j = 0; j < height; ++j) {
		        for (int i = 0; i < width; ++i) {
		            image.read(&number, sizeof(char));
		            if (number == 0) {
						d[i][j] = 0; 
					} else {
						d[i][j] = 1;
					}
		        }
			}	
		
		//cout << "Image:" << endl;
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
		//		cout << d[i][j];
				pattern[k*n1+i+j*width] = d[i][j];
			}
		//	cout << endl;
		}

		// Reading label
	    label.read(&number, sizeof(char));
	    for (int i = 0; i <= n3; ++i) {
			expected[i] = 0.0;
		}
	    expected[number + 1] = 1.0;
	    
	    //cout << "Label: " << (int)(number) << endl;
	}
    
}


void write_matrix(string file_name) {
    ofstream file(file_name.c_str(), ios::out);
	
	// Input layer - Hidden layer
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n1; ++j) {
			file << w[j*n1+i] << " ";
		}
		file << endl;
    }
	
	file.close();
}

// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]) {

 srand (time(NULL));
	about();
	
    report.open(report_fn.c_str(), ios::out);
    image.open(training_image_fn.c_str(), ios::in | ios::binary); // Binary image file
    label.open(training_label_fn.c_str(), ios::in | ios::binary ); // Binary label file
	// Reading file headers
    char number;
    for (int i = 0; i < 16; ++i) {
        image.read(&number, sizeof(char));
	}
    for (int i = 0; i < 8; ++i) {
        label.read(&number, sizeof(char));
	}
   // init_array();
   input();	
 /*  pattern[0]=0;
   pattern[1]=1;
   pattern[2]=1;
   pattern[3]=0;
   pattern[4]=1;
   pattern[5]=1;
   pattern[6]=0;
   pattern[7]=1;
   pattern[8]=0;
   pattern[9]=1;
*/
    
    /*for (int k = 0; k < nTraining; ++k)
    {
    	for(int j=0;j<height;j++)     // rows
	    {
	        for(int i=0;i<width;i++) // columns
	        {
	            cout<<pattern[k*n1+i+j*width];
	        }
	    	cout<<endl;
	    }
	    cout<<endl;
    }cout<<endl;
	  */  
	// ANN initialization
    //w=new int[n1*n1];	
    int i,j,k,l;
    int sum;
    for(j=0;j<n1;j++)
        for(i=j;i<n1;i++)
            if(i==j)
                w[j*n1+i]=0;
            else
            {
                sum=0;
                for(k=0;k<nTraining;k++){
                    sum+=(pattern[k*n1+i]*2-1)*(pattern[k*n1+j]*2-1);//(pattern[k*n1+i]*2-1)*(pattern[k*n1+j]*2-1);//(pattern[k*n1+i])*(pattern[k*n1+j]);
                }
                w[j*n1+i]=sum;
                w[i*n1+j]=sum;
            }
    // print the weight matrix
    cout<<"The weight matrix:"<<endl<<endl;
    write_matrix(model_fn);
    report.close();
    image.close();
    label.close();
    
    return 0;
}
