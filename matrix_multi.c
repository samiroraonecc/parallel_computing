#include <mpi.h> 
#include <stdio.h> 
int main(int argc, char** argv) 
{  int rank; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
int arow = 3, acol = 3,brow = 3, bcol = 3; 
int A[arow][acol], B[brow][bcol], C[arow][bcol]; 
if (rank == 0) 
{ int v=1; 
for (int i = 0; i < arow; i++) 
for (int j = 0; j < acol; j++) 
A[i][j] = v++; 
MPI_Send(A,9, MPI_INT, 2, 123, MPI_COMM_WORLD);  } 
else if (rank == 1) 
{   int v=10; 
for (int i = 0; i < brow; i++) 
for (int j = 0; j < bcol; j++) 
B[i][j] = v++; 
MPI_Send(B, brow * bcol, MPI_INT, 2, 123, MPI_COMM_WORLD); 
} 
else if (rank == 2) 
{ 
MPI_Recv(A,9, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
MPI_Recv(B,9, MPI_INT, 1, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
for (int i = 0; i < arow; i++) 
{ 
for (int j = 0; j < bcol; j++) 
{ 
C[i][j] = 0; 
for (int k = 0; k < acol; k++) 
{ 
C[i][j] += A[i][k] * B[k][j]; 
} 
} 
} 
printf("Matrix C:\n"); 
for (int i = 0; i < arow; i++) 
{ 
for (int j = 0; j < bcol; j++) 
{ 
printf("%d ", C[i][j]); 
} 
printf("\n"); 
}   } 
MPI_Finalize(); 
return 0; 
} 
