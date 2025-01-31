#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void matrix_addition(int n, int A[n][n], int B[n][n], int C[n][n], int threads) {
    double start_time, end_time;
    
    // Set number of OpenMP threads
    omp_set_num_threads(threads);

    // Start time for parallel execution
    start_time = omp_get_wtime();
    
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // End time for parallel execution
    end_time = omp_get_wtime();
    printf("Parallel Execution Time (Threads = %d): %f seconds\n", threads, end_time - start_time);
}

void serial_matrix_addition(int n, int A[n][n], int B[n][n], int C[n][n]) {
    double start_time, end_time;
    
    // Start time for serial execution
    start_time = omp_get_wtime();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // End time for serial execution
    end_time = omp_get_wtime();
    printf("Serial Execution Time: %f seconds\n", end_time - start_time);
}

int main(void) {
    int n;
    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    int (*A)[n] = malloc(sizeof(int[n][n]));
    int (*B)[n] = malloc(sizeof(int[n][n]));
    int (*C)[n] = malloc(sizeof(int[n][n]));

    // Initialize matrices with random values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Serial Execution
    serial_matrix_addition(n, A, B, C);

    // Parallel Execution with 8 Threads
    matrix_addition(n, A, B, C, 8);

    // Parallel Execution with 16 Threads
    matrix_addition(n, A, B, C, 16);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}