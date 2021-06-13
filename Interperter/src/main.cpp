#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main(const int argc, const char* const argv[]) {
	// Check if all parameters are entered
	if (argc != 3) {
		// Display help otherwise
		std::cout << "Usage: " << argv[0] << " fileInputName fileOutputName" << std::endl;
		return -1;
	}

	try {
		// Open the input file
		std::ifstream input(argv[1]);
		if (input.is_open()) {
			// Get number of motors
			std::string str_numMotors;
			std::getline(input, str_numMotors);
			const unsigned int numMotors = static_cast<unsigned int>(std::count(
				str_numMotors.begin(), str_numMotors.end(), ' ')) + 1;
			// Reset line number back to the beginning
			input.seekg(std::ios::beg);

			// Open the output file
			std::ofstream output(argv[2]);
			if (output.is_open()) {
				// Motors
				struct Motor {
					std::string in, old;
				};
				std::vector<Motor> motors(numMotors);

				// Loop through all lines of input file
				bool changed = false;
				unsigned int timesLooped = 0;
				while (!input.eof()) {
					// Read value from input
					for (Motor& motor : motors) {
						input >> motor.in;

						// Check if it's changed
						if (motor.in != motor.old) {
							changed = true;
						}
					}

					// Write wait time when changing motor values if the value changed and it's not the first iteration
					if (changed && !motors[0].old.empty()) {
						output << "WAIT_STATEMENT(delayTime" + (timesLooped <= 1 ? "" : "*" + std::to_string(timesLooped)) + ")" << std::endl << std::endl;

						// Reset the variables
						changed = false;
						timesLooped = 0;
					}

					// Write motor commands if motor value changed
					for (unsigned int i = 0; i < motors.size(); i++) {
						if (motors[i].in != motors[i].old) {
							// Write to file
							output << "MOTOR_CONTROL_STATEMENT(" << i << ", " << motors[i].in << ")" << std::endl;

							// Set old input value
							motors[i].old = motors[i].in;
						}
					}

					timesLooped++;
				}
				// Save wait time for final loop
				output << "WAIT_STATEMENT(delayTime" + (timesLooped <= 1 ? "" : "*" + std::to_string(timesLooped)) + ")";

				output.close();
			}
			else {
				std::cerr << "Error creating output file." << std::endl;
				return -4;
			}
			input.close();
		}
		else {
			std::cerr << "Error opening input file." << std::endl;
			return -3;
		}
	}
	catch (const std::exception& e) {
		// Couldn't open file
		std::cerr << "Error reading file." << std::endl;
		std::cerr << e.what() << std::endl;
		return -2;
	}

	std::cout << "Finished successfully!" << std::endl;
}
