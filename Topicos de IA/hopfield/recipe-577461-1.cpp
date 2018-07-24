
#include <iostream>
#include <curses.h> // getch()
using namespace std;

int main (int argc, char *argv[])
{ 
    cout<<"Hopfield Artificial Neural Network (ANN):"<<endl<<endl;
    srand(time(NULL)); // use current time to seed random number generator
    int n=28*28;          // size of each pattern = number of neurons
    int i,j,k,sum;
    
    // Create a random pattern matrix to learn.
    // Each row is a separate pattern to learn (n bits each).
    cout<<"Training patterns:"<<endl<<endl;
    // max capacity (number of patterns it can learn) of Hopfield network
    // is 0.138N (N: number of neurons)
    int m=1000; // number of patterns (rows)
    int* pattern=new int[m*n];
    for(j=0;j<m;j++)     // rows
    {
        for(i=0;i<n;i++) // columns
        {
            pattern[j*n+i]=rand()%2;
            cout<<pattern[j*n+i];
        }
        cout<<endl;
    }
    cout<<endl;
    
    // calculate the weight matrix (symmetric and square)
    // w[i,j]=w[j,i] & i!=j (i==j => w=0)
    int* w=new int[n*n];
    for(j=0;j<n;j++)
        for(i=j;i<n;i++)
            if(i==j)
                w[j*n+i]=0;
            else
            {
                sum=0;
                for(k=0;k<m;k++)
                    sum+=(pattern[k*n+i]*2-1)*(pattern[k*n+j]*2-1);
                w[j*n+i]=sum;
                w[i*n+j]=sum;
            }

    // print the weight matrix
    cout<<"The weight matrix:"<<endl<<endl;
    for(j=0;j<n;j++)
    {
        for(i=0;i<n;i++)
            printf("%2d ",w[j*n+i]);
        cout<<endl;
    }
    cout<<endl;

    cout<<"Pattern-recognition Test:"<<endl<<endl;
    // Select one of the training patterns randomly
    int selectedPattern=rand()%m;
    cout<<"Test pattern selected:"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<pattern[selectedPattern*n+i];
    }
    cout<<endl<<endl;
    
    int errorPercentage=10;
    cout<<"Initial network state:"<<endl;
    cout<<"The test pattern w/ "<<errorPercentage<<"% error added:"<<endl;
    int* neuron=new int[n];      // current state of the network
    int* neuron_prev=new int[n]; // prev state of the network
    for(i=0;i<n;i++)
    {
        neuron[i]=pattern[selectedPattern*n+i];
        if(rand()%100<errorPercentage) neuron[i]=1-neuron[i];
        cout<<neuron[i];
        neuron_prev[i]=neuron[i]; // initially prev state=current
    }
    cout<<endl<<endl;

    // if state of the network stays unchanged for ? steps
    // that means the network is converged to an answer
    // so then exit the loop and printout the last state
    int ctr_unchg=0;

    // loop counter to ensure a stop just in case
    // if the network becomes cyclic or chaotic
    int ctr=0;
    
    while(ctr_unchg<100 && ctr<20000) // max 1000 loops allowed
    {

        // First choice for updating the network
        for(k=0;k<n;k++) // update the whole network ?
        {
            // Serial-Random updating:
            // Randomly select a neuron and update its value
            j=rand()%n;
            sum=0;
            for(i=0;i<n;i++)
                if(i!=j)
                    sum+=neuron[i]*w[j*n+i];
            if(sum>=0)
                neuron[j]=1;
            else
                neuron[j]=0;
        }

        bool changed=false;
        for(k=0;k<n;k++)
            if(neuron[k]!=neuron_prev[k])
            {
                changed=true;
                break;
            }
        if(changed==false)
            ctr_unchg++;
        else
            ctr_unchg=0;

        // update the previous network state
        for(k=0;k<n;k++)
            neuron_prev[k]=neuron[k];

        ctr++;              
    }

    // note: Hopfield net also learns inverse of each bit pattern
    // so it can also end up with one of the inverse patterns!

    // if the network is converged then
    // printout the last state of the network
    if(ctr_unchg>=100)
    {
        cout<<"Converged network state:"<<endl<<endl;
        for(i=0;i<n;i++)
            cout<<neuron[i];
        cout<<endl<<endl;

        // calculate the convergence error percentage
        float sumDif=0; // total number of differences
        for(i=0;i<n;i++)
            if(neuron[i]!=pattern[selectedPattern*n+i])
                sumDif++;
        cout<<"Convergence error percentage:"<<100.0*sumDif/(float
)n<<endl;
    }
    else
        cout<<"The network did not reach the convergence limit set!"<<endl;
    
    // garbage collection
    delete []pattern;
    delete []w;
    delete []neuron;
    delete []neuron_prev;

    //getch(); // wait until any key is pressed
    return 0;
}
