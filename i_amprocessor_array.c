//11 Write a parallel MPI program in C where each process prints its rank along with the
 //corresponding value from an integer array arr[4]. Each process should print "I am processor 
 //X with array value Y", where X is the rank of the process and Y is the value from the array ar[]
  //corresponding to its rank. 
//nsure that the program initializes and finalizes the MPI environment correctly. 
//runs with exactly 4 processes.
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) { int rank, size; char processor_name[MPI_MAX_PROCESSOR_NAME]; int name_len; int ar[]={05,18,28,30};
MPI_Init(&argc, &argv); // Initialize MPI environment
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes
MPI_Get_processor_name(processor_name, &name_len); // Get the processor name
printf("I am processor %d with array value %d \n",rank ,ar[rank]);
MPI_Finalize(); // Finalize MPI environment return 0;
}