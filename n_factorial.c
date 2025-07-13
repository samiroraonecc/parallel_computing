#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
    int rank, size, n = 5; // Calculate 5!
    long long local_product = 1, global_product = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Broadcast n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process multiplies its assigned range
    for (int i = rank + 1; i <= n; i += size) {
        local_product *= i;
    }

    // Reduce using multiplication across all processes
    MPI_Reduce(&local_product, &global_product, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Factorial of %d is %lld\n", n, global_product); // Should print 120
    }

    MPI_Finalize();
    return 0;
}
