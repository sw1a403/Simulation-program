#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define distance 1

int main (void){
    int speed, bus, time;
    printf("test:");
    scanf("\n%d", &speed);
    printf("%d", speed);
    time = (int)distance / speed;
    printf("\n%d", time);
    printf("Gay Mink");
    return EXIT_SUCCESS;
}
    