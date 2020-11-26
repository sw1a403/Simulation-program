# Traffic simulation of Jyllandsgade, Aalborg.
This is our simulation program for Jyllandsgade in Aalborg. The purpose of this program is to try and simulate the travel time of a bus on Jyllandsgade. 

The user will be able to input different factors that will affect the simulation program. The following user inputs are possible:

* Max speed of the motor vehicles and bus in km/h.
* Are there traffic lights on the road?
* Traffic lights timing interval in seconds with a minimum of 1 second and a maximum of 60 seconds.
* Are there other motor vehicles on the road?
* Amount of other motor vehicles on the road if there is any minimum of 2 and maximum of 100.
* Is there more than one lane on the route?
* The amount of lanes on the road choose between two and three lanes. 

The following factors are static in this simulation program:

* Road length set to 1000m
* Constant acceleration of 1.4 m/s^2
* Constant deceleration of -3.2 m/s^2
* Amount of traffic lights set to 5 in the simulation program. 

This way we are able to simulate what affects the travel time of a bus on Jyllandsgade most, and indicate what may reduce the travel time.


# How to use the program.

To use this program you will need to download the source code and compile main.c. You will need a C compiler like MinGW GCC found at: http://www.mingw.org/ to compile this program. 

After compiling the program and running it you will be prompted to type in the follow user inputs:

* Max speed of the motor vehicles and bus in km/h will be converted to m/s.
* Do you want to use traffic light during the simulation?
  * If yes what traffic light interval do you want between 1 and 60 seconds.
* Do you want other motor vehicles in front of the bus being simulated?
  * If yes how many motor vehicles with a minimum of 2 and a maximum of 100.
* Do you want more than one lane?
  * If yes do you want two or three lanes for the simulation. (Note this will distrubite the user inputted other motor vehicles to more than one lane.)
 


