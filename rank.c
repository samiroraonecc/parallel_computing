// Write a parallel MPI program in C where three processes (ranks 0, 1, and 2) each print two 
//values from an integer array ar[], and one process (rank 3) prints three values from the
// same array. The array ar[] has a length of 9. Each process should print "I am processor X with
// index value Y, Z" (for ranks 0, 1, and 2). runs with exactly 4 processes.
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    int ar[] = {05, 18, 28, 30, 14, 0, 8, 9, 69};
    
    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes
    MPI_Get_processor_name(processor_name, &name_len); // Get the processor name
    
    int i = rank;
    if (i < 3) {
        printf("I am processor %d with index value %d , %d \n", rank, ar[rank+i], ar[rank+i+1]);
    } else {
        printf("I am processor %d with index value %d , %d ,%d \n", rank, ar[rank+i], ar[rank+i+1], ar[rank+i+2]);
    }
    
    MPI_Finalize(); // Finalize MPI environment
    return 0;
}
//