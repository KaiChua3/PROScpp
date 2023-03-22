#include "main.h"
#include "pros/motors.hpp"
#include <chrono>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1,"Hello PROS User!");
	pros::lcd::register_btn1_cb(on_center_button);
	pros::ADIDigitalOut piston ('A');
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
#define Motor_Port 18 //Flywheel Motor
#define DIGITAL_SENSOR_PORT 'B' //Exapansion
#define EXPANSIONPNEUMATIC 'A' //Same thing as above
#define IntakeMotor_PORT 17 //Intake
#define LEFT_WHEELS_PORT 15 //Front left wheel of drivetrain
#define RIGHT_WHEELS_PORT 16 //Front right wheel of drivetrain
#define LEFT_WHEELS_BACK_PORT 11 //Back left wheel of drivetrain
#define RIGHT_WHEELS_BACK_PORT 12 //Back right wheel of drivetrain
#define ROLLER_MOTOR_PORT 13 //Roller
#define OPTICAL_PORT 1 //Front Optical Sensor
#define VISION_PORT 20 //Vision Sensor
#define OPTICAL_PORT_BACK 4 //Side Optical Sensor

void autonomous() {
  pros::delay(10);
  pros::Motor Flywheel (Motor_Port, true);
  pros::ADIDigitalOut pistonExpansion2 (DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut pistonExpansion (EXPANSIONPNEUMATIC);
  pros::Motor intake (IntakeMotor_PORT);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Optical optical_sensor(OPTICAL_PORT);
  pros::Motor_Group left_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group right_drivetrain({right_wheels,right_wheels_back});
  //Auton for Worlds
  //
  //**START OF AUTON**
  //
  //Reverses into roller
  left_drivetrain.move_velocity(-300);
  right_drivetrain.move_velocity(-300);
  pros::delay(2000);
  //
  //Spins roller while moving backwards
  //Uses Optical sensor to spin roller until color is not detected
  //
  left_drivetrain.move_velocity(-300);
  right_drivetrain.move_velocity(-300);
  if (optical_sensor.get_hue() >= 210 && optical_sensor.get_hue() <= 280) {
    roller.move_velocity(-125);
  }
  pros::delay(2000);
  left_drivetrain.move_velocity(0);
  right_drivetrain.move_velocity(0);
  roller.move_velocity(0);
  pros::delay(1);
  //
  //Moves away from roller
  //
  left_drivetrain.move_velocity(150);
  right_drivetrain.move_velocity(150);
  pros::delay(100);
  left_drivetrain.move_velocity(0);
  right_drivetrain.move_velocity(0);
  pros::delay(1);
//
// **END OF AUTON**
//
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  pros::Motor Flywheel (Motor_Port, true);
  pros::ADIDigitalOut pistonExpansion2 (DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut pistonExpansion (EXPANSIONPNEUMATIC);
  pros::Motor intake (IntakeMotor_PORT);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Optical optical_sensor(OPTICAL_PORT);
  pros::Controller master (CONTROLLER_MASTER);
  pros::Optical optical_sensor_back(OPTICAL_PORT_BACK);
  bool isPressedExpansion = master.get_digital(DIGITAL_X);
  /**
  Sets expansion so it won't release; just a precaution in case initial set values are reversed
  */
  pistonExpansion.set_value(true);
  pistonExpansion2.set_value(true);
  optical_sensor.set_led_pwm(100);
  while (true) {
    pistonExpansion.set_value(true);
    pistonExpansion2.set_value(true);
    isPressedExpansion = master.get_digital(DIGITAL_X);
    //
    //If Button R1 is pressed, Flywheel will begin to spin
    //
    if (master.get_digital(DIGITAL_R1)) {
      Flywheel.move_velocity(135);
    } else {
      Flywheel.move_velocity(0);
    }
    /**
    If Button L1 is pressed, intake turns clockwise
    */
    if (master.get_digital(DIGITAL_L1)){
      intake.move_velocity(210);
    } 
    //If Button R2 is pressed, intake turns counter clockwise (old feature from A team bot MAY NOT BE NECESSARY)
    else if (master.get_digital(DIGITAL_R2)){
      intake.move_velocity(-210);
    } else {
      intake.move_velocity(0);
    }
    /**
    Optical Sensor code:
    When color (red) is detected, motor will begin to spin
    Needs to change to spin for blue
    There are 2 if statements since there is gonna be 2 optical sensors
    */
    if (optical_sensor.get_hue() >= 210 && optical_sensor.get_hue() <= 280) {
      roller.move_velocity(100);
    } else {
      roller.move_velocity(0);
    }
    if (optical_sensor.get_hue() >= 210 && optical_sensor.get_hue() <= 280) {
      roller.move_velocity(100);
    } else {
      roller.move_velocity(0);
    }
    /**
    If Button X is pressed, expansion will activate
    */
    if(isPressedExpansion){
        pistonExpansion.set_value(false);
        pistonExpansion2.set_value(false);
      pros::delay(2);
    } else if (!isPressedExpansion) {
        pistonExpansion.set_value(true);
        pistonExpansion2.set_value(true);
    } 
    left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
    left_wheels_back.move(master.get_analog(ANALOG_LEFT_Y));
    right_wheels.move(master.get_analog(ANALOG_RIGHT_Y) * 10);
    right_wheels_back.move(master.get_analog(ANALOG_RIGHT_Y) * 10);
  }
}