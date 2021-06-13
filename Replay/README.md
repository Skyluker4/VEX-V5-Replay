# Replay

This program records data from the robot at a certain interval. It is currently configured to record motor values, but can be modified to record whatever data you want. The only files that really need modified in order for the program to be usable are ```config.hpp```, ```user.hpp```, and ```user.cpp```.

## Requirements

- VEXcode V5 Pro

### Optional

- Micro-SD Card (formatted to FAT-32)

## Configuration

- ```MOTOR_CONTROL_STATEMENT(MOTOR_INDEX, MOTOR_VALUE)``` in ```user.hpp``` must be properly defined. This macro will set the specified motor to the recorded value.
- ```WAIT_STATEMENT(DELAY_TIME)``` in ```config.hpp``` must be properly defined. This will control how the robot waits. There's not much reason to change this.
- ```constexpr [type] delayTime``` in ```config.hpp``` must be defined. The type can be changed if needed (from ```unsigned int``` to ```float```, for example). There's not much reason to change the type, but the intervals can be made faster or slower depending on your preference. Currently set to 20000 microseconds.
- ```enum MotorName config::MotorNames``` in ```config.hpp``` must include the names of all of your motors. Even if you plan on referencing them by index, something must be put for each motor, as this also keeps track of how many motors are going to be used.
- ```vex::motor config::Robot::motors[numMotors]``` in ```config.hpp``` must include all motors that will be used. The order of the motors needs to match with the names given in ```enum MotorName config::MotorNames```.
- ```void opcontrol(config::Robot& robot, config::MotorValue (&motorValues)[config::numMotors])``` in ```user.cpp``` should include code for controlling the robot. It needs to save the values it's setting the motors to in ```config::MotorValue (&motorValues)[config::numMotors]``` and set the motors themselves to that value as well. Currently there is a loop at the end of the function that automatically sets the motors to the values in ```motorValues```. This way, all the user-control has to do is set the values in the array and the motors will be automatically set at the end. See the code provided for an example.
- ```USE_SERIAL``` in ```config.hpp``` should be defined if the output should sent to a computer via USB serial connection. Otherwise comment out.
- ```USE_SDCARD``` in ```config.hpp``` should be defined if the output should be saved to an SD card. Otherwise comment out.

## Building

Build in VEXcode Pro V5. Open the ```Replay.v5code``` project file and select ```Build```.

## Usage

By default, the program saves in slot #7 under the name ```Replay```. Run the program and it will start recording movements after 2 seconds of waiting. It will alert you when it's started by vibrating and displaying a message. To stop the robot, press the buttons ```Y``` and ```A``` on the main controller at the same time. Wait until the controller notifies you that it's done saving by vibrating and displaying a message saying that it's done.

## Recording Data

All data is saved at the end, after the user does the stop command. Nothing is transmitted or saved while the robot is still moving and data is still being recorded.

### Serial Connection

The program can output to a computer directly using the serial connection over USB. The output can be accessed through the console in VEXcode V5, in ```pros-cli``` using ```prosv5 terminal [PORT]```, or another program that can communicate via serial. Serial communication is slower (and less reliable) than saving to an SD card, so only use this option if you do not have access to a micro-SD card. Serial over the wireless controller is even slower, and the delay rate in ```int main()``` in ```main.cpp``` might need to be increased if data is being lost.

### Micro-SD Card

The SD card must be formatted to ```FAT-32``` to be used by the robot. The program saves a file called ```recording.txt``` to the root of the SD card. If a file already exists with that name, it will append a number to the name of the file (and keep increasing until there is a unique filename) so it save as ```recording-1.txt```. This means that more recent files will have a higher number appended to their filename.
