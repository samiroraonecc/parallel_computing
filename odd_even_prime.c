#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h> 
int is_prime(int n) { 
if (n < 2) return 0; 
for (int i = 2; i * i <= n; i++) { 
if (n % i == 0) return 0; 
} 
return 1; 
} 
int main(int argc, char *argv[]) { 
int rank, size, i; 
const int N = 100; 
int data[N]; 
int chunk; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
chunk = N / size; 
int *sub_data = (int *)malloc(chunk * sizeof(int)); 
if (rank == 0) { 
for (i = 0; i < N; i++) { 
data[i] = i + 1; 
} 
} 
MPI_Scatter(data, chunk, MPI_INT, sub_data, chunk, MPI_INT, 0, MPI_COMM_WORLD); 
int local_prime_sum = 0, local_even_sum = 0, local_odd_sum = 0; 
int local_prime_max = -1, local_even_max = -1, local_odd_max = -1; 
int local_prime_min = 1<<30, local_even_min = 1<<30, local_odd_min = 1<<30; 
for (i = 0; i < chunk; i++) { 
int val = sub_data[i]; 
// Prime numbers 
if (is_prime(val)) { 
local_prime_sum += val; 
if (val > local_prime_max) local_prime_max = val; 
if (val < local_prime_min) local_prime_min = val; 
} 
// Even numbers 
if (val % 2 == 0) { 
local_even_sum += val; 
if (val > local_even_max) local_even_max = val; 
if (val < local_even_min) local_even_min = val; 
} 
// Odd numbers 
if (val % 2 != 0) { 
local_odd_sum += val; 
if (val > local_odd_max) local_odd_max = val; 
if (val < local_odd_min) local_odd_min = val; 
} 
} 
// Allocate arrays to gather local results at root 
int *prime_sums = NULL, *prime_maxs = NULL, *prime_mins = NULL; 
int *even_sums = NULL, *even_maxs = NULL, *even_mins = NULL; 
int *odd_sums = NULL, *odd_maxs = NULL, *odd_mins = NULL; 
if (rank == 0) { 
prime_sums = (int *)malloc(size * sizeof(int)); 
prime_maxs = (int *)malloc(size * sizeof(int)); 
prime_mins = (int *)malloc(size * sizeof(int)); 
even_sums = (int *)malloc(size * sizeof(int)); 
even_maxs = (int *)malloc(size * sizeof(int)); 
even_mins = (int *)malloc(size * sizeof(int)); 
odd_sums = (int *)malloc(size * sizeof(int)); 
odd_maxs = (int *)malloc(size * sizeof(int)); 
odd_mins = (int *)malloc(size * sizeof(int)); 
} 
// Gather sums 
MPI_Gather(&local_prime_sum, 1, MPI_INT, prime_sums, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_even_sum, 1, MPI_INT, even_sums, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_odd_sum, 1, MPI_INT, odd_sums, 1, MPI_INT, 0, MPI_COMM_WORLD); 
// Gather max 
MPI_Gather(&local_prime_max, 1, MPI_INT, prime_maxs, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_even_max, 1, MPI_INT, even_maxs, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_odd_max, 1, MPI_INT, odd_maxs, 1, MPI_INT, 0, MPI_COMM_WORLD); 
// Gather min 
MPI_Gather(&local_prime_min, 1, MPI_INT, prime_mins, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_even_min, 1, MPI_INT, even_mins, 1, MPI_INT, 0, MPI_COMM_WORLD); 
MPI_Gather(&local_odd_min, 1, MPI_INT, odd_mins, 1, MPI_INT, 0, MPI_COMM_WORLD); 
if (rank == 0) { 
// Combine sums 
int total_prime_sum = 0, total_even_sum = 0, total_odd_sum = 0; 
int total_prime_max = -1, total_even_max = -1, total_odd_max = -1; 
int total_prime_min = 1<<30, total_even_min = 1<<30, total_odd_min = 1<<30; 
for (i = 0; i < size; i++) { 
// sum 
total_prime_sum += prime_sums[i]; 
total_even_sum += even_sums[i]; 
total_odd_sum += odd_sums[i]; 
// max 
if (prime_maxs[i] > total_prime_max) total_prime_max = prime_maxs[i]; 
if (even_maxs[i] > total_even_max) total_even_max = even_maxs[i]; 
if (odd_maxs[i] > total_odd_max) total_odd_max = odd_maxs[i]; 
// min 
if (prime_mins[i] < total_prime_min) total_prime_min = prime_mins[i]; 
if (even_mins[i] < total_even_min) total_even_min = even_mins[i]; 
if (odd_mins[i] < total_odd_min) total_odd_min = odd_mins[i]; 
} 
printf("Primes -> Sum: %d, Max: %d, Min: %d\n", total_prime_sum, total_prime_max, total_prime_min); 
printf("Evens -> Sum: %d, Max: %d, Min: %d\n", total_even_sum, total_even_max, total_even_min); 
printf("Odds -> Sum: %d, Max: %d, Min: %d\n", total_odd_sum, total_odd_max, total_odd_min); 
} 
free(sub_data); 
if (rank == 0) { 
free(prime_sums); free(prime_maxs); free(prime_mins); 
free(even_sums); free(even_maxs); free(even_mins); 
free(odd_sums); free(odd_maxs); free(odd_mins); 
} 
MPI_Finalize(); 
return 0; 
} 
