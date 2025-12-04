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

void turntoAngle(int angle) {
  wait(100, msec);

  const double threshold = 1; // how close to target angle to stop
  const double kP = 0.28; // how strongly to turn
  const double maxPower = 80; // max rpm

  double error = angle - Inertial.heading(degrees);
  while (error > threshold || error < -threshold) {
    error = angle - Inertial.heading(degrees);
    double turnPower = error * kP;

    if (turnPower > maxPower) turnPower = maxPower;
    if (turnPower < -maxPower) turnPower = -maxPower;

    if (turnPower >= 0) {
      Left.spin(forward, turnPower, rpm);
      Right.spin(reverse, turnPower, rpm);
    } else {
      Left.spin(reverse, -turnPower, rpm);
      Right.spin(forward, -turnPower, rpm);
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
    wait(100, msec);
  }
}


void autonomous(void) {
  driveForward(200);
  turntoAngle(-90);
  driveForward(700);
  spinIntake(1500);
  turntoAngle(45);
  driveForward(375);
  scoreMiddle(1000);
  wait(500, msec);
  driveReverse(375);
  turntoAngle(-45); 
  driveForward(900);
  spinIntake(1500);
  turntoAngle(-45);
  driveForward(750);
  turntoAngle(45);
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
