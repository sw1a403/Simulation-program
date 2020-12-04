#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MINUTE 60

void simulate_one_bus();
void speed_vehicle(float *vehicle_speed);
void traffic_light(int *answer_model, int *answer_interval);
int *traffic_model(int answer_model);
int *traffic_interval(int answer_interval);
void calculate_travel_time(float speed, int dif_dist_intersec[6], int traffic_light_model[5], int traffic_light_interval[5]);
int *traffic_inflow(int *vehicles);
int more_lanes();
int light_green_or_red(int total_time, int traffic_light_interval[5], int traffic_light_model[5], int round);
int ac_dec_celeration(float speed, int dif_dist_intersec[6], int round, int *ac_dec_time, int *to_short);
void print_time_intersec(int time, int total_time, int time_added_round, int total_time_added, int round);


int main (void){
    simulate_one_bus(); 
    return EXIT_SUCCESS;
}   

void simulate_one_bus(){
    int dif_dist_intersec[6] = {29, 78, 305, 308, 191, 39};
    int *traffic_light_model, *traffic_light_interval;
    float speed;
    int answer_model = 0, answer_interval = 0;
    speed_vehicle(&speed);
    traffic_light(&answer_model, &answer_interval);
    traffic_light_model = traffic_model(answer_model);
    traffic_light_interval = traffic_interval(answer_interval);
    calculate_travel_time(speed, dif_dist_intersec, traffic_light_model, traffic_light_interval);
}

void speed_vehicle(float *vehicle_speed){
    float temp;
    printf("Enter speed (km/h). Can't be slower than 1, or faster than 80: ");
    while(temp < 1 || temp > 80)
        scanf(" %f", &temp);
    temp /= 3.6;
    *vehicle_speed = temp;
    printf("Converted to m/s. You entered: %2.3f\n", *vehicle_speed);
}

void traffic_light(int *answer_model, int *answer_interval){
    char answer, temp_answer_model, temp_answer_interval;
    printf("\nDo you want traffic lights to be implemented? (y/n): ");
    while(answer != 'y' && answer != 'n')
        scanf(" %c", &answer);
    if(answer == 'y'){
        printf("\nDo you want the different intersections to have different traffic light models? (y/n): ");
        while(temp_answer_model != 'y' && temp_answer_model != 'n')
            scanf(" %c", &temp_answer_model);
        if(temp_answer_model == 'y')
            *answer_model = 1;
        printf("\nDo you want the different intersections to have different intervals? (y/n): ");
        while(temp_answer_interval != 'y' && temp_answer_interval != 'n')
            scanf(" %c", &temp_answer_interval);
        if(temp_answer_interval == 'y')
            *answer_interval = 1;        
    } else if(answer == 'n'){
        printf("\nTraffic lights will not be implemented.");
        *answer_model = -1;
        *answer_interval = -1;
    }
}

int *traffic_model(int answer_model){
    int *traffic_light_model = (int*)malloc(5 * sizeof(int)), i, temp_model = 0;
    for(i = 0; i < 5; i++){
        if(answer_model == -1){
            traffic_light_model[i] = 0;
            continue;
        }else if(answer_model == 1){
            temp_model = 0;
            printf("\nWhich traffic light model do you want in intersection[%d]? Answer must be 2, 6 or 8 (int only): ", (i + 1));
        }else if(answer_model == 0 && i == 0)
            printf("\nWhich traffic light model do you want for the intersections? Answer must be 2, 6 or 8 (int only): ");    
        while(temp_model != 2 && temp_model != 6 && temp_model != 8)
            scanf(" %d", &temp_model);
        traffic_light_model[i] = temp_model;
    }
    return traffic_light_model;
}

int *traffic_interval(int answer_interval){
    int *traffic_light_interval = (int*)malloc(5 * sizeof(int)), i, temp_interval = 0;
    for(i = 0; i < 5; i++){
        if(answer_interval == -1){
            traffic_light_interval[i] = 0;
            continue;
        }else if(answer_interval == 1){
            temp_interval = 0;
            printf("\nHow long should the intervals for intersection[%d] be in seconds? Must be between 10 & 60 (int only): ", (i + 1));
        } else if(answer_interval == 0 && i == 0)
            printf("\nHow long should the intervals for the intersections be in seconds? Must be between 10 & 60 (int only): ");       
        while(temp_interval < 10 || temp_interval > 60)
            scanf(" %d", &temp_interval);
        traffic_light_interval[i] = temp_interval;
    }
    return traffic_light_interval;
}

