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
const string testing_image_fn = "mnist/t10k-images.idx3-ubyte";

// Testing label file name
const string testing_label_fn = "mnist/t10k-labels.idx1-ubyte";

// Weights file name
const string model_fn = "model-neural-network.dat";

// Report file name
const string report_fn = "testing-report.dat";

// Number of training samples
const int nTesting = 100;//10000;


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
int* w=new int[n1*n1];
int d[width + 1][height + 1];
int* pattern=new int[nTesting*n1];
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


void load_model(string file_name) {
	ifstream file(file_name.c_str(), ios::in);
	
	// Input layer - Hidden layer
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n1; ++j) {
			file >> w[j*n1+i];
		}
    }
	
	file.close();
}

void input() {
	// Reading image
	for (int k = 0; k < nTesting; ++k)
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
	    for (int i = 0; i < n3; ++i) {
			expected[i] = 0.0;
		}
	    expected[number + 1] = 1.0;
	    
	  //  cout << "Label: " << (int)(number) << endl;
	}
    
}


// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]) {

 	//srand (time(NULL));
	about();
	
    report.open(report_fn.c_str(), ios::out);
    image.open(testing_image_fn.c_str(), ios::in | ios::binary); // Binary image file
    label.open(testing_label_fn.c_str(), ios::in | ios::binary ); // Binary label file
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
    load_model(model_fn); // Load model (weight matrices) of a trained Neural Network
  /* pattern[0]=1;
   pattern[1]=1;
   pattern[2]=1;
   pattern[3]=1;
   pattern[4]=1;
   */
  /* for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n1; ++j) {
			cout<<w[j*n1+i]<<" ";
		}
		cout<<endl;
    }cout<<endl;
*/
   for (int k = 0; k < nTesting; ++k)
   {
   		int* neuron=new int[n1];      // current state of the network
	    int* neuron_prev=new int[n1]; // prev state of the network
	    for(int i=0;i<n1;i++)
	    {
	        neuron[i]=pattern[10*n1+i];
	        //cout<<neuron[i];
	        neuron_prev[i]=neuron[i]; // initially prev state=current
	    }
	   // cout<<endl<<endl;
   
	    int ctr_unchg=0;

	    // loop counter to ensure a stop just in case
	    // if the network becomes cyclic or chaotic
	    int ctr=0;
	    
	    while(ctr_unchg<1000 && ctr<10000) // max 1000 loops allowed
	    {

	        // First choice for updating the network
	        for(int j=0;j<n1;j++) // update the whole network ?
	        {
	            // Serial-Random updating:
	            // Randomly select a neuron and update its value
	           // int j=rand()%n1;
	            double sum=0;
	            //cout<<j<<endl;
	            for(int i=0;i<n1;i++){
	                if(i!=j){
	                    sum+=neuron[i]*w[j*n1+i];
	                	//if(w[j*n1+i]!=0){

	                		//cout<<w[j*n1+i]<<" "<<neuron[i]<<" "<<sum<<"   ";
	                	//}
	                }
	            }

	            //cout<<endl;
	            //cout<<sum<<endl;
	            if(sum>0){
	            //	cout<<"positivo"<<endl;
	                neuron[j]=1;
	            }
	            else {
	                neuron[j]=0;
	            }
	           // else{
	            //	neuron[j]=-1;
	           // }
	          //  cout<<endl;

	      		//cout<<neuron[j];
	        }

	        bool changed=false;
	        for(int l=0;l<n1;l++)
	            if(neuron[l]!=neuron_prev[l])
	            {
	                changed=true;
	                break;
	            }
	        if(changed==false)
	            ctr_unchg++;
	        else
	            ctr_unchg=0;

	        // update the previous network state
	        for(int l=0;l<n1;l++)
	            neuron_prev[l]=neuron[l];

	        ctr++;              
	    }
   		
   		for(int j=0;j<height;j++)     // rows
	    {
	        for(int i=0;i<width;i++) // columns
	        {
	            cout<<pattern[k*n1+i+j*width];
	        }
	        cout<<"\t";
	        for(int i=0;i<width;i++) // columns
	        {
	            cout<<neuron[j*width+i];
	        }
	    	cout<<endl;
	    }
	    cout<<endl;
   	
   	}

    
    cout<<endl;
    report.close();
    image.close();
    label.close();
    
    return 0;
}

