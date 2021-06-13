# VEX V5 Replay

A solution that allows you to record and playback robot movements.
Motor values are recorded at a set interval and saved via serial connection or to the micro-SD card.
This solution contains three projects, ```Replay``` is a VEXCode V5 Pro C++ project to record movements, ```Interpreter``` is a CMake C++ project to read the input and save it to a file to be copied into a program, and ```ReplayTest``` is a VEXCode V5 Pro C++ project to quickly test the interpreted output.
This solution contains three projects, ```Replay``` is a VEXCode V5 Pro C++ project to record movements, ```Interpreter``` is a CMake C++ project to read the input and save it to a file to be copied into a program, and ```ReplayTest``` is a VEXCode V5 Pro C++ project to quickly test the interpreted output.

## Accuracy

This program may not always replay motions with 100% accuracy. Currently, it is configured to record values that a motor is set to at a certain interval. This can be modified, however. The longer a recording is, the less accurate it will be as it progresses through.
It is crucial to start the robot in the same position every time. Recording and been designed to be as precise and as efficient as possible to help eliminate any discrepancies with timing.

## Requirements

- VEXcode V5 Pro
- CMake
- C++ compiler (g++, Clang, Visual Studio, etc.)

### Optional

- Micro-SD Card (formatted to FAT-32)

## Usage

See ```README.md``` of [```Replay```](Replay/README.md), [```Interpreter```]((Interpreter/README.md)), and [```ReplayTest```](ReplayTest/README.md) for more information for each project.

1. [Configure ```Replay```](Replay/README.md)
   1. Change the robot configuration accordingly
   2. Set if you'd like to output to serial, micro-SD card, or both
   3. Add your ```opcontrol``` code to control the robot
2. Compile and Upload ```Replay``` to your robot
3. Run ```Replay``` (default slot is slot #7)
   1. Starts recording after a 2 second delay
   2. End recording by pressing the buttons ```Y``` and ```A``` on the main controller at the same time
4. Save output to computer
5. Run Interpreter on the file
   1. [Modify and build if necessary](Interpreter/README.md)
   2. Usage ```interpret inputFile outputFile```
6. Paste output where it needs to go
   1. [Test the program with ```ReplayTest```](ReplayTest/README.md) (default slot is slot #8)

## What about PROS?

It shouldn't be too hard to port ```Replay``` and ```ReplayTest``` over to the PROS.
If you do manage it get it working on PROS, submit a pull request.

## Future Plans

Some features that would be nice to have later:

- PROS support
- Creating a program that allows you to select from a list of already recorded files and then play them back from inside of the robot without ever having to go to the computer to generate the code
- Allow pausing while recording
- Figure out how to record encoder/sensor values and use them in a meaningful way
- A GUI to manage and edit recorded data