void calculate_travel_time(float speed, int dif_dist_intersec[6], int traffic_light_model[5], int traffic_light_interval[5]){
    int time, round, total_time = 0, *inflow, vehicles, i, j, k, time_next_intersec,
        vehicles_in_front, temp_time_added_round = 0,  timer_traffic_light = 0,
        time_added_round = 0, total_time_added = 0, amount_lanes = 1, place = 0,
        intersec_arrays[3][6][100], vehicle_rest, ac_dec_time = 0, to_short;
    float intersec_dist = 10, time_through_intersec = 0;
    inflow = traffic_inflow(&vehicles);
    amount_lanes = more_lanes();
    if(amount_lanes != 1){
        for(i = 0; i < vehicles; i++){
            for(j = 0; j < amount_lanes; j++){
                intersec_arrays[j][0][place] = inflow[i];
                i++;
                if(i >= vehicles)
                    break;
            }
            place++;
        }
        vehicle_rest = vehicles % amount_lanes;
        vehicles = (vehicles - vehicle_rest) / amount_lanes;
        if(vehicle_rest == 0)
            printf("\nThe vehicles split into the %d different lanes,"
                   "\nthere is %d vehicles in each lane", amount_lanes, vehicles);
        else if(vehicle_rest == 1)
            printf("\nThe vehicles split into the %d different lanes,"
                   "\nthere is %d vehicles in one lane and %d in the others", amount_lanes, (vehicles + 1), vehicles);
        else if(vehicle_rest == 2)
            printf("\nThe vehicles split into the %d different lanes,"
                   "\nthere is %d vehicles in two lane and %d in the last one", amount_lanes, (vehicles + 1), vehicles);
    }    
    for(i = 0; i < 3; i++)
        for(j = 1; j < 6; j++)
            for(k = 0; k < vehicles; k++){
                intersec_arrays[i][j][k] = 0;
                if(amount_lanes == 1)
                    intersec_arrays[i][0][j] = inflow[j];
            }
    for(round = 0; round <= 5; round++){
        if(temp_time_added_round != 0){
            if(round == 5)
                time = ac_dec_time;
            else{
                time = (int)dif_dist_intersec[round] / speed + ac_dec_time;
                dif_dist_intersec[round + 1] = ac_dec_celeration(speed, dif_dist_intersec, round, &ac_dec_time, &to_short);
            }
        } else
            time = (int)dif_dist_intersec[round] / speed;
        timer_traffic_light += time;
        temp_time_added_round = 0;
        j = 0;
        k = 0;
        if(round < 5)
            for(i = 0; i < vehicles; i++){
                if(intersec_arrays[0][round][i] != 0){
                    intersec_arrays[0][round + 1][i] = intersec_arrays[0][round][i];  
                    if(traffic_light_interval[round] == 0)
                        time_added_round = 0;
                    else if(traffic_light_interval[round] != 0){
                        time_added_round = light_green_or_red(timer_traffic_light, traffic_light_interval, traffic_light_model, round);
                        time_next_intersec = (int)dif_dist_intersec[round + 1] / speed + timer_traffic_light + ac_dec_time;
                        if(intersec_arrays[0][round + 1][j] != 0 && light_green_or_red(time_next_intersec, traffic_light_interval, traffic_light_model, round) == 0){
                            intersec_arrays[0][round + 2][j] = intersec_arrays[0][round + 1][j];
                            j++;
                        }else if(intersec_arrays[0][round + 2][k] != 0 && light_green_or_red(time_next_intersec, traffic_light_interval, traffic_light_model, round) == 0){
                            intersec_arrays[0][round + 3][k] = intersec_arrays[0][round + 2][k];
                            k++;
                        }                
                        if(time_added_round > 1){
                            temp_time_added_round += time_added_round; 
                            vehicles_in_front = vehicles - (i + 2);
                            if(vehicles_in_front == 0)
                                printf("\nThe traffic light is red, but the bus is in the front.");
                            else
                                printf("\nThere is a red light. There are %d vehicles in front of the bus."
                                    "\nTime before green light %d", vehicles_in_front, time_added_round);
                            time += time_added_round + ac_dec_time;
                            timer_traffic_light += time_added_round;
                        } else{
                            if(time_through_intersec > 1){
                                time++;
                                timer_traffic_light++;
                                temp_time_added_round++;
                                time_through_intersec = 0;
                            } else
                                time_through_intersec += intersec_dist / speed;
                        }
                    }
                }
            }    
        total_time += time; 
        total_time_added += temp_time_added_round;
        print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round); 
        if(temp_time_added_round > 1 && round <= 4 && round != 0){
            if(to_short == 1)
                printf("\nAfter intersection [%d] the bus didn't accelerate to full speed,"
                       "\nThe added time is %d\n", round + 1, ac_dec_time);
            else
                printf("\nTime added for acceleration is %d\n", ac_dec_time);   
        }    
    }
    print_time_intersec(time, total_time, temp_time_added_round, total_time_added, round);
}

