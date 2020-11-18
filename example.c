#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1000
#define MINUTE 60
/* hej */ 
int main (void){
    int minutes, seconds, time;
    float speed;
    char strings_plural[2][8] = {"minutes", "seconds"};
    char strings_singular[2][8] = {"minute", "second"};
    printf("Enter speed (km/h): ");
    scanf(" %f", &speed);
    speed /= 3.6;
    printf("Converted to m/s. You entered: %2.3f\n", speed);

    time = (int)distance / speed;
    minutes = time / (int)MINUTE;
    seconds = fmod(time, MINUTE);

    if (minutes == 0){
        printf("The travel time is: %d %s.\n", seconds,
        (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    }

    else if (seconds == 0){
        printf("The travel time is: %d %s. \n", minutes, 
        (minutes > 1) ? strings_plural[0] : strings_singular[0]);
    }
    
    else{
        printf("The travel time is: %d %s and %d %s. \n", 
        minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
        seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    }
    return EXIT_SUCCESS;
}   