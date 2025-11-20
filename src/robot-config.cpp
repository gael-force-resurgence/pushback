#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

motor Left1 = motor(PORT1, ratio6_1, true);
motor Left2 = motor(PORT2, ratio18_1, true);
motor Left3 = motor(PORT3, ratio18_1, true);
motor Right1 = motor(PORT8, ratio18_1, false);
motor Right2 = motor(PORT9, ratio18_1, false);
motor Right3 = motor(PORT10, ratio18_1, false);

motor FrontstageRoller = motor(PORT6, ratio6_1, true);
// motor BackstageRoller = motor(PORT12, ratio6_1, true);
motor ScoringRoller = motor(PORT13, ratio6_1, false);

Intake intake = Intake(FrontstageRoller, ScoringRoller);

pneumatics Wedge = pneumatics(Brain.ThreeWirePort.A);
pneumatics Scoring = pneumatics(Brain.ThreeWirePort.C);

void vexcodeInit(void) {};