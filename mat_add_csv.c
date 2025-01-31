#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int n, int A[n][n], int B[n][n], int C[n][n], int threads, double *time_taken) {
    double start_time, end_time;
    
    // Set OpenMP thread count
    omp_set_num_threads(threads);

    // Start measuring time
    start_time = omp_get_wtime();
    // collapse(2)
    #pragma omp parallel for 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // End measuring time
    end_time = omp_get_wtime();
    *time_taken = end_time - start_time;
}

void serial_matrix_addition(int n, int A[n][n], int B[n][n], int C[n][n], double *time_taken) {
    double start_time, end_time;
    
    start_time = omp_get_wtime();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    end_time = omp_get_wtime();
    *time_taken = end_time - start_time;
}

int main() {
    FILE *file = fopen("performance_data.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // CSV Header
    fprintf(file, "Matrix Size, Serial Time, Parallel (8 Threads), Parallel (16 Threads)\n");

    int sizes[] = {100, 500, 1000, 2000, 3000,4000,6000,7000,8000,9000,10000,12000,14000,16000,18000,20000,22000,24000,28000,30000}; // Different matrix sizes to test
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    for (int j = 0;j<16;j++)
    {
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));

        // Initialize matrices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        double serial_time, parallel_8_time, parallel_16_time;

        // Measure execution times
        serial_matrix_addition(n, A, B, C, &serial_time);
        matrix_addition(n, A, B, C, j, &parallel_8_time);
        //matrix_addition(n, A, B, C, 16, &parallel_16_time);

        // Save results to CSV
        fprintf(file, "%d, %d, %f, %f\n", n,j, serial_time, parallel_8_time);

        // Free allocated memory
        free(A);
        free(B);
        free(C);
    }
    }
    fclose(file);
    printf("Performance data saved to performance_data.csv\n");

    return 0;
}
