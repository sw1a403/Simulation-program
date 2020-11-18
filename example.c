#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MINUTE 60

void simulate_one_bus();
void speed_vehicle(float *vehicle_speed);
void traffic_light(int *temp_interval);
void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]);

int main (void){
    simulate_one_bus(); 
    return EXIT_SUCCESS;
}   

void simulate_one_bus(){
    int dif_dist_intersec[6] = {29, 88, 315, 318, 201, 49};
    int bus, interval;
    float speed;
    traffic_light(&interval);
    speed_vehicle(&speed);
    calculate_travel_time(interval, speed, dif_dist_intersec);
}

void speed_vehicle(float *vehicle_speed){
    float temp;
    printf("Enter speed (km/h): ");
    scanf(" %f", &temp);
    temp /= 3.6;
    *vehicle_speed = temp;
    printf("Converted to m/s. You entered: %2.3f\n", *vehicle_speed);
}

void traffic_light(int *temp_interval){
    int temp;
    char answer;
    while(answer != 'y' && answer != 'n'){
        printf("\nDo you want traffic lights to be implemented? (y/n): ");
        scanf(" %c", &answer);
    }
    if(answer == 'y'){
        printf("\nHow long should the intervals be in seconds? (int only): ");
        scanf(" %d", &temp);
        *temp_interval = temp;
    }
    else if(answer == 'n')
        printf("\nTraffic lights will not be implemented");
}

void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]){
    int minutes, seconds, time, i, distance, total_time = 0, total_distance = 0;
    char strings_plural[2][8] = {"minutes", "seconds"};
    char strings_singular[2][8] = {"minute", "second"};

    for(i = 0; i <= 5; i++){
        distance = dif_dist_intersec[i];
        total_distance += distance;
        time = (int)distance / speed;
        total_time += time;
        minutes = (int)time / MINUTE;
        seconds = (int)fmod(time, MINUTE);     
        if(minutes == 0){
            printf("The bus reached intersection [%d] after %d %s.\n", (i + 1), seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("The bus reached intersection [%d] after %d %s.\n", (i + 1), minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("The bus reached intersection [%d] after %d %s and %d %s.\n", (i + 1),
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
    }
    total_time = (int)total_distance / speed;
    minutes = (int)total_time / MINUTE;
    seconds = (int)fmod(total_time, MINUTE);     
    if(minutes == 0){
        printf("The bus reached the end of the course after %d %s.\n", seconds,
        (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    } else if(seconds == 0){
        printf("The bus reached the end of the course after %d %s.\n", minutes, 
        (minutes > 1) ? strings_plural[0] : strings_singular[0]);
    } else{
        printf("The bus reached the end of the course after %d %s and %d %s.\n", 
        minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
        seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
    }
}