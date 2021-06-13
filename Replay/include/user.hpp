#ifndef _HEADER_USER
#define _HEADER_USER

#include "config.hpp"

// Defines how each motor is set for the interperter. Saves to line #1 of output. "[INDEX]" defines index of motor
#define MOTOR_CONTROL_STATEMENT(MOTOR_INDEX, MOTOR_VALUE) robot.motors[MOTOR_INDEX].spin(vex::forward, MOTOR_VALUE, vex::rpm);

void opcontrol(config::Robot& robot, config::MotorValue (&motorValues)[config::numMotors]);

#endif
