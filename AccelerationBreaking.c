#include <stdlib.h>
#include <stdio.h>

int acceleration(max_speed);
int deacceleration(max_speed);

int main(void){
int max_speed = 0;
    printf("What is the max speed of the cars? \n");
    scanf("%d", max_speed);

    acceleration();
    deacceleration();

return EXIT_SUCCESS;
}
/*acceleration is m/s^2*/
int acceleration(int max_speed){
/*double acceleration = 4.0;*/
    int max_speed_m = 0;
    max_speed_m = max_speed * 0.27;
    printf("%d", max_speed_m);



}
/*deacceleration is m/s^2*/
int deacceleration(int max_speed){
/*double deacceleration = 3.2;*/
    int max_speed_m = 0;
    max_speed_m = max_speed * 0.27;
    printf("%d", max_speed_m);
}
/*double acceleration
double deacceleration*/