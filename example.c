#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1000
#define MINUTE 60

void simulate_one_bus();
void traffic_light(int *temp_interval);
void speed_vehicle(float *vehicle_speed);

int main (void){
    simulate_one_bus(); 
    return EXIT_SUCCESS;
}   

void simulate_one_bus(){
    int bus, minutes, seconds, time, interval;
    float speed;
    char strings_plural[2][8] = {"minutes", "seconds"};
    char strings_singular[2][8] = {"minute", "second"};


    traffic_light(&interval);
    speed_vehicle(&speed);

    time = (int)distance / speed;
    minutes = (int)time / MINUTE;
    seconds = (int)fmod(time, MINUTE);

    if(minutes == 0){
        printf("The travel time is: %d %s.\n", seconds,
        (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    }
    else if(seconds == 0){
        printf("The travel time is: %d %s. \n", minutes, 
        (minutes > 1) ? strings_plural[0] : strings_singular[0]);
    }
    else{
        printf("The travel time is: %d %s and %d %s. \n", 
        minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
        seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    }

}

void traffic_light(int *temp_interval){
    int temp;
    char answer;
    while(answer != 'y' && answer != 'n'){
        printf("\nDo you want traffic lights to be implemented? (y/n): ");
        scanf(" %c", &answer);
    }
        if(answer == 'y'){
            printf("\nHow long should the intervals be in seconds? Round number only: ");
            scanf(" %d", &temp);
            *temp_interval = temp;
        }
        else if(answer == 'n')
            printf("\nTraffic lights will not be implemented");
}

void speed_vehicle(float *vehicle_speed){
    float temp;
    printf("Enter speed (km/h): ");
    scanf(" %f", &temp);
    temp /= 3.6;
    *vehicle_speed = temp;
    printf("Converted to m/s. You entered: %2.3f\n", *vehicle_speed);
}

