#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1000

int main (void){
    int bus;
    float speed, time;
    printf("Enter speed (km/h): ");
    scanf(" %f", &speed);
    speed /= 3.6;
    printf("Converted to m/s. You entered: %2.3f\n", speed);
    time = (float)distance / speed;
    printf("The travel time is : %4.1f seconds.\n", time);

    return EXIT_SUCCESS;
}   