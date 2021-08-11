/* Program to demonstrate time taken by function timed() */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "speculation_barrier.h"

// A function that creates a large array and exits
void timed(int argc, char *argv[])
{
int i;
int val;
int limit;
int array[10000];
int option  = atoi(argv[2]);
limit = 10000;
for (i = 0; i < 10000; i++) {
    array[i] = i;
    //printf("%d ", array[i]);
}
int untrusted_value = 34;
if (untrusted_value < limit){
    if (option == 1){
        val = load_no_speculate (array + untrusted_value, array, array + limit);
    }
    else{
        val = array[untrusted_value];
    }
}

}
  
// The main program calls timed() and measures time taken by timed()
// accepts two command line argumnets. first to specify number of runs and the second one enables the load_no_speculate mitigation with '1'
int main(int argc, char *argv[])
{
int i;   
 double num[1000];
    double sum, avg;
    int times = atoi(argv[1]);
    while (times > 1000 || times < 1 && argc == 2) {
        printf("Error! number should in range of (1 to 1000).\n");
        exit(0);
    }
    for (i = 0; i < times;  i++){
        // Calculate the time taken by fun()
        clock_t t;
        t = clock();
        timed(argc, argv);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        num[i] = time_taken;
    //printf("%f ", num[i]);        
    sum += num[i];
    //printf("%f ", sum);
    }
    avg = sum / times;
    printf("Average time took %f seconds to execute \n", avg);
    return 0;
}