int *traffic_inflow(int *vehicles){
    int temp = 0, i, *array;
    char answer;
    printf("\nDo you want inflow? These will be the vehicles before the bus. (y/n): ");
    while(answer != 'y' && answer != 'n')
        scanf(" %c", &answer);
    if(answer == 'y'){
        printf("\nHow many vehicles would you like? (int only, min 1, max 100): ");
        while(temp < 1 || temp > 100)
            scanf(" %d", &temp);
        temp++;
        *vehicles = temp;
        array = (int*)malloc(temp * sizeof(int));
        for(i = 0; i < temp; i++){
            array[i] = 1;
            if((i + 1) == temp)
                array[i] = 2;
        }
    } else{
        printf("\nThere will be no other vehicles than the bus.");
        array = (int*)malloc(sizeof(int));
        *vehicles = 1;
        array[0] = 2;
    }
    return array;
}

int more_lanes(){
    int lanes = 0;
    char answer_lanes;
    printf("\nDo you want more than one lane? (y/n): ");
    while(answer_lanes != 'y' && answer_lanes != 'n')
        scanf(" %c", &answer_lanes);
    if(answer_lanes == 'y'){
        printf("\nDo you want two or three lanes? (int only): ");
        while(lanes != 2 && lanes != 3)
            scanf(" %d", &lanes);
    } else if(answer_lanes == 'n'){
        printf("\nThere will only be used one lane.");
        lanes = 1;
    }
    return lanes;
}

int ac_dec_celeration(float speed, int dif_dist_intersec[6], int round, int *ac_dec_time, int *to_short){
    const double acceleration = 1.4, decceleration = -3.2;
    int ac_time, ac_dist;
    ac_time = (int)speed / acceleration;
    ac_dist = 0.5 * acceleration * pow(ac_time, 2);
    if(ac_dist >= dif_dist_intersec[round + 1]){
        ac_time = (int)sqrt(dif_dist_intersec[round + 1] / (0.5 * acceleration));
        *to_short = 1;
    } else{
        dif_dist_intersec[round + 1] -= ac_dist;
        *to_short = 0;
    }
    *ac_dec_time = ac_time;
    return dif_dist_intersec[round + 1];
}

int light_green_or_red(int total_time, int traffic_light_interval[5], int traffic_light_model[5], int round){
    int time_until_change = total_time % traffic_light_interval[round], 
        count = 0, time_added, i, divisor = 0;
    switch(traffic_light_model[round]){
        case 2:
            divisor = 2; break;
        case 6:
            divisor = 3; break;
        case 8:
            divisor = 4; break;
    }
    for(i = 0; i < total_time; i += traffic_light_interval[round])
        count++;
    if(count % divisor == 1)
        time_added = 0;
    else{
        if(time_until_change == 0)
            time_added = 1;
        else        
            time_added = traffic_light_interval[round] - time_until_change;
    }    
    return time_added;
}

void print_time_intersec(int time, int total_time, int time_added_round, int total_time_added, int round){
    int minutes, seconds;
    char strings_plural[2][8] = {"minutes", "seconds"};
    char strings_singular[2][8] = {"minute", "second"};
    if(round <= 4){
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
        if(round <= 4){
            minutes = (int)time / MINUTE;
            seconds = (int)fmod(time, MINUTE);
            if(minutes == 0){
                printf("\nThe bus reached intersection [%d] after %d %s.\n", (round + 1), seconds,
                (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            } else if(seconds == 0){
                printf("\nThe bus reached intersection [%d] after %d %s.\n", (round + 1), minutes, 
                (minutes > 1) ? strings_plural[0] : strings_singular[0]);
            } else{
                printf("\nThe bus reached intersection [%d] after %d %s and %d %s.\n", (round + 1),
                minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
                seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
            }
        }
    } else if(round == 6){
        minutes = (int)time / MINUTE;
        seconds = (int)fmod(time, MINUTE);
        if(minutes == 0){
            printf("\nThe bus drove from intersection [%d] to the end of the street in %d %s.\n", (round - 1), seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nThe bus drove from intersection [%d] to the end of the street in %d %s.\n", (round - 1), minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nThe bus drove from intersection [%d] to the end of the street in %d %s and %d %s.\n", (round - 1),
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
        minutes = (int)total_time_added / MINUTE;
        seconds = (int)fmod(total_time_added, MINUTE);
        if(minutes == 0){
            printf("\nTotal time spend at red light were %d %s.", seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nTotal time spend at red light were %d %s.",  minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nTotal time spend at red light were %d %s and %d %s.",
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
        minutes = (int)total_time / MINUTE;
        seconds = (int)fmod(total_time, MINUTE);     
        if(minutes == 0){
            printf("\nThe bus reached the end of the course after %d %s.\n", seconds,
            (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        } else if(seconds == 0){
            printf("\nThe bus reached the end of the course after %d %s.\n", minutes, 
            (minutes > 1) ? strings_plural[0] : strings_singular[0]);
        } else{
            printf("\nThe bus reached the end of the course after %d %s and %d %s.\n", 
            minutes, (minutes > 1) ? strings_plural[0] : strings_singular[0],
            seconds, (seconds > 1) ? strings_plural[1] : strings_singular[1]);
        }
    }
}