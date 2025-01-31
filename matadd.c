#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

clock_t start, end;
double cpu_time_used;

int main(void)
{
    int i, j;
    int col = 10000;
    int row = 10000;

    // Dynamically allocate memory for the matrices
    int **a = (int**)malloc(row * sizeof(int*));
    int **b = (int**)malloc(row * sizeof(int*));
    int **c = (int**)malloc(row * sizeof(int*));

    for (i = 0; i < row; i++) {
        a[i] = (int*)malloc(col * sizeof(int));
        b[i] = (int*)malloc(col * sizeof(int));
        c[i] = (int*)malloc(col * sizeof(int));
    }

    // Initialize matrices a and b with random values
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            a[i][j] = rand() % row;
            b[i][j] = rand() % row;
        }
    }

    // Uncomment these lines if you want to print matrices a and b
    
    /*
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    */

    // Parallel execution
    start = clock();
    #pragma omp parallel for shared(a,b,c)
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parallel execution time: %lf\n", cpu_time_used);

    // Sequential execution
    start = clock();
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential execution time: %lf\n", cpu_time_used);

    // Free allocated memory
    for (i = 0; i < row; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}
