#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller Controller;
motor FrontRight = motor(PORT11, ratio18_1, false); 
motor FrontLeft = motor(PORT14, ratio18_1, true);
motor BackRight = motor(PORT13, ratio18_1, false);
motor BackLeft = motor(PORT12, ratio18_1, true);
motor Middle = motor(PORT8, ratio6_1, true); 
motor Outtake1 = motor(PORT6,ratio6_1, false); 
motor Outtake2 = motor(PORT7,ratio6_1, true); 

void vexcodeInit(void) {}

motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group Right = motor_group(FrontRight, BackRight);
motor_group Intake = motor_group(Middle, Outtake1);
motor_group Outtake = motor_group(Outtake2);