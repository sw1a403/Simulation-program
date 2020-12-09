# Traffic simulation of Jyllandsgade, Aalborg.
This is our simulation program for Jyllandsgade in Aalborg. The purpose of this program is to try and simulate the travel time of a bus on Jyllandsgade. 

The user will be able to input different factors that will affect the simulation program. The following user inputs are possible:

* Max speed of the motor vehicles and bus in km/h.
* Are there traffic lights on the road?
  * If yes do you want different traffic light models:
    * If yes what traffic light model for each intersection.
    * If no what traffic light model for all intersections.
  * If yes do you want different traffic light timing intervals:
     * If yes what timing intervals for each intersection.
     * If no what timing interval for all intersections.
* Are there other motor vehicles on the road?
* Amount of other motor vehicles on the road if there is any minimum of 2 and maximum of 100.
* Is there more than one lane on the route?
* The amount of lanes on the road choose between two and three lanes. 

The following factors are static in this simulation program:

* Road length set to 950m
* Constant acceleration/deceleration of 1.4 m/s^2
* Amount of traffic lights set to 5 in the simulation program. 

This way we are able to simulate what affects the travel time of a bus on Jyllandsgade most, and indicate what may reduce the travel time.


# How to use the program.

To use this program you will need to download the source code and compile main.c. You will need a C compiler like MinGW GCC found at: http://www.mingw.org/ to compile this program. 

After compiling the program and running it you will be prompted to type in the follow user inputs:

* Max speed of the motor vehicles and bus minimum of 10 km/h and maximum of 60 km/h.
* Are there traffic lights on the road?
  * If yes do you want different traffic light models:
    * If yes what traffic light model for each intersection choose between 2, 6 or 8.
    * If no what traffic light model for all intersections choose between 2, 6 or 8.
  * If yes do you want different traffic light timing intervals:
     * If yes what timing intervals for each intersection minimum 10 seconds and maximum of 100 seconds.
     * If no what timing interval for all intersections minimum 10 seconds and maximum of 100 seconds.
* Are there other motor vehicles on the road?
* Amount of other motor vehicles on the road if there is any minimum of 2 and maximum of 100.
* Is there more than one lane on the route?
  *  If yes what amount of lanes on the road choose between two and three lanes. 



