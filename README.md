# rogainetool

A simple tool for calculating a recommended path between points

## Description

This is a tool for use in Rogaining. Rogaines are a sporting event that takes place over several hours (3-24 hours) and the objective is to get the most points within the time frame. Competitors do this using a map and compass to navigate to controls which are worth different amounts of points based off of how difficult the control is to get(points are 10 times the first digit, e.g. 46 is 40 points). 

The purpose of this tool is for the user to input the distance they believe they can travel in the alloted time, the scale using vertical bars, and to click the control points inputting the number for each control. This tool will return the most efficient route in terms of points under the given distance.

## Getting Started
It is recommended to navigate to the RogaineTool subfolder and use the makefile to compile and run:

cd RogaineTool
make

### Dependencies
OpenCV is required for the map interaction. Use the following line to install:
sudo apt install libopencv-dev

### Installing

...

### Input Files

The program only requires an image file (jpg or png) of a rogaine map, two are provided and more are available on the Rogaine SA website. This is configured in the terminal.

### Executing program

The program can be compiled and run using the commands:
./rogaine in the root folder. 

Otherwise, use the make file to recompile and check for OpenCV (THIS IS RECOMMENDED):
cd RogaineTool
make

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
