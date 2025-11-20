#include "devices.h"

void Intake::spin(IntakeState state, float speed) {
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
            this->stop();
            break;
    };
};