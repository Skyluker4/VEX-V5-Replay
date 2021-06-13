# Interpreter

This program takes an input file and generates an output file to be used in code.
It's designed to be as modular as possible, automatically detecting the number of motors in use. It generates output code in the form of macros ```MOTOR_CONTROL_STATEMENT(MOTOR_INDEX, MOTOR_VALUE)``` and ```WAIT_STATEMENT(WAIT_TIME)``` which can be implemented however you want to in your project.

## Requirements

- CMake
- C++ compiler (g++, Clang, Visual Studio, etc.)

## Building

In order to build run:
```cmake . -b build```
which will generate the files necessary to build the program in ```build/```.

## Usage

Run ```interpret inputFile outputFile``` with ```inputFile``` being the path to the file saved by the robot and ```outputFile``` being the path to the file that you want the code generated to save to.
