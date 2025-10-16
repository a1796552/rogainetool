# rogainetool

A simple tool for calculating a recommended path between points

## Description

This is a tool for use in Rogaining. Rogaines are a sporting event that takes place over several hours (3-24 hours) and the objective is to get the most points within the time frame. Competitors do this using a map and compass to navigate to controls which are worth different amounts of points based off of how difficult the control is to get(points are 10 times the first digit, e.g. 46 is 40 points). 

The purpose of this tool is for the user to input the distance they believe they can travel in the alloted time, the scale using vertical bars, and to click the control points inputting the number for each control. This tool will return the most efficient route in terms of points under the given distance.

## Running The Program

### Dependencies
This tool requires OpenCV which can be installed using 
```
sudo apt install libopencv-dev
```
and will be checked by the makefile.  
The program also uses a Rogaine map in either JPG or PNG format, two have been provided called map.png and map2.png. More maps can be found at the SA Rogaining Website

### Executing The Program

To execute the program, use the command in either root or subfolder
```
make
```
The program will have a pop up window with the map, the terminal is still required for some instructions and text input  

## Help

If the program is not running correctly, try navigating to the sub folder and using the makefile

## Authors

Sunggil Kang - a1796552  
Braden Kerber - a1939333  
Jack Marschall - a1851490  

## Version History
* 0.3
   * Added user interface to main branch
* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release
