#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1000

int main (void){
    int speed, bus, time;
    printf("Enter speed:");
    scanf(" %d", &speed);
    printf("You entered: %d\n", speed);
    time = (int)distance / speed;
    printf("The travel time is : %d", time);
    
    return EXIT_SUCCESS;
}
    