#pragma once

using namespace vex;

enum IntakeState {
    IN_FULL,
    IN_STORAGE,
    OUT_FULL
};

class Intake {
   private:
    vex::motor FrontstageRoller, BackstageRoller, ScoringRoller;

   public:
    Intake(motor frontstage, motor back, motor scoring) : FrontstageRoller(frontstage), BackstageRoller(back), ScoringRoller(scoring) {};

    inline void setState(IntakeState state) {
        switch (state) {
            case IN_FULL:
                FrontstageRoller.spin(fwd, 100, pct);
                BackstageRoller.spin(fwd, 100, pct);
                ScoringRoller.spin(fwd, 100, pct);
                break;
            case IN_STORAGE:
                FrontstageRoller.spin(fwd, 100, pct);
                BackstageRoller.spin(fwd, 100, pct);
                ScoringRoller.stop(hold);
                break;
            case OUT_FULL:
                FrontstageRoller.spin(fwd, -100, pct);
                BackstageRoller.spin(fwd, -100, pct);
                ScoringRoller.spin(fwd, -100, pct);
                break;
        }
    };

    /**
     * Starts the intake control thread.
     */
    inline void startThread() {

    };
};