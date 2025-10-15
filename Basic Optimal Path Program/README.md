# rogainetool
This is a tool for use in Rogaining. Rogaines are a sporting event that takes place over several hours (3-24 hours) and the objective is to get the most points within the time frame. Competitors do this using a map and compass to navigate to controls which are worth different amounts of points based off of how difficult the control is to get(points are 10 times the first digit, e.g. 46 is 40 points). 

The purpose of this tool is for the user to input the distance they believe they can travel in the alloted time, the scale using vertical bars, and to click the control points inputting the number for each control. This tool will return the most efficient route in terms of points under the given distance.

Note: Use the makefile given by typing 'make' into the terminal, this tool requires OpenCV which can be installed using 'sudo apt install libopencv-dev' and will be checked by the makefile