#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MINUTE 60

void simulate_one_bus();
void speed_vehicle(float *vehicle_speed);
void traffic_light(int *temp_interval);
void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]);
int *traffic_inflow(int *vehicles);
int light_green_or_red(int total_time, int light_interval);
void print_time_intersec(int time, int total_time, int time_added_round, int total_time_added, int round);

int main (void){
    simulate_one_bus(); 
    return EXIT_SUCCESS;
}   

void simulate_one_bus(){
    int dif_dist_intersec[6] = {29, 88, 315, 318, 201, 49};
    int interval;
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
        printf("\nTraffic lights will not be implemented.");
}
/*
void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]){
    int time, round, distance, total_time = 0, *inflow, vehicles, i, 
        time_through_intersec, intersec_dist = 20, vehicles_in_front,
        temp_time_added_round = 0,
        time_added_round = 0, total_time_added = 0, first_intersec[50];
    inflow = traffic_inflow(&vehicles);
    for(round = 0; round <= 5; round++){
        distance = dif_dist_intersec[round];
        time = (int)distance / speed;
        total_time += time;
        for(i = 0; i < vehicles; i++){
            if(round == 5)
                break;
            if(round % 2 == 1)
                first_intersec[i] = inflow[i];
            else if(round % 2 == 0)
                inflow[i] = first_intersec[i];
            time_through_intersec = (int)intersec_dist / speed;
            temp_time_added_round += time_added_round;
            total_time += time_through_intersec;
            time += time_through_intersec;
            time_added_round = light_green_or_red(total_time, light_interval);
            total_time += time_added_round;
            if(time_added_round > 0){
                vehicles_in_front = vehicles - (i + 1);
                if(vehicles_in_front == 0)
                    printf("\nThe traffic light is red, but the bus is in the front.");
                else
                    printf("\nThere is a red light. There are %d vehicles in front of the bus."
                           "\nThe bus waited for %d seconds", vehicles_in_front, time_added_round);
            }
            temp_time_added_round += time_through_intersec;
        }
        total_time_added += temp_time_added_round;
        print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round); 
        temp_time_added_round = 0;
    }
    print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round);
} */

void calculate_travel_time(int light_interval, float speed, int dif_dist_intersec[6]){
    int time, round, distance, total_time = 0, *inflow, vehicles, i, j,
        time_through_intersec, intersec_dist = 20, vehicles_in_front,
        temp_time_added_round = 0, time_next_intersec,
        time_added_round = 0, total_time_added = 0;
    int multiple_intersec_arrays[6][50];
    inflow = traffic_inflow(&vehicles);
    for(i = 0; i < 6; i++){
        for(j = 0; j <= vehicles; j++){
            multiple_intersec_arrays[0][j] = inflow[j];
            if(i != 0)
                multiple_intersec_arrays[i][j] = 0;
        }
    }
    for(round = 0; round <= 5; round++){
        time = (int)dif_dist_intersec[round] / speed;
        total_time += time;
        temp_time_added_round = 0;
        j = 0;
        for(i = 0; i < vehicles; i++){
            if(multiple_intersec_arrays[round][i] != 0){
                multiple_intersec_arrays[round][i] = multiple_intersec_arrays[round + 1][i];  
                time_through_intersec = (int)intersec_dist / speed;
                total_time += time_through_intersec;
                time += time_through_intersec;
                time_added_round = light_green_or_red(total_time, light_interval);
                time_next_intersec = (int)dif_dist_intersec[round + 1] / speed + total_time;
                if(multiple_intersec_arrays[round + 1][j] != 0 && light_green_or_red(time_next_intersec, light_interval) == 0){
                    multiple_intersec_arrays[round + 2][j] = multiple_intersec_arrays[round + 1][j];
                    j++;
                }
                total_time += time_added_round;
                temp_time_added_round += time_added_round;
                temp_time_added_round += time_through_intersec;
                if(time_added_round > 0){
                    vehicles_in_front = vehicles - (i + 1);
                    if(vehicles_in_front == 0)
                        printf("\nThe traffic light is red, but the bus is in the front.");
                    else
                        printf("\nThere is a red light. There are %d vehicles in front of the bus."
                            "\nTime before %d green light", vehicles_in_front, time_added_round);
                }
            }
        }
        total_time_added += temp_time_added_round;
        print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round); 
    }
    print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round);
}

int *traffic_inflow(int *vehicles){
    int temp, i, *array;
    char answer;
    while(answer != 'y' && answer != 'n'){
        printf("\nDo you want inflow? These will be the vehicles before the bus. (y/n): ");
        scanf(" %c", &answer);
    }
    if(answer == 'y'){
        printf("\nHow many vehicles would you like? (int only, max 50): ");
        scanf(" %d", &temp);
        *vehicles = temp;
        array = (int*)malloc(temp * sizeof(int));
        for(i = 0; i < temp; i++){
            array[i] = 1;
            if((i + 1) == temp)
                array[i] = 2;
        }
    }
    else if(answer == 'n'){
        printf("\nThere will be no other vehicles than the bus.");
        array = (int*)malloc(sizeof(int));
        *vehicles = 1;
        array[0] = 2;
    }
    return array;
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
            printf("\nThe bus reached intersection [%d] after %d %s.", (round + 1), seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nThe bus reached intersection [%d] after %d %s.", (round + 1), minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nThe bus reached intersection [%d] after %d %s and %d %s.", (round + 1),
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
        minutes = (int)time_added_round / MINUTE;
        seconds = (int)fmod(time_added_round, MINUTE);
        if(time_added_round > 0){
            if(minutes == 0){
                printf("\n\nAt intersection [%d] there were red light and the bus waited for %d %s.\n", (round + 1), seconds,
                (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            } else if(seconds == 0){
                printf("\n\nAt intersection [%d] there were red light and the bus waited for %d %s.\n", (round + 1), minutes, 
                (minutes > 1) ? strings_plural[0] : strings_singular[0]);
            } else{
                printf("\n\nAt intersection [%d] there were red light and the bus waited for %d %s and %d %s.\n", (round + 1),
                minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
                seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            }
        }
    } else{
        minutes = (int)total_time / MINUTE;
        seconds = (int)fmod(total_time, MINUTE);     
        if(minutes == 0){
            printf("\nThe bus reached the end of the course after %d %s.", seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nThe bus reached the end of the course after %d %s.", minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nThe bus reached the end of the course after %d %s and %d %s.", 
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
        minutes = (int)total_time_added / MINUTE;
        seconds = (int)fmod(total_time_added, MINUTE);
        if(minutes == 0){
            printf("\nTotal time spend at red light were %d %s.\n", seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nTotal time spend at red light were %d %s.\n",  minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nTotal time spend at red light were %d %s and %d %s.\n",
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
    }
}