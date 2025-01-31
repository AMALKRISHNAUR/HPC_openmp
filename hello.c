#include <stdio.h>
#include <omp.h>

int main(void)
{
    //omp_set_num_threads(8);
    int id;
    #pragma omp parallel
    {
        id = omp_get_thread_num();
        printf("Hello from %d\n",id);
    }
}