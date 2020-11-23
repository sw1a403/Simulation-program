#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MINUTE 60

void simulate_one_bus();
void speed_vehicle(float *vehicle_speed);
void traffic_light(int *temp_interval);
void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]);
int light_green_or_red(int total_time, int light_interval);
void print_time_intersec(int time, int total_time, int time_added_round, int total_time_added, int round);

int main (void){
    simulate_one_bus(); 
    return EXIT_SUCCESS;
}   

void simulate_one_bus(){
    int dif_dist_intersec[6] = {29, 88, 315, 318, 201, 49};
    int bus, interval;
    float speed;
    speed_vehicle(&speed);
    traffic_light(&interval);
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
        printf("\nTraffic lights will not be implemented\n");
}

void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]){
    int time, round, distance, total_time = 0, total_distance = 0, 
        time_added_round = 0, total_time_added = 0;
    for(round = 0; round <= 5; round++){
        distance = dif_dist_intersec[round];
        time = (int)distance / speed;
        total_time += time;
        time_added_round = light_green_or_red(total_time, light_interval); 
        total_time_added += time_added_round;
        print_time_intersec(time, total_time, time_added_round, total_time_added, round); 
    }
    total_time += total_time_added;
    print_time_intersec(time, total_time, time_added_round, total_time_added, round);
}

int light_green_or_red(int total_time, int light_interval){
    int time_until_change = total_time % light_interval, 
        count = 0, time_added, i;
    for(i = 0; i < total_time; i += light_interval)
        count++;
    if(count % 2 == 1)
        time_added = 0;
    else{
        if(time_until_change == 0)
            time_added = 1;
        else
            time_added = light_interval - time_until_change;
    }
    return time_added;
}

void print_time_intersec(int time, int total_time, int time_added_round, int total_time_added, int round){
    int minutes, seconds;
    char strings_plural[2][8] = {"minutes", "seconds"};
    char strings_singular[2][8] = {"minute", "second"};
    minutes = (int)time / MINUTE;
    seconds = (int)fmod(time, MINUTE);
    if(round <= 5){
        if(minutes == 0){
            printf("The bus reached intersection [%d] after %d %s.\n", (round + 1), seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("The bus reached intersection [%d] after %d %s.\n", (round + 1), minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("The bus reached intersection [%d] after %d %s and %d %s.\n", (round + 1),
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
        minutes = (int)time_added_round / MINUTE;
        seconds = (int)fmod(time_added_round, MINUTE);
        if(time_added_round > 0){
            if(minutes == 0){
                printf("\nAt intersection [%d] there were red light and the bus waited for %d %s.\n\n", (round + 1), seconds,
                (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            } else if(seconds == 0){
                printf("\nAt intersection [%d] there were red light and the bus waited for %d %s.\n\n", (round + 1), minutes, 
                (minutes > 1) ? strings_plural[0] : strings_singular[0]);
            } else{
                printf("\nAt intersection [%d] there were red light and the bus waited for %d %s and %d %s.\n\n", (round + 1),
                minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
                seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            }
        }
    } else {
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
        minutes = (int)total_time_added / MINUTE;
        seconds = (int)fmod(total_time_added, MINUTE);
        if(minutes == 0){
            printf("Total time spend at red light were %d %s.\n", seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("Total time spend at red light were %d %s.\n",  minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("Total time spend at red light were %d %s and %d %s.\n",
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
    }
}