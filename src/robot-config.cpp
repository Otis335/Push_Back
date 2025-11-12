#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller;
motor FrontRight = motor(PORT1, ratio18_1, false);
motor FrontLeft = motor(PORT2, ratio18_1, true);
motor BackRight = motor(PORT3, ratio18_1, false);
motor BackLeft = motor(PORT4, ratio18_1, true);

void vexcodeInit(void) {}

motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group Right = motor_group(FrontRight, BackRight);