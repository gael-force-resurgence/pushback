#include "devices.h"

#include <math.h>
#include <stdio.h>

void Intake::spin(IntakeState state, float speed) {
    this->currentState = state;
    switch (state) {
        case IN:
            FrontstageRoller.spin(fwd, speed, pct);
            // BackstageRoller.spin(fwd, speed, pct);
            ScoringRoller.spin(fwd, speed, pct);
            break;
        case IN_STORAGE:
            FrontstageRoller.spin(fwd, speed, pct);
            // BackstageRoller.spin(fwd, speed, pct);
            ScoringRoller.stop(hold);
            break;
        case OUT:
            FrontstageRoller.spin(fwd, -speed, pct);
            // BackstageRoller.spin(fwd, -speed, pct);
            ScoringRoller.spin(fwd, -speed, pct);
            break;
        case STOP:
            FrontstageRoller.stop(hold);
            ScoringRoller.stop(hold);
            break;
    };
};

double abs(double value) {
    if (value < 0) {
        return -value;
    } else {
        return value;
    };
}

void Intake::unjam() {
    if (abs(FrontstageRoller.velocity(pct)) < 3 && this->antiJamEnabled) {
        printf("Unjamming intake... %f\n", FrontstageRoller.velocity(pct));
        wait(500, msec);
        if (abs(FrontstageRoller.velocity(pct)) >= 3) {
            return;
        }

        if (this->currentState == IN) {
            FrontstageRoller.spin(fwd, -100, pct);
            ScoringRoller.spin(fwd, -100, pct);

            wait(400, msec);

            FrontstageRoller.spin(fwd, 100, pct);
            ScoringRoller.spin(fwd, 100, pct);

            wait(500, msec);
        } else if (this->currentState == IN_STORAGE) {
            FrontstageRoller.spin(fwd, -100, pct);

            wait(400, msec);

            FrontstageRoller.spin(fwd, 100, pct);

            wait(500, msec);
        } else if (this->currentState == OUT) {
            FrontstageRoller.spin(fwd, 100, pct);
            ScoringRoller.spin(fwd, 100, pct);

            wait(400, msec);

            FrontstageRoller.spin(fwd, -100, pct);
            ScoringRoller.spin(fwd, -100, pct);

            wait(500, msec);
        }
    };
};