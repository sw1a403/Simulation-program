# Traffic simulation of Jyllandsgade, Aalborg.
This is our simulation program for Jyllandsgade in Aalborg. The purpose of this program is to try and simulate the travel time of a bus on Jyllandsgade. 

The user will be able to input different factors that will affect the travel time. The following user inputs are possible:

* Max speed of the motor vehicles and bus in km/h.
* Is there traffic lights on the road?
* Amount of traffic lights on the road and timing interval.
* Is there other motor vehicles on the road?
* Amount of other motor vehicles on the road if there is any.

The following factors are static in this simulation program:

* Road length set to 1000m
* Constant acceleration from 0 to max speed in 0 seconds.
* Max amount of traffic lights limited to 5 in the simulation program. 

This way we are able to simulate what affects the travel time of a bus on Jyllandsgade most, and indicate what may reduce the travel time.


# How to use the program.

To use this program you will need to download the source code and compile main.c. You will need a C compiler like MinGW GCC found at: http://www.mingw.org/ to compile this program. 

After compiling the program and running it you will be prompted to type in the follow user inputs:



