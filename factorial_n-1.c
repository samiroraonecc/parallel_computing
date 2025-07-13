//fac(1)-fac(2)+fac(3)-fac(4)+....+fac(n)
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to calculate factorial
long long factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[]) {
    int rank, size, n;
    long long local_sum = 0, global_sum = 0;
    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get input from command line or set default
    if (argc > 1) {
        n = atoi(argv[1]);
    } else {
        n = 10; // default value
    }
    
    if (rank == 0) {
        printf("Computing alternating factorial sum for n = %d\n", n);
        printf("Using %d processes\n", size);
        printf("Formula: fac(1) - fac(2) + fac(3) - fac(4) + ... + fac(%d)\n\n", n);
    }
    
    // Each process handles a subset of terms
    // Process i handles terms: i+1, i+1+size, i+1+2*size, etc.
    for (int i = rank + 1; i <= n; i += size) {
        long long fac_i = factorial(i);
        
        // Apply alternating sign: positive for odd indices, negative for even
        if (i % 2 == 1) {
            local_sum += fac_i;
        } else {
            local_sum -= fac_i;
        }
        
        // Debug output to show work distribution
        printf("Process %d: fac(%d) = %lld, sign = %s\n", 
               rank, i, fac_i, (i % 2 == 1) ? "+" : "-");
    }
    
    // Reduce all local sums to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Master process prints the result
    if (rank == 0) {
        printf("\nFinal Result: %lld\n", global_sum);
        
        // Verification with sequential calculation (for small n)
        if (n <= 12) {
            long long verify_sum = 0;
            printf("\nVerification (sequential):\n");
            for (int i = 1; i <= n; i++) {
                long long fac_i = factorial(i);
                if (i % 2 == 1) {
                    verify_sum += fac_i;
                    printf("+ fac(%d) = %lld\n", i, fac_i);
                } else {
                    verify_sum -= fac_i;
                    printf("- fac(%d) = %lld\n", i, fac_i);
                }
            }
            printf("Sequential result: %lld\n", verify_sum);
            printf("Match: %s\n", (verify_sum == global_sum) ? "YES" : "NO");
        }
    }
    
    MPI_Finalize();
    return 0;
}
