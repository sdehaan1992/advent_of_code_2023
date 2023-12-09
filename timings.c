#include "timings.h"

double get_performance(void (*function)(void))
{
    clock_t start = 0;
    clock_t end = 0;
    double cpu_time = NAN;
    start = clock();
    function();
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    return cpu_time;
}
