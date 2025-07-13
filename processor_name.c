#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) { int rank, size; char processor_name[MPI_MAX_PROCESSOR_NAME]; int name_len;
MPI_Init(&argc, &argv); // Initialize MPI environment
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes
MPI_Get_processor_name(processor_name, &name_len); // Get the processor name
printf("Processor name: %s, Rank: %d, Size: %d\n", processor_name, rank, size);
MPI_Finalize(); // Finalize MPI environment return 0;
}