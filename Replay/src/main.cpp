#include "v5_cpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.hpp"
#include "user.hpp"

// Used to optimize the check to exit, which will only ever be true once
#define unlikely(cond) __builtin_expect(!!(cond), 0)

// Define error codes
#define ERROR_MEM_ALLOC -1 // malloc failed
#define ERROR_SD_WRITE -2  // SD card not found

// Function to reverse linked list
static void reverse(struct MotorValuesNode** head_ref) {
	struct MotorValuesNode* prev = NULL;
	struct MotorValuesNode* current = *head_ref;
	struct MotorValuesNode* next = NULL;

	// Repeat until end of list
	while(current != NULL) {
		// Store next
		next = current->next;

		// Reverse current MotorValuesNode's pointer
		current->next = prev;

		// Move pointers one position ahead.
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

int main() {
	// Set buffer size for line, 64 characters should be more than enough
	constexpr size_t bufferSize = config::outputBufferLength * sizeof(char);

	// Robot setup
	config::Robot robot;

	// Let controller know we are booting up
	robot.mainController.LCD.print("Starting...");

#ifdef USE_SDCARD
	if(!robot.brain.SDcard.isInserted()) {
		// Alert on the controller
		robot.mainController.rumble("---...---");
		robot.mainController.LCD.clearScreen();
		robot.mainController.LCD.setCursor(1, 1);
		robot.mainController.LCD.print("SD Card not found");

// Ask to continue if using serial
#ifdef USE_SERIAL
		robot.mainController.LCD.newLine();
		robot.mainController.LCD.print("Continue?");
		robot.mainController.LCD.newLine();
		robot.mainController.LCD.print("A = Yes/B = No");
		while(true) {
			if(robot.mainController.ButtonA.pressing())
				break;
			if(robot.mainController.ButtonB.pressing())
				return ERROR_SD_WRITE;
			vex::wait(20, vex::msec);
		}
#else
		// Exit
		return ERROR_SD_WRITE;
#endif
	}
#endif

	// String setup
	char* line = (char*)malloc(bufferSize);
	if(line == NULL) {
		robot.mainController.rumble("---...---");
		robot.mainController.LCD.clearScreen();
		robot.mainController.LCD.setCursor(1, 1);
		robot.mainController.LCD.print("Error allocating");
		robot.mainController.LCD.newLine();
		robot.mainController.LCD.print("memory");
		return ERROR_MEM_ALLOC;
	}

	// Linked list setup
	struct MotorValuesNode* head = NULL;
	struct MotorValuesNode* link;

	// Maybe helps with performance? Maybe not, but it doesn't hurt anything AFAIK.
	vexDisplayDoubleBufferDisable();

	// Let other stuff finish just in case
	vex::this_thread::setPriority(vex::task::taskPrioritylow);
	__asm__("YIELD");
	vex::wait(1, vex::seconds);
	vex::this_thread::sleep_for(1000);

	// Go
	vex::this_thread::setPriority(vex::task::taskPriorityHigh);
	robot.mainController.LCD.clearLine(3);
	robot.mainController.LCD.print("Recording");
	robot.mainController.rumble(".");
	uint_fast64_t rawTime = vexSystemHighResTimeGet();

	// Collect data
	while(true) {
		// Generate new MotorValuesNode
		link = (MotorValuesNode*)malloc(sizeof(MotorValuesNode));

		// BEGIN MOTOR CONTROL

		// Call opcontrol function (not as efficient (compiler doesn't inline it)) or write driver control here
		// Must set values in linked list to save
		opcontrol(robot, link->motorValues);

		// END MOTOR CONTROL

		// Save pointer to previous MotorValuesNode in current MotorValuesNode
		link->next = head;
		head = link;

		// Check for exit condition and exit if true
		if(unlikely(robot.mainController.ButtonY.pressing() && robot.mainController.ButtonA.pressing()))
			break;

		// Wait for the specified delay time to wait for the controller
		WAIT_STATEMENT(config::delayTime)
	}

	// Begin to save data collected
	// Stop all motors
	config::stopAllMotors(robot.motors);

	// Time isn't important to us anymore
	vex::this_thread::setPriority(vex::task::taskPriorityNormal);

	// Notify controller that we are saving the data
	robot.mainController.LCD.clearLine(3);
	robot.mainController.LCD.print("Saving...");
	robot.mainController.rumble("..");

	// Reverse the list so it's in the right order (really more like unreversing it)
	reverse(&head);

	// Write new file

#ifdef USE_SDCARD
	// Set filename to write to
	char* filename = (char*)malloc(256 * sizeof(char));
	sprintf(filename, "recording.txt");
	// Change filename if there are other files with same name
	constexpr size_t readBufferSize = 2 * sizeof(char);
	uint8_t* readBuffer = (uint8_t*)malloc(readBufferSize);
	for(int i = 1; robot.brain.SDcard.loadfile(filename, readBuffer, readBufferSize) > sizeof(char); i++)
		sprintf(filename, "recording-%u.txt", i);
	free(readBuffer);
	robot.brain.SDcard.savefile(filename, (uint8_t*)" ", strlen(" "));	// IDK if this is necessary for creating the file or if appendfile does that automatically
#endif

	// Read the list and free the nodes after reading them
	struct MotorValuesNode* ptr = head;
	struct MotorValuesNode* oldPtr;
	while(ptr != NULL) {
		// Save the info
		int length = 0;
		for(int i = 0; i < config::numMotors; i++)
			length += sprintf(line + length, FMT " ", ptr->motorValues[i]);
		sprintf(line + length - 1, "\n");

#ifdef USE_SERIAL
		// Print to serial
		printf("%s", line);
		vex::wait(0.1, vex::seconds);
#endif
#ifdef USE_SDCARD
		// Print to SD Card
		robot.brain.SDcard.appendfile(filename, (uint8_t*)line, strlen(line));
#endif

		// Get MotorValuesNode to free
		oldPtr = ptr;

		// Go to next MotorValuesNode
		ptr = ptr->next;

		// Free the old MotorValuesNode
		free(oldPtr);
	}

	// Free up everything else
	free(line);
#ifdef USE_SDCARD
	free(filename);
#endif

	// Done
	robot.mainController.LCD.clearLine(3);
	robot.mainController.LCD.print("Finished! Y+A to exit.");
	robot.mainController.rumble("-");

	// Exit program and go back to runscreen
	while(!(robot.mainController.ButtonY.pressing() && robot.mainController.ButtonA.pressing()))
		vex::wait(20, vex::msec);
	vexSystemExitRequest();
}