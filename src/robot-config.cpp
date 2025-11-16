#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller;
motor FrontRight = motor(PORT1, ratio18_1, false); //not updated, port number change
motor FrontLeft = motor(PORT2, ratio18_1, true);
motor BackRight = motor(PORT3, ratio18_1, false);
motor BackLeft = motor(PORT4, ratio18_1, true);
motor Front = motor(PORT10, ratio6_1); //port undetermined, unfinished below
motor Middle = motor(PORT11, ratio6_1); //port undetermined
motor Outtake1 = motor(PORT12,ratio6_1); //port undetermined
motor Outtake2 = motor(PORT13,ratio6_1); //port undertermined

void vexcodeInit(void) {}

motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group Right = motor_group(FrontRight, BackRight);
motor_group Intake = motor_group(Middle, Outtake1);
motor_group Outtake = motor_group(Outtake2);