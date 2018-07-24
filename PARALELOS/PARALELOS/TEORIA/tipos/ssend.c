#include "mpi.h"   /* PROVIDES THE BASIC MPI DEFINITION AND TYPES */
#include <stdio.h>

int main(int argc, char **argv) {
 
  MPI_Status stat;
  int count=0;
  int my_rank; 
  int size;
  int partner;
  MPI_Init(&argc, &argv); /*START MPI */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /*DETERMINE RANK OF THIS PROCESSOR*/
  MPI_Comm_size(MPI_COMM_WORLD, &size); /*DETERMINE TOTAL NUMBER OF PROCESSORS*/
  for(int i=0;i<10;i++){
  if (my_rank ==0) {
    
    MPI_Ssend(&count,1, MPI_BYTE,1,1,MPI_COMM_WORLD);
    
    MPI_Recv(&count,1, MPI_BYTE,1, 1, MPI_COMM_WORLD, &stat);     
    count++;
    printf("Hello world! I'm rank (processor number) %d count %d\n", my_rank, count);
    
    
  }
  else {
    MPI_Recv(&count,1, MPI_BYTE,0, 1, MPI_COMM_WORLD, &stat);
    count++;
    printf("Hello world! I'm rank (processor number) %d count %d\n", my_rank, count);  
    
    MPI_Ssend(&count,1, MPI_BYTE,0,1,MPI_COMM_WORLD);
    
  }
  }	
  MPI_Finalize();  /* EXIT MPI */
}

