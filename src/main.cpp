#include "vex.h"
using namespace vex;

competition Competition;


void driveForward(int timeMsec) {
  Inertial.setHeading(0, degrees);

  int elapsed = 0;
  while (elapsed < timeMsec) {
    double heading = 0 - Inertial.heading(degrees);
    double error = 0 - heading;
    double correction = error * 0.8;

    Left.spin(forward, 200 + correction, rpm);
    Right.spin(forward, 200 - correction, rpm);

    wait(10, msec);
    elapsed += 10;
  }
  Left.stop();
  Right.stop();
}

void driveReverse(int timeMsec) {
  Inertial.setHeading(0, degrees);

  int elapsed = 0;
  while (elapsed < timeMsec) {
    double heading = 0 - Inertial.heading(degrees);
    double error = 0 - heading;
    double correction = error * 0.8;

    Left.spin(reverse, 200 + correction, rpm);
    Right.spin(reverse, 200 - correction, rpm);

    wait(10, msec);
    elapsed += 10;
  }
  Left.stop();
  Right.stop();
}

void spinIntake(int timeMsec) {
  Intake.spin(fwd, 600, rpm);
  wait(timeMsec, msec);
  Intake.stop(coast);
}

void scoreMiddle(int timeMsec) {
  Outtake1.spin(fwd, 600, rpm);
  Outtake2.spin(reverse, 600, rpm);
  wait(timeMsec, msec);
  Outtake1.stop(coast);
  Outtake2.stop(coast);
}

void scoreLong(int timeMsec) {
  Outtake1.spin(fwd, 600, rpm);
  Outtake2.spin(fwd, 600, rpm);
  wait(timeMsec, msec);
  Outtake1.stop(coast);
  Outtake2.stop(coast);
}

void turntoAngle(int angle, int maxRPM) {
  int error = angle - Inertial.rotation(deg);
  while (abs(error)>1){

  error = angle - Inertial.rotation(deg);

  int speedRPM = error * 1;
   

    if (speedRPM > maxRPM) speedRPM = maxRPM;
    if (speedRPM < -maxRPM) speedRPM = -maxRPM;

    if (speedRPM >= 0) {
      Left.spin(forward, speedRPM, rpm);
      Right.spin(reverse, speedRPM, rpm);
    } else {
      Left.spin(reverse, -speedRPM, rpm);
      Right.spin(forward, -speedRPM, rpm);
    }

    wait(20, msec);
  }

  Left.stop();
  Right.stop();

}


void pre_auton(void) {
  vexcodeInit();

  Inertial.calibrate();
  while (Inertial.isCalibrating()) {
    wait(20, msec);
  }
}


void autonomous(void) {
  driveForward(100);
  turntoAngle(-90, 333);
  driveForward(700);
  spinIntake(1500);
  turntoAngle(-45, 333);
  driveForward(200);
  scoreMiddle(1000);
  wait(500, msec);
  driveReverse(200);
  turntoAngle(-45,333); 
  driveForward(700);
  spinIntake(1500);
  turntoAngle(-45,333);
  driveForward(750);
  turntoAngle(45,333);
  driveForward(400);
  scoreLong(2000);
}


void usercontrol(void) {
  while (1) {
    float throttle = Controller.Axis3.value();
    if (throttle < 5 && throttle > -5) {
      throttle = 0;
    }
    throttle = throttle / 1.27;

    float turn = Controller.Axis1.value();
    if (turn < 5 && turn > -5) {
      turn = 0;
    }
    turn = turn / 1.27;

    throttle = pow(throttle, 3) / 10000;
    turn = pow(turn, 3) / 10000;

    float leftpow = throttle + turn;
    float rightpow = throttle - turn;

    if (leftpow == 0) {
      Left.stop(brake);
    }
    if (rightpow == 0) {
      Right.stop(brake);
    }

    Left.spin(fwd, (leftpow * 0.12), volt);
    Right.spin(fwd, (rightpow * 0.12), volt);

  
    if (Controller.ButtonR1.pressing()) {
      Intake.spin(fwd, 600, rpm);
    } else if (Controller.ButtonR2.pressing()) {
      Intake.spin(reverse, 600, rpm);
    } else {
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

  }
}

int main() {
  vexcodeInit();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  };
}
