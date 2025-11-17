#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants() {
    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(10, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .42, 0, 5, 0);
    chassis.set_turn_constants(12, .4, .03, 4.5, 15);
    chassis.set_swing_constants(12, .45, .001, 1.7, 8);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 200, 5000);
    chassis.set_turn_exit_conditions(1, 100, 1500);
    chassis.set_swing_exit_conditions(1, 100, 1000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants() {
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.drive_min_voltage = 0;
}

void odom_test() {
    chassis.set_coordinates(0, 0, 0);
    while (1) {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(5, 20, "X: %f", chassis.get_X_position());
        Brain.Screen.printAt(5, 40, "Y: %f", chassis.get_Y_position());
        Brain.Screen.printAt(5, 60, "Heading: %f", chassis.get_absolute_heading());
        Brain.Screen.printAt(5, 80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
        Brain.Screen.printAt(5, 100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
        task::sleep(20);
    }
}

#define PRINT_COORDS \
    printf("X: %.2f, Y: %.2f, Theta: %.2f\n", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());

void red_solo_awp() {
    default_constants();

    Wedge.open();
    chassis.drive_distance(20, 0, 12, 6, 1.5, 100, 2000);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-5, 90, 12, 6, 1.5, 100, 2000);
    FrontstageRoller.spin(fwd, 100, pct);
    BackstageRoller.spin(fwd, 100, pct);
    ScoringRoller.spin(fwd, 100, pct);
    chassis.drive_distance(20, 90, 12, 6, 1.5, 100, 2000);
    chassis.drive_distance(-3, 90, 5, 6, 1.5, 100, 2000);

    chassis.drive_stop(hold);
};

void blue_solo_awp() {
    default_constants();

    Wedge.open();
    chassis.drive_distance(20, 0, 12, 6, 1.5, 100, 2000);
    chassis.turn_to_angle(-90);
    chassis.drive_distance(-5, -90, 12, 6, 1.5, 100, 2000);
    FrontstageRoller.spin(fwd, 100, pct);
    BackstageRoller.spin(fwd, 100, pct);
    ScoringRoller.spin(fwd, 100, pct);
    chassis.drive_distance(20, -90, 12, 6, 1.5, 100, 1000);
    chassis.drive_distance(-2, -90, 5, 6, 1.5, 100, 2000);
    wait(500, msec);
    FrontstageRoller.stop();
    BackstageRoller.stop(hold);
    ScoringRoller.stop(hold);
    chassis.drive_distance(-10, -90, 5, 6, 1.5, 100, 2000);
    chassis.turn_to_angle(90);
    chassis.drive_distance(10, 90, 8, 6, 1.5, 100, 2000);

    chassis.drive_stop(hold);
};