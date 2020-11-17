#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
int element_compare(const void *ip1, const void *ip2);

int main(void){
    int i = 0; 
    double *numbers = malloc(MAX * sizeof(double));
    if (numbers == NULL){
        printf("Memory could not be allocated");
            exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));

    printf("\nBefore sort:\n\n");
    for (i = 0; i < MAX; ++i){
        numbers[i] = (double)rand();
        printf("Array number [%d] is: %f\n", i, numbers[i]);
    }

    qsort(numbers, MAX, sizeof(double), element_compare);

    printf("\nAfter sort:\n\n");
    for(i = 0; i < MAX; ++i){
        printf("Sorted array number [%d] is: %f\n", i, numbers[i]);
    }
    free(numbers);
    return EXIT_SUCCESS;
}

int element_compare(const void *ip1, const void *ip2){
  int result;
  double *ipi1 = (double *)ip1, *ipi2 = (double *) ip2;

  if (*ipi1 < *ipi2)
     result = -1;
  else if (*ipi1 > *ipi2)
     result = 1;
  else
     result = 0;

  return result;
}