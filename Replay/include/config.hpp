#ifndef _HEADER_CONFIG
#define _HEADER_CONFIG

#include <cstdint>

// Write to serial?
#define USE_SERIAL
// Write to SD card?
#define USE_SDCARD

// User-defined control statements
#define WAIT_STATEMENT(DELAY_TIME)                            \
	while(vexSystemHighResTimeGet() - rawTime < (DELAY_TIME)) \
		;                                                     \
	rawTime = vexSystemHighResTimeGet();

// Format string, should match type of MotorValue
#define FMT "%d"

namespace config {
	// Set wait time in microseconds (1000μs = 1ms)
	constexpr uint_fast64_t delayTime = 20000;

	// Can be changed to whatever type is being recorded
	typedef int_fast32_t MotorValue;

	// Only change this if the string is getting cut off on output. 64 characters should be more than enough
	constexpr size_t outputBufferLength = 64;

	typedef uint_fast8_t Port;

	// Reference motors by name
	typedef enum MotorNames {
		motor1,
		motor2,
		motor3,
		motor4,
		motor5,
		motor6,
		motor7,
		motor8,
		numMotors // Do not delete! Used to count how many total motors there are
	} MotorName;

	// Robot configuration
	struct Robot {
		vex::brain brain;
		vex::controller mainController;
		vex::motor motors[numMotors] = {
			vex::motor(vex::PORT1, vex::ratio18_1, false),
			vex::motor(vex::PORT2, vex::ratio18_1, false),
			vex::motor(vex::PORT3, vex::ratio18_1, false),
			vex::motor(vex::PORT4, vex::ratio18_1, false),
			vex::motor(vex::PORT5, vex::ratio18_1, false),
			vex::motor(vex::PORT6, vex::ratio18_1, false),
			vex::motor(vex::PORT7, vex::ratio18_1, false),
			vex::motor(vex::PORT8, vex::ratio18_1, false)
		};
	};

	// Helper function to stop all motors
	void stopAllMotors(vex::motor (&motors)[numMotors]);
} // namespace config

// Linked list MotorValuesNode structure
struct MotorValuesNode {
	config::MotorValue motorValues[config::numMotors];
	struct MotorValuesNode* next;
};

#endif
