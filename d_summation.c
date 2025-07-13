//write a MPI Program for distributed summation of the numbers from 1 to 100 using 4 processes. 
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
int rank, size;
int start, end, local_sum = 0, total_sum = 0;
int N = 100;
MPI_Init(&argc, &argv); // Initialize MPI
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process rank
MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
if (size != 4) {
if (rank == 0)
printf("Please run with exactly 4 processes.\n");
MPI_Finalize();
return 0;
}
// Divide work among processes
int chunk = N / size;
start = rank * chunk + 1;
end = (rank == size - 1) ? N : start + chunk - 1;
// Each process computes its partial sum
for (int i = start; i <= end; i++) {
local_sum += i;
}
// Reduce local sums to total sum at root process
MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
if (rank == 0) {
printf("The total sum from 1 to 100 is: %d\n", total_sum);
}
MPI_Finalize();
return 0;
}