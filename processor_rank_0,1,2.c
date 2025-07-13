//Write a parallel MPI program in C where three processes (ranks 0, 1, and 2) each print two values from an integer array ar[], and one process (rank 3) 
//prints three values from the same array.
// The array ar[] has a length of 9. Each process should print "I am processor X with index value Y, Z" (for ranks 0, 1, and 2). runs with exactly 4 processes.
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int ar[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90}; // Example values

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and total number of processes
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

    // Assign and print based on rank
    if (rank == 0) {
        printf("I am processor %d with index value %d, %d\n", rank, ar[0], ar[1]);
    } else if (rank == 1) {
        printf("I am processor %d with index value %d, %d\n", rank, ar[2], ar[3]);
    } else if (rank == 2) {
        printf("I am processor %d with index value %d, %d\n", rank, ar[4], ar[5]);
    } else if (rank == 3) {
        printf("I am processor %d with index value %d, %d, %d\n", rank, ar[6], ar[7], ar[8]);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
