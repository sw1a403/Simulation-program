#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/*
v = a*t + v__0, t = 9.92;

s = 1/2 * a * t^2 + v__0 * t + s__0 = 68.88448 m

Braking:
s = -vo^2/(2a)

Find new values for these
a = 1.4 m/s^2
braking = 3.2 m/s^2

We don't use scanf when we implement this function
When implementing this function, we have 4 parameters:
the constant time t
the constant distance to accelerate from 0-50 km/h
the array containing the distances between intersections
whether the traffic light is green or red.
*/

void gaymink(double max_speed, const double acceleration, const double decceleration, double *time, double *distance, char green_or_red);

int main(void){

    const double acceleration = 1.4, decceleration = -3.2;
    double time, distance, max_speed;
    char green_or_red;
    printf("Enter the max speed for the cars: ");
    scanf(" %lf", &max_speed);
    printf("\nIs the traffic light red or green? (g/r): ");
    scanf(" %c", &green_or_red);
    
    max_speed /= 3.6;

    gaymink(max_speed, acceleration, decceleration, &time, &distance, green_or_red);

    printf("\nTime: %2.3f and distance: %2.3f\n", time, distance);

    return EXIT_SUCCESS;
}


/*acceleration is m/s^2*/

void gaymink(double max_speed, const double acceleration, const double decceleration, double *time, double *distance, char green_or_red){

    /*Acceleration*/

    if(green_or_red == 'g'){
        *time = max_speed/acceleration;

        *distance = (0.5 * acceleration * pow(*time, 2));
    }

    /*Decceleration*/
    else{
        *time = -max_speed/decceleration;
        *distance = -(pow(max_speed, 2))/(2 * decceleration);
    }
}