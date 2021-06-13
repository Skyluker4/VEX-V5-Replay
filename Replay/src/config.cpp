#include "v5_cpp.h"
#include "config.hpp"

namespace config {
	void stopAllMotors(vex::motor (&motors)[numMotors]) {
		for(vex::motor motor : motors)
			motor.stop();
	}
}
