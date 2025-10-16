# rogainetool

A simple tool for calculating a recommended path between points

## Description



## Getting Started

### Dependencies

* Describe any prerequisites, libraries, OS version, etc., needed before installing program.
* ex. Windows 10

### Installing

...

### Input Files

The program requires an input file to run. The file is made up of lines with the format:
```
checkpointNumber, Xcoordinate, Ycoordinate, points
```
With the first checkpoint representing the start with checkpointNumber = 0 and points = 0

Example of the contents of a file:
```
0, 0, 0, 0
1, 1, 3, 2
2, 3, 1, 3
3, 4, 6, 7
```

### Executing program

The program can be compiled and run using the commands:
```
g++ RogaineTool/main.cpp RogaineTool/checkpoint.cpp RogaineTool/routePlanner.cpp -o rogaine
./rogaine <filename>
```

Premade test files are located in the testfile folder. To run a test file as input use the command:
```
./rogaine TestFiles/testfile1.txt 
```

## Help

If the program is not running correctly, ensure that the input files match the format specified above

## Authors

Sunggil Kang - a1796552
Braden Kerber - a1939333
Jack Marschall - a1851490

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release