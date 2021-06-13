# Replay Test

This program can be used for testing how the robot performs when replaying the recorded actions.

## Requirements

- VEXcode V5 Pro

## Configuration

In order for the program to run correctly, the following have to be configured correctly:

- ```MOTOR_CONTROL_STATEMENT(MOTOR_INDEX, MOTOR_VALUE)``` must be properly defined. Preferably in the same way it was in ```Replay```. This macro will set the specified motor to the recorded value.
- ```WAIT_STATEMENT(DELAY_TIME)``` must be properly defined. Preferably in the same way it was in ```Replay```. This will control how the robot waits. There's not much reason to change the type, but the intervals can be made faster or slower depending on your preference. Currently set to 20000 microseconds.
- ```constexpr [type] delayTime``` must be defined. The type can be changed if needed (from ```unsigned int``` to ```float```, for example). Preferably be the same as it was in ```Replay```.
- ```vex::motor motors[]``` must include all motors that will be set during the runtime of the program. The order and configuration of the motors should match exactly with how they were in ```Replay```.

## Building

Build in VEXcode Pro V5. Open the ```ReplayTest.v5code``` project file and select ```Build```.

## Usage

By default, the program saves in slot #8 under the name ```ReplayTest```. Run the program and it will start its movements after 2 seconds of waiting.
