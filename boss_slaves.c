//Write an MPI program that prints the name of the processor and the rank of each process. 
//The program should identify process 0 as the "boss" and all other processes as "slaves".
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
int rank, size, name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];
MPI_Init(&argc, &argv); // Initialize MPI
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get rank of process
MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
MPI_Get_processor_name(processor_name, &name_len); // Get processor name
if (rank == 0) {
printf("Boss: Process %d is running on %s\n", rank, processor_name);
} else {
printf("Slave: Process %d is running on %s\n", rank, processor_name);
}
MPI_Finalize(); // Finalize MPI
return 0;
}
