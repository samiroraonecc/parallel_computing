//Write a parallel MPI program in C that prints out the processor name, rank, and size of each process in the MPI_COMM_WORLD communicator. 
//Ensure that the program initializes and finalizes the MPI environment correctly and runs with exactly 4 processes.
 
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    
    // Initialize MPI environment
    MPI_Init(&argc, &argv);
// Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get the processor name
    MPI_Get_processor_name(processor_name, &name_len);
    
    // Check if running with exactly 4 processes
    if (size != 4) {
        if (rank == 0) {
            printf("Error: This program must run with exactly 4 processes.\n");
            printf("Current number of processes: %d\n", size);
            printf("Please run with: mpirun -np 4 ./program_name\n");
        }
        MPI_Finalize();
        return 1;
    }
    
    // Print processor information
    printf("Hello from processor %s, rank %d out of %d processes\n", 
           processor_name, rank, size);
    
    // Optional: Add a barrier to synchronize output
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Master process can print additional summary
    if (rank == 0) {
        printf("\nProgram completed successfully with %d processes.\n", size);
    }
    
    // Finalize MPI environment
    MPI_Finalize();
    
    return 0;
}


