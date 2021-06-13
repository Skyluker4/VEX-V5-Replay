#include "v5_cpp.h"

// Defines how the specified motor will be set to the recorded value. Should match with the Replay program. If you copy it in from Replay, you'll need to remote "robot." from motors
#define MOTOR_CONTROL_STATEMENT(MOTOR_INDEX, MOTOR_VALUE) motors[MOTOR_INDEX].spin(vex::forward, MOTOR_VALUE, vex::rpm);

// Defines how the robot will wait. Should match with the Replay program. Not much of a reason to change this.
#define WAIT_STATEMENT(DELAY_TIME)                             \
	while (vexSystemHighResTimeGet() - rawTime < (DELAY_TIME)) \
		;                                                      \
	rawTime = vexSystemHighResTimeGet();

int main() {
	// Motor configuration. Make sure this matches how they were when they were recorded in the Replay program
	vex::motor motors[] = {
		vex::motor(vex::PORT1, vex::ratio18_1, false),
		vex::motor(vex::PORT2, vex::ratio18_1, false),
		vex::motor(vex::PORT3, vex::ratio18_1, false),
		vex::motor(vex::PORT4, vex::ratio18_1, false),
		vex::motor(vex::PORT5, vex::ratio18_1, false),
		vex::motor(vex::PORT6, vex::ratio18_1, false),
		vex::motor(vex::PORT7, vex::ratio18_1, false),
		vex::motor(vex::PORT8, vex::ratio18_1, false)
	};

	// Set base time to wait for each recorded moment
	constexpr unsigned int delayTime = 20000;

	// Maybe helps with performance? Maybe not, but it doesn't hurt anything AFAIK.
	vexDisplayDoubleBufferDisable();

	// Let other stuff finish just in case, probably not necessary
	vex::this_thread::setPriority(vex::task::taskPrioritylow);
	__asm__("YIELD");
	vex::wait(1, vex::seconds);
	vex::this_thread::sleep_for(1000);

	// Go
	vex::this_thread::setPriority(vex::task::taskPriorityHigh);
	uint_fast64_t rawTime = vexSystemHighResTimeGet();

	// START

	// PASTE INTERPRETED OUTPUT HERE
	MOTOR_CONTROL_STATEMENT(0, 0)
	MOTOR_CONTROL_STATEMENT(1, 0)
	MOTOR_CONTROL_STATEMENT(2, 0)
	MOTOR_CONTROL_STATEMENT(3, 0)
	MOTOR_CONTROL_STATEMENT(4, 0)
	MOTOR_CONTROL_STATEMENT(5, 0)
	MOTOR_CONTROL_STATEMENT(6, 0)
	MOTOR_CONTROL_STATEMENT(7, 0)
	WAIT_STATEMENT(delayTime)

	MOTOR_CONTROL_STATEMENT(0, 100)
	WAIT_STATEMENT(delayTime)

	MOTOR_CONTROL_STATEMENT(0, 0)
	MOTOR_CONTROL_STATEMENT(1, 60)
	WAIT_STATEMENT(delayTime * 5)

	MOTOR_CONTROL_STATEMENT(1, 0)
	WAIT_STATEMENT(delayTime)

	// END

	// Stop all motors
	for (vex::motor motor : motors)
		motor.stop();

	// Time isn't important to us anymore
	vex::this_thread::setPriority(vex::task::taskPriorityNormal);

	// Exit the program
	vexSystemExitRequest();
}
