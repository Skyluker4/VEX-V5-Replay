#include "v5_cpp.h"
#include <cstdint>

#include "config.hpp"
#include "user.hpp"

void opcontrol(config::Robot& robot, config::MotorValue (&motorValues)[config::numMotors]) {
	using namespace config;

	// React to user input and save to motor value
	motorValues[motor1] = robot.mainController.ButtonA.pressing() ? 100 : 0;
	motorValues[motor2] = robot.mainController.ButtonB.pressing() ? 100 : 0;
	motorValues[motor3] = robot.mainController.ButtonX.pressing() ? 100 : 0;
	motorValues[motor4] = robot.mainController.ButtonY.pressing() ? 100 : 0;
	motorValues[motor5] = robot.mainController.ButtonL1.pressing() ? 100 : 0;
	motorValues[motor6] = robot.mainController.ButtonL2.pressing() ? 100 : 0;
	motorValues[motor7] = robot.mainController.ButtonR1.pressing() ? 100 : 0;
	motorValues[motor8] = robot.mainController.ButtonR2.pressing() ? 100 : 0;

	// Set all motors to their respective values from motor value
	for(uint_fast8_t i = 0; i < config::numMotors; i++)
		MOTOR_CONTROL_STATEMENT(i, motorValues[i]) // Defined by MOTOR_CONTROL_STATEMENT in user.hpp
}
