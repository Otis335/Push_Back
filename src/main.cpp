

#include "vex.h"
#include <robot-config.h>

using namespace vex;


competition Competition;

void driveForward (int timeMsec) {
    Inertial.setHeading (0, degrees);

    int elaspsed = 0;

  while (0 < timeMsec) {
    double heading = 0 - Inertial.heading(degrees);
    double error = 0 - heading;

    double correction = error * 0.8; 

  Left.spin (forward, 200 + correction, rpm);
  Right.spin (fwd, 200 - correction, rpm);
  wait(10, msec);
  elaspsed += 10;

  }
  Left.stop();
  Right.stop();
}

void driveReverse (int timeMsec) {
    Inertial.setHeading (0, degrees);

    int elaspsed = 0;

  while (0 < timeMsec) {
    double heading = 0 - Inertial.heading(degrees);
    double error = 0 - heading;

    double correction = error * 0.8; 

  Left.spin (reverse, 200 + correction, rpm);
  Right.spin (reverse, 200 - correction, rpm);
  wait(10, msec);
  elaspsed += 10;

  }
  Left.stop();
  Right.stop();
}

void spinIntake (int timeMsec) {
  Intake.spin (fwd, 600, rpm);
  wait(20, msec);
  Intake.stop (coast);
}

void scoreMiddle (int timeMsec) {
  Outtake1.spin (fwd, 600, rpm);
  Outtake2.spin (reverse, 600, rpm);
  wait(20, msec);
  Outtake1.stop (coast);
  Outtake2.stop (coast);
}

void scoreLong (int timeMsec) {
  Outtake1.spin (fwd, 600, rpm);
  Outtake2.spin (fwd, 600, rpm);
  wait(20, msec);
  Outtake1.stop(coast);
  Outtake2.stop(coast);
}

void turntoAngle (int angle) {
  Inertial.setHeading (0, degrees);
  wait(100, msec);

  while (fabs(angle - Inertial.heading(degrees)) > 1){ 
    double error = angle - Inertial.heading(degrees);
    double turnPower = error * (5/18); //(100/360)

    Left.spin (fwd, turnPower, rpm);
    Right.spin (reverse, turnPower, rpm);
    wait(20, msec);
  }

  Left.stop();
  Right.stop();
}

void pre_auton(void) {
vexcodeInit();

Inertial.calibrate();
  while(Inertial.isCalibrating()) {
  wait (100, msec);
  }

}



void autonomous(void) {
  driveForward (1800);
  spinIntake (1000);
  turntoAngle (-45);
  driveForward (1000);
  scoreMiddle (1000);
  wait (500, msec);
  driveReverse (1000);
  turntoAngle (-125);
  driveForward(500);
  turntoAngle (90);
  //include match loader here
  driveForward(2000);
  spinIntake(1500);
  driveReverse (500);
  //close match loader or something
  turntoAngle (180);
  driveForward (1000);
  scoreLong (1000);

}



void usercontrol(void) {

  while(1)
  {
    float throttle = Controller.Axis3.value();
    if (throttle < 5 && throttle > -5) 
    {
      throttle = 0;
    }
    throttle = throttle / 1.27;
    float turn = Controller.Axis1.value();
    if (turn < 5 && turn > -5) 
    {
      turn = 0;
    }
    turn = turn / 1.27;
    throttle = pow(throttle, 3) / 10000;
    turn = pow(turn, 3) / 10000;
    
    float leftpow;
    float rightpow;

    leftpow = throttle + turn;
    rightpow = throttle - turn;
    if (leftpow == 0)
    {
      Left.stop(brake);
    }
    if (rightpow == 0)
    {
      Right.stop(brake);
    }

    Left.spin(fwd, (leftpow * 0.12), volt);
    Right.spin(fwd, (rightpow * 0.12), volt);

       if (Controller.ButtonR1.pressing()) {
      Intake.spin(fwd, 600, rpm);
    }
    else if (Controller.ButtonR2.pressing()) {
      Intake.spin(reverse, 600, rpm);
    }
    else {
      Intake.stop(coast);
    }
    
    if (Controller.ButtonL1.pressing()) {
      Outtake.spin(fwd, 600, rpm);
    }
    else if (Controller.ButtonL2.pressing()) {
      Outtake.spin(reverse, 600, rpm);
    }
    else {
      Outtake.stop(coast);
    }

    if (Controller.ButtonA.pressing()) {
      Outtake1.spin(fwd, 600, rpm);
    }
    else if (Controller.ButtonY.pressing()) {
      Outtake1.spin(reverse, 600, rpm);
    }
    else {
      Outtake1.stop(coast);
    }
    
    wait(20, msec);
  }



int main() ;
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

 
  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}
