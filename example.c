#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1000
#define MINUTE 60

int main (void){
    int bus;
    float speed, time, minutes, seconds;
    printf("Enter speed (km/h): ");
    scanf(" %f", &speed);
    speed /= 3.6;
    printf("Converted to m/s. You entered: %2.3f\n", speed);

    time = (float)distance / speed;
    minutes = time / (float)MINUTE;
    seconds = fmod(time, MINUTE);

    if(minutes == 1){
        printf("The travel time is: 1 minute");
    }
    else if(minutes > 1){
         printf("The travel time is: %4.1f minute", minutes);
    }
    else{
        printf("The travel time is: 0 minutes");
    }
    if(seconds == 60){
        printf(" and 1 second");
    }
    else if(seconds > 1){
         printf(" and %4.1f seconds", seconds);
    }
    else{
        printf(" and 0 seconds");
    }
    return EXIT_SUCCESS;
}   