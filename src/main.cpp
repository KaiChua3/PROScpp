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
	pros::lcd::set_text(1, "Hello PROS User!");

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
#define Motor_Port 18
#define DIGITAL_SENSOR_PORT 'B'
#define EXPANSIONPNEUMATIC 'A'
#define IntakeMotor_PORT 17
#define LEFT_WHEELS_PORT 15
#define RIGHT_WHEELS_PORT 16
#define LEFT_WHEELS_BACK_PORT 11
#define RIGHT_WHEELS_BACK_PORT 12
#define ROLLER_MOTOR_PORT 13
#define INDEX2_PORT 14
#define INDEX3_PORT 3
#define OPTICAL_PORT 1
#define VISION_PORT 20
void turn_left() {
 pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
right_drivetrain.move_velocity(300);
left_drivetrain.move_velocity(-300);
pros::delay(500);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
}
void turn_right() {
   pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
  left_drivetrain.move_velocity(300);
  right_drivetrain.move_velocity(-300);
  pros::delay(500);
  left_drivetrain.move_velocity(0);
  right_drivetrain.move_velocity(0);
}
void spin_roller() {
	  pros::Motor roller (ROLLER_MOTOR_PORT, true);
	  roller.move_velocity(150);
	  pros::delay(500);
	  roller.move_velocity(0);
}
void move_bot_forward() {
   pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
  all_drivetrain.move_velocity(300);
  pros::delay(500);
  all_drivetrain.move_velocity(0);
}
void autonomous() {
  pros::Task::delay(10);
   pros::Motor Flywheel (Motor_Port, true);
  pros::ADIDigitalOut pistonExpansion2 (DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut pistonExpansion (EXPANSIONPNEUMATIC);
  pros::Motor intake (IntakeMotor_PORT);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor indexerPush (INDEX2_PORT);
  pros::Optical optical_sensor(OPTICAL_PORT);
  pros::Motor_Group left_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group right_drivetrain({right_wheels,right_wheels_back});
  //New Auton
  //
  //**START OF AUTON**
  //
  //Reverses into roller
  left_drivetrain.move_velocity(-300);
  right_drivetrain.move_velocity(-300);
  pros::delay(2000);
  //
  //Spins roller while moving backwards
  //
  left_drivetrain.move_velocity(-300);
  right_drivetrain.move_velocity(-300);
  indexerPush.move_velocity(-125);
  pros::delay(200);
  roller.move_velocity(-400);
  pros::delay(5000);
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
  //Spin up flywheel
  //
  Flywheel.move_velocity(75);
  pros::delay(3000);
  //
  //Indexer is pushed up; getting ready to fire
  //
  Flywheel.move_velocity(75);
  indexerPush.move_velocity(125);
  pros::delay(50);
  //
  //Flywheel shoots the disc/discs
  //
  Flywheel.move_velocity(75);
  indexerPush.move_velocity(125);
  roller.move_velocity(-100);
  intake.move_velocity(210);
  pros::delay(1000);
  indexerPush.move_velocity(0);
  roller.move_velocity(0);
  intake.move_velocity(0);
  Flywheel.move_velocity(0);
  pros::delay(1);
//
// **END OF AUTON**
//
  
  
/**
right_drivetrain.move_velocity(300);
left_drivetrain.move_velocity(-300);
pros::delay(500);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
*/
/** Old Auton DO NOT USE
pistonExpansion.set_value(false);
left_drivetrain.move_velocity(300);
right_drivetrain.move_velocity(300);
pros::delay(500);
left_drivetrain.move_velocity(300);
right_drivetrain.move_velocity(300);
roller.move_velocity(180);
pros::delay(1000);
roller.move_velocity(180);
all_drivetrain.move_velocity(0);
pros::delay(1);
//Beyond here is the new auton

left_drivetrain.move_velocity(-65);
right_drivetrain.move_velocity(-50);
roller.move_velocity(180);
//Move backwards to position bot
pros::delay(500);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
roller.move_velocity(0);
pros::delay(100);
left_drivetrain.move_velocity(65);
right_drivetrain.move_velocity(-50);
//Turns bot to face goal
pros::delay(315);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
rightFlywheel.move_velocity(99);
  //Spin up flywheel
pros::delay(4000);
rightFlywheel.move_velocity(99);
pistonFlywheel.set_value(true);
//Shoots disc into goal first time
pros::delay(100);
pistonFlywheel.set_value(false);
pros::delay(100);
rightFlywheel.move_velocity(99);
pros::delay(1000);
rightFlywheel.move_velocity(99);
pistonFlywheel.set_value(true);
//Shoots disc into goal second time
pros::delay(100);
rightFlywheel.move_velocity(0);
pistonFlywheel.set_value(false);
pros::delay(1);
*/

//This auton drives to the middle of the field and turn to the goal to shoot it
//This auton is not necessary since you only need to spin up and shoot from roller position
/**
left_drivetrain.move_velocity(65);
right_drivetrain.move_velocity(-50);
//Turns bot to flywheel facing parralel to goal; going to move to other tile
pros::delay(800);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
left_drivetrain.move_velocity(-65);
right_drivetrain.move_velocity(-50);
//Moves forward until middle of field
pros::delay(5000);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
left_drivetrain.move_velocity(-65);
right_drivetrain.move_velocity(50);
//Turns bot to face goal
pros::delay(1400);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
rightFlywheel.move_velocity(170);
leftFlywheel.move_velocity(150);
//Spin up flywheel
pros::delay(2000);
rightFlywheel.move_velocity(170);
leftFlywheel.move_velocity(150);
pistonFlywheel.set_value(true);
//Shoots disc into goal
pros::delay(100);
*/
//End of auton

//Not useful anymore; drivetrain and roller activated at the same time
/**
roller.move_velocity(150);
pros::delay(500);
roller.move_velocity(0);
*/
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
  pros::Motor indexerPush (INDEX2_PORT);
  pros::Optical optical_sensor(OPTICAL_PORT);
  pros::Controller master (CONTROLLER_MASTER);
  bool isPressedExpansion = master.get_digital(DIGITAL_X);
  pistonExpansion.set_value(true);
  pistonExpansion2.set_value(true);
  optical_sensor.set_led_pwm(100);
  while (true) {
    pistonExpansion.set_value(true);
    pistonExpansion2.set_value(true);
    isPressedExpansion = master.get_digital(DIGITAL_X);
    if (master.get_digital(DIGITAL_R1)) {
      //Motor1 was moving at 100 to whoever made it 100; let me know if it was intentional
      Flywheel.move_velocity(135);
    } else {
      Flywheel.move_velocity(0);
    } 

    if (master.get_digital(DIGITAL_L1)){
      intake.move_velocity(210);
    } else if (master.get_digital(DIGITAL_R2)){
      intake.move_velocity(-210);
    } else {
      intake.move_velocity(0);
    }

    /**if (master.get_digital(DIGITAL_L2)) {
      indexerPush.move_velocity(-125);
      pros::delay(200);
      roller.move_velocity(-450);
    } else {
      roller.move_velocity(0);
      indexerPush.move_velocity(0);
    }
    */
    
    if (optical_sensor.get_hue() >= 345 && optical_sensor.get_hue() <= 360 || optical_sensor.get_hue() >= 0 && optical_sensor.get_hue() <= 15) {
      roller.move_velocity(100);
    } else {
      roller.move_velocity(0);
    }

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

  /** Old Code: FOR OLD BOT MAY NOT WORK FOR NEW BOT
  pistonExpansion.set_value(true);
  pistonExpansion2.set_value(true);
  while (true) {
  pistonExpansion.set_value(true);
  pistonExpansion2.set_value(true);
	isPressedExpansion = master.get_digital(DIGITAL_X);
	if (master.get_digital(DIGITAL_R1)) {
    //Motor1 was moving at 100 to whoever made it 100; let me know if it was intentional
		rightFlywheel.move_velocity(-150);
	} else {
		rightFlywheel.move_velocity(0);
	}

	if (master.get_digital(DIGITAL_L1)) {
		//intake.move(-127);
		intake.move_velocity(150);
  } else {
		//intake.move(0);
		intake.move_velocity(0);
	}

	if (master.get_digital(DIGITAL_R2)) {
		roller.move_velocity(100);
	} else if (master.get_digital(DIGITAL_L2)){
		roller.move_velocity(-100);
	} else {
    roller.move_velocity(0);
  }
  //Indexer code ***FOR TESTING ONLY*** COMMENT OUT LATER
  if (master.get_digital(DIGITAL_UP)) {
    index1.move_velocity(125);
  } else {
    index1.move_velocity(0);
  }
  if (master.get_digital(DIGITAL_DOWN)) {
    index2.move_velocity(-100);
  } else {
    index2.move_velocity(0);
  }
  if (master.get_digital(DIGITAL_A)) {
    index3.move_velocity(210);
  } else {
    index3.move_velocity(0);
  }
//Reversed because pnuematics is weird
	if(isPressedExpansion){
		pistonExpansion.set_value(false);
    pistonExpansion2.set_value(false);
		pros::delay(2);
	} else if (!isPressedExpansion) {
		pistonExpansion.set_value(true);
    pistonExpansion2.set_value(true);
	} 
	left_wheels.move(master.get_analog(ANALOG_LEFT_Y)*1.3);
	left_wheels_back.move(master.get_analog(ANALOG_LEFT_Y)*1.3);
  right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));
	right_wheels_back.move(master.get_analog(ANALOG_RIGHT_Y));
	
    pros::delay(2);
  }
  */

}
