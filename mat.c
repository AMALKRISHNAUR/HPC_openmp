#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

clock_t start, end;
double cpu_time_used;
int main(void)
{
    int i,j;
    int col = 1000;
    int row = 1000;
    int a[row][col];
    int b[row][col];
    int c[row][col];
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            a[i][j] = rand() % row;
        }
    }
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            b[i][j] = rand() % row;
        }
    }
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    start = clock();
    #pragma omp parallel for 
  

        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                c[i][j] = a[i][j]+b[i][j];
            }

        }
    end = clock();
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("parallel execution: %lf\n",cpu_time_used);
    start = clock();
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            c[i][j] = a[i][j]+b[i][j];
        }

    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("the sequential time: %lf\n",cpu_time_used);
}