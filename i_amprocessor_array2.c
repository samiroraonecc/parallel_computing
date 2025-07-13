//Write a parallel MPI program in C where each process prints its rank along with the corresponding values 
//from integer arrays arr[] (where ar[] has a length of 8). Each process should print "I am processor X with array value Y, Z",
//here X is the rank of the process, Y is the value from the array ar[] corresponding to its rank, and Z is the value from the array ar[] corresponding to its rank plus 4. 
//Ensure that the program initializes and finalizes the MPI environment correctly. runs with exactly 4 processes.
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int arr[8] = {10, 20, 30, 40, 50, 60, 70, 80}; // Example values

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ensure the program runs with exactly 4 processes
    if (size != 4) {
        if (rank == 0) {
            printf("This program must be run with exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    // Each process prints its corresponding values from the array
    printf("I am processor %d with array value %d, %d\n",
           rank, arr[rank], arr[rank + 4]);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
